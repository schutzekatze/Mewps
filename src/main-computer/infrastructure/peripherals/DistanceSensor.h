/*
 * DistanceSensor.h
 *
 *  Created on: Jan 24, 2017
 *      Author: schutzekatze
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_DISTANCESENSOR_H_
#define INFRASTRUCTURE_PERIPHERALS_DISTANCESENSOR_H_

namespace infrastructure
{

class DistanceSensor
{

public:

	// Returns distance registered in centimeters
	static float get_distance();

private:

    static constexpr float CONVERSION_FACTOR = 0.001;

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_DISTANCESENSOR_H_ */
