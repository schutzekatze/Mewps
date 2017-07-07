/*
 * PowerSupply.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_POWERSUPPLY_H_
#define INFRASTRUCTURE_PERIPHERALS_POWERSUPPLY_H_

namespace infrastructure
{

class PowerSupply
{

public:

	// Returns a value from 0.0 to 1.0 (0% - 100%) based on how much power is left
	static float get_supply_status();

	// Returns estimated seconds left until the power supply is exhausted
	static int get_estimated_remaining_time();

private:

	static constexpr float CONVERSION_FACTOR = 2.0 * 5.0 / 1024.0 * 1.029;
	static constexpr float MIN_VOLTAGE = 7.6;
	static constexpr float MAX_VOLTAGE = 9.6;

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_POWERSUPPLY_H_ */
