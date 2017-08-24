/*
 * Accelerometer.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_ACCELEROMETER_H
#define INFRASTRUCTURE_PERIPHERALS_ACCELEROMETER_H

#include <tuple>
using std::tuple;

namespace infrastructure {

// Threadsafe
class Accelerometer {

public:

    // Returns accelerations in x, y and z
    static tuple<float, float, float> get_accelerations();

private:

    static constexpr float CONVERSION_FACTOR = 0.1;

    Accelerometer() = delete;

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_ACCELEROMETER_H */
