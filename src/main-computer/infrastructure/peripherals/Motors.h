/*
 * Motors.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_MOTORS_H
#define INFRASTRUCTURE_PERIPHERALS_MOTORS_H

#include <tuple>
using std::tuple;

namespace infrastructure {

class Motors {

public:

    /*
     * Set and get powers given to the robot motors.
     * The values range from -1.0 to 1.0, with -1.0 meaning
     * going reverse at max speed, and 1.0 going forward at max speed.
     */
    static void set_powers(float power_left, float power_right);
    static tuple<float, float> get_powers();

private:

    Motors() = delete;

    static constexpr float CONVERSION_FACTOR = 255.0;

    static float power_left, power_right;

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_MOTORS_H */
