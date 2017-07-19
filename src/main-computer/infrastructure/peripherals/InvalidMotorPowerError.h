/*
 * InvalidMotorPowerError.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_INVALIDMOTORPOWERERROR_H
#define INFRASTRUCTURE_PERIPHERALS_INVALIDMOTORPOWERERROR_H

#include <stdexcept>
using std::runtime_error;

#include <tuple>
using std::tuple;
using std::make_tuple;

namespace infrastructure {

class InvalidMotorPowerError: public runtime_error {

public:

    InvalidMotorPowerError(float power_left, float power_right):
    	runtime_error("Motors were given invalid power values."),
		power_left(power_left), power_right(power_right) {}

    tuple<float, float> get_powers() const {
        return make_tuple(power_left, power_right);
    }

private:

    float power_left, power_right;

};

} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_INVALIDMOTORPOWERERROR_H */
