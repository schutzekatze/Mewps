/*
 * SerialCommunicator.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMUNICATOR_H_
#define INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMUNICATOR_H_

#include <cstdint>

#include <atomic>
using std::atomic;

namespace infrastructure
{

class SerialCommunicator
{

public:

	static constexpr int TIMEOUT_PERIOD = 20; //tenths of a second

	static void send(const uint16_t msg);
	static uint16_t receive();

	static int get_failures();

private:

	static constexpr const char* tty_path = "/dev/ttyACM0";

	static int tty;

	static atomic<int> failures;

	static struct Init
	{
        Init();
        ~Init();
	} init;

};

} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMUNICATOR_H_ */
