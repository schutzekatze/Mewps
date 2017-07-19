/*
 * DistanceSensor.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_DISTANCESENSOR_H
#define INFRASTRUCTURE_PERIPHERALS_DISTANCESENSOR_H

namespace infrastructure {

class DistanceSensor {

public:

	// Returns distance registered in centimeters
	static float get_distance();

private:

	DistanceSensor() = delete;

    static constexpr float CONVERSION_FACTOR = 0.001;

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_DISTANCESENSOR_H */
