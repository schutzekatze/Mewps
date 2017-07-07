/*
 * DistanceSensor.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: schutzekatze
 */

#include "DistanceSensor.h"

#include "CommProtocolThreadsafe.h"

namespace infrastructure
{

float DistanceSensor::get_distance()
{
	int16_t millimeters;

	CommProtocolThreadsafe::request_distance_ts(&millimeters);

	return CONVERSION_FACTOR * millimeters;
}

}  /* namespace infrastructure */
