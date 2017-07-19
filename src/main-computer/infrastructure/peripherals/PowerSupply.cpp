/*
 * PowerSupply.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "PowerSupply.h"

#include "microcontroller/Communicator.h"
using infrastructure::microcontroller::Communicator;

namespace infrastructure {

float PowerSupply::get_supply_status() {
	return (Communicator::request_power_status() * CONVERSION_FACTOR - MIN_VOLTAGE)
												      / (MAX_VOLTAGE - MIN_VOLTAGE);
}

float PowerSupply::get_estimated_remaining_time() {
	return 0;
}

}  /* namespace infrastructure */
