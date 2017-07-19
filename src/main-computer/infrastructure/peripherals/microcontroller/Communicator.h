/*
 * Communicator.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMUNICATOR_H
#define INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMUNICATOR_H

#include <mutex>
using std::mutex;

#include <tuple>
using std::tuple;

namespace infrastructure {
namespace microcontroller {

// Threadsafe
class Communicator {

public:

	static void issue_motors_command(const int power_left, const int power_right);
	static int request_distance();
	static tuple<int, int, int> request_accelerometer_data();
	static int request_compass_orientation();
	static int request_power_status();

private:

    Communicator() = delete;

	static mutex threadsafety;

};

} /* namespace microcontroller */
} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLERCOMMUNICATOR_H */
