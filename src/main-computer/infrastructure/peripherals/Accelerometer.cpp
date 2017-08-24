/*
 * Accelerometer.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "Accelerometer.h"

using std::make_tuple;
using std::tie;

#include "microcontroller/Communicator.h"
using infrastructure::microcontroller::Communicator;

namespace infrastructure {

tuple<float, float, float> Accelerometer::get_accelerations() {
	int ax, ay, az;
	tie(ax, ay, az) = Communicator::request_accelerometer_data();

	return make_tuple(ax * CONVERSION_FACTOR, ay * CONVERSION_FACTOR, az * CONVERSION_FACTOR);
}

}  /* namespace infrastructure */
