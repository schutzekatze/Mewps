/*
 * Motors.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "Motors.h"
using std::make_tuple;
using std::unique_lock;

#include <chrono>
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

#include "microcontroller/Communicator.h"
using infrastructure::microcontroller::Communicator;

#include "InvalidMotorPowerError.h"

#include <iostream>
using std::cout;

namespace infrastructure {

int sgn(float n) {
    return n >= 0 ? 1 : -1;
}

void Motors::set_powers(float power_left, float power_right) {
    if ((power_left < -1.0 || power_left > 1.0) ||
        (power_right < -1.0 || power_right > 1.0)) {
        throw InvalidMotorPowerError(power_left, power_right);
    }

    unique_lock<mutex> lock(power_mutex);

	power_left_desired = power_left;
	power_right_desired = power_right;

    degree_left_desired = power2degree(power_left);
    degree_right_desired = power2degree(power_right);

    degree_left_step_sign = sgn(degree_left_desired - degree_left);
    degree_right_step_sign = sgn(degree_right_desired - degree_right);

    power_desired_changed = true;
    power_desired_changed_condition.notify_one();
}

tuple<float, float> Motors::get_powers() {
    unique_lock<mutex> lock(power_mutex);

    return make_tuple(power_left, power_right);
}

void Motors::power_regulator_routine() {
    power_regulator.detach();

    bool done_left, done_right;
    for(;;) {
        {
            unique_lock<mutex> lock(power_mutex);
            while (!power_desired_changed)
                power_desired_changed_condition.wait(lock);
            power_desired_changed = false;
        }

        done_left = done_right = false;
        for(;;) {
            {
                unique_lock<mutex> lock(power_mutex);

                if (!done_left) {
                    degree_left += degree_left_step_sign * DEGREE_STEP;
                    if ((degree_left_desired - degree_left) * degree_left_step_sign < 0) {
                        degree_left = degree_left_desired;
                        done_left = true;
                    }
                }

                if (!done_right) {
                    degree_right += degree_right_step_sign * DEGREE_STEP;
                    if ((degree_right_desired - degree_right) * degree_right_step_sign < 0) {
                        degree_right = degree_right_desired;
                        done_right = true;
                    }
                }

                Communicator::issue_motors_command(
                    degree2power(degree_left) * CONVERSION_FACTOR,
                    degree2power(degree_right) * CONVERSION_FACTOR
                );
            }

            const int sleeptime = POWER_CHANGE_PERIOD;
            if (done_left && done_right) {
                unique_lock<mutex> lock(power_mutex);

                if (power_desired_changed) {
                    power_desired_changed = false;
                    done_left = done_right = false;

                    lock.unlock();
                    sleep_for(milliseconds(sleeptime));
                } else {
                    break;
                }
            } else {
                sleep_for(milliseconds(sleeptime));
            }
        }
    }
}

float Motors::power_left = 0, Motors::power_right = 0;
float Motors::power_left_desired = 0, Motors::power_right_desired = 0;
bool Motors::power_desired_changed = false;
mutex Motors::power_mutex;
condition_variable Motors::power_desired_changed_condition;

float Motors::degree_left = 0, Motors::degree_right = 0;
float Motors::degree_left_desired = 0, Motors::degree_right_desired = 0;
float Motors::degree_left_step_sign = 0, Motors::degree_right_step_sign = 0;

thread Motors::power_regulator(power_regulator_routine);

}  /* namespace infrastructure */
