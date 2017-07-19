/*
 * Compass.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "Compass.h"

#include "microcontroller/Communicator.h"
using infrastructure::microcontroller::Communicator;

namespace infrastructure {

float Compass::get_orientation() {
	return Communicator::request_compass_orientation() * CONVERSION_FACTOR;
}

}  /* namespace infrastructure */
