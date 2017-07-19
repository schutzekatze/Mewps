/*
 * MicrocontrollerCommunicator.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "Communicator.h"

using std::unique_lock;
using std::make_tuple;

#include "comm_protocol.h"

namespace infrastructure {
namespace microcontroller {

inline void issue_motors_command_wrapper(const int power_left, const int power_right) {
    issue_motors_command(power_left, power_right);
}

void Communicator::issue_motors_command(const int power_left, const int power_right) {
    unique_lock<mutex> lock(threadsafety);

    issue_motors_command_wrapper(power_left, power_right);
}

inline void request_distance_wrapper(int16_t* distance) {
    request_distance(distance);
}

int Communicator::request_distance() {
    unique_lock<mutex> lock(threadsafety);

    int16_t distance;
    request_distance_wrapper(&distance);
    return distance;
}

inline void request_accelerometer_data_wrapper(int16_t *ax, int16_t *ay, int16_t *az) {
    request_accelerometer_data(ax, ay, az);
}

tuple<int, int, int> Communicator::request_accelerometer_data() {
    unique_lock<mutex> lock(threadsafety);

    int16_t ax, ay, az;
    request_accelerometer_data_wrapper(&ax, &ay, &az);

    return make_tuple(ax, ay, az);
}

inline void request_compass_orientation_wrapper(int16_t* orientation) {
    request_compass_orientation(orientation);
}

int Communicator::request_compass_orientation() {
    unique_lock<mutex> lock(threadsafety);

    int16_t orientation;
    request_compass_orientation_wrapper(&orientation);
    return orientation;
}

inline void request_power_status_wrapper(int16_t* status) {
    request_power_status(status);
}

int Communicator::request_power_status() {
    unique_lock<mutex> lock(threadsafety);

    int16_t status;
    request_power_status_wrapper(&status);
    return status;
}

mutex Communicator::threadsafety;

} /* namespace microcontroller */
} /* namespace infrastructure */
