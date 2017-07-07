/*
 * CommProtocolThreadsafe.h
 *
 *  Created on: Jan 27, 2017
 *      Author: schutzekatze
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_COMMPROTOCOLTHREADSAFE_H_
#define INFRASTRUCTURE_PERIPHERALS_COMMPROTOCOLTHREADSAFE_H_

#include "comm_protocol.h"

#include <mutex>
using std::mutex;
using std::unique_lock;

namespace infrastructure
{

class CommProtocolThreadsafe
{

public:

	static int16_t receive_preamble_ts()
	{
	    unique_lock<mutex> lock(threadsafety);

	    return receive_preamble();
	}

	static void request_microphone_data_ts(int16_t* intensity1, int16_t* intensity2, int16_t* intensity3)
	{
	    unique_lock<mutex> lock(threadsafety);

	    request_microphone_data(intensity1, intensity2, intensity3);
	}

	static void send_microphone_data_ts(const int16_t intensity1, const int16_t intensity2, const int16_t intensity3)
	{
	    unique_lock<mutex> lock(threadsafety);

	    send_microphone_data(intensity1, intensity2, intensity3);
	}

	static void issue_motors_command_ts(const int16_t power_left, const int16_t power_right)
	{
	    unique_lock<mutex> lock(threadsafety);

	    issue_motors_command(power_left, power_right);
	}

	static void receive_motors_command_ts(int16_t* power_left, int16_t* power_right)
	{
		unique_lock<mutex> lock(threadsafety);

	    receive_motors_command(power_left, power_right);
	}

	static void request_distance_ts(int16_t* distance)
	{
		unique_lock<mutex> lock(threadsafety);

	    request_distance(distance);
	}

	static void send_distance_ts(const int16_t distance)
	{
	    unique_lock<mutex> lock(threadsafety);

	    send_distance(distance);
	}

	static void request_accelerometer_data_ts(int16_t *ax, int16_t *ay, int16_t *az)
	{
		unique_lock<mutex> lock(threadsafety);

	    request_accelerometer_data(ax, ay, az);
	}

	static void send_accelerometer_data_ts(const int16_t ax, const int16_t ay, const int16_t az)
	{
	    unique_lock<mutex> lock(threadsafety);

	    send_accelerometer_data(ax, ay, az);
	}

	static void request_power_status_ts(int16_t* status)
	{
		unique_lock<mutex> lock(threadsafety);

	    request_power_status(status);
	}

	static void send_power_status_ts(const int16_t status)
	{
	    unique_lock<mutex> lock(threadsafety);

	    send_power_status(status);
	}

private:

	static mutex threadsafety;

};

} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_COMMPROTOCOLTHREADSAFE_H_ */
