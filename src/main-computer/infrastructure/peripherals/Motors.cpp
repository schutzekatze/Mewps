/*
 * Motors.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "Motors.h"

#include "microcontroller/Communicator.h"
using infrastructure::microcontroller::Communicator;

#include "InvalidMotorPowerError.h"

using std::make_tuple;

namespace infrastructure {

float Motors::power_left = 0;
float Motors::power_right = 0;

void Motors::set_powers(float power_left, float power_right) {
    if ((power_left < -1.0 || power_left > 1.0) ||
        (power_right < -1.0 || power_right > 1.0)) {
        throw InvalidMotorPowerError(power_left, power_right);
    }

	Motors::power_left = power_left;
	Motors::power_right = power_right;

	float left = power_left * CONVERSION_FACTOR;
	float right = power_right * CONVERSION_FACTOR;

    Communicator::issue_motors_command(left, right);
}

tuple<float, float> Motors::get_powers() {
    return make_tuple(power_left, power_right);
}

}  /* namespace infrastructure */
