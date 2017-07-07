/*
 * Motors.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "Motors.h"

#include "CommProtocolThreadsafe.h"

#include "InvalidMotorPowerError.h"

namespace infrastructure
{

float Motors::power_left = 0;
float Motors::power_right = 0;

void Motors::set_powers(float power_left, float power_right)
{
    if ((power_left < -1.0 || power_left > 1.0) ||
        (power_right < -1.0 || power_right > 1.0))
    {
        throw InvalidMotorPowerError(power_left, power_right);
    }

	Motors::power_left = power_left;
	Motors::power_right = power_right;

	int16_t left = power_left * CONVERSION_FACTOR;
	int16_t right = power_right * CONVERSION_FACTOR;

    CommProtocolThreadsafe::issue_motors_command_ts(left, right);
}

void Motors::get_powers(float *power_left, float *power_right)
{
    *power_left = Motors::power_left;
    *power_right = Motors::power_right;
}

}  /* namespace infrastructure */
