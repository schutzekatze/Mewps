/*
 * Accelerometer.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_ACCELEROMETER_H_
#define INFRASTRUCTURE_PERIPHERALS_ACCELEROMETER_H_

namespace infrastructure
{

class Accelerometer
{

public:

    static void get_accelerations(float* ax, float *ay, float *az);

private:

    static constexpr float CONVERSION_FACTOR = 0.1;

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_ACCELEROMETER_H_ */
