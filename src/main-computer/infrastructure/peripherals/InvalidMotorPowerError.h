/*
 * InvalidMotorPowerError.h
 *
 *  Created on: Jan 29, 2017
 *      Author: schutzekatze
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_INVALIDMOTORPOWERERROR_H_
#define INFRASTRUCTURE_PERIPHERALS_INVALIDMOTORPOWERERROR_H_

#include <stdexcept>
using std::runtime_error;

namespace infrastructure
{

class InvalidMotorPowerError: public runtime_error
{

public:

    InvalidMotorPowerError(float power_left, float power_right):
    	runtime_error("Motors were given invalid power values."),
		power_left(power_left), power_right(power_right) {}

    void get_powers(float *power_left, float *power_right) const
    {
    	*power_left = this->power_left;
        *power_right = this->power_right;
    }

private:

    float power_left, power_right;

};

} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_INVALIDMOTORPOWERERROR_H_ */
