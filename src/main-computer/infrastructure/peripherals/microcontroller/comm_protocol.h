/*
 * comm_protocol.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_COMM_PROTOCOL_H
#define INFRASTRUCTURE_PERIPHERALS_COMM_PROTOCOL_H

#include "serial_comm.h"
#include <stdio.h>

// Unique preambles to identify message type
enum Preamble: int16_t {
    MOTORS_COMMAND,
    DISTANCE_REQUEST,
    ACCELEROMETER_REQUEST,
    COMPASS_REQUEST,
    POWER_STATUS_REQUEST
};

// Protocol wrappers
inline int16_t receive_preamble() {
    return serial_comm_receive();
}

inline void issue_motors_command(const int16_t power_left, const int16_t power_right) {
    serial_comm_send(MOTORS_COMMAND);
    serial_comm_send(power_left);
    serial_comm_send(power_right);
    serial_comm_receive();
}

inline void receive_motors_command(int16_t* power_left, int16_t* power_right) {
    *power_left = serial_comm_receive();
    *power_right = serial_comm_receive();
    serial_comm_send(0);
}

inline void request_distance(int16_t* distance) {
    serial_comm_send(DISTANCE_REQUEST);
    *distance = serial_comm_receive();
}

inline void respond_distance(const int16_t distance) {
    serial_comm_send(distance);
}

inline void request_accelerometer_data(int16_t *ax, int16_t *ay, int16_t *az) {
    serial_comm_send(ACCELEROMETER_REQUEST);
    *ax = serial_comm_receive();
    *ay = serial_comm_receive();
    *az = serial_comm_receive();
}

inline void respond_accelerometer_data(const int16_t ax, const int16_t ay, const int16_t az) {
    serial_comm_send(ax);
    serial_comm_send(ay);
    serial_comm_send(az);
}

inline void request_compass_orientation(int16_t* orientation) {
    serial_comm_send(COMPASS_REQUEST);
    *orientation = serial_comm_receive();
}

inline void respond_compass_orientation(const int16_t orientation) {
    serial_comm_send(orientation);
}

inline void request_power_status(int16_t* status) {
    serial_comm_send(POWER_STATUS_REQUEST);
    *status = serial_comm_receive();
}

inline void respond_power_status(const int16_t status) {
    serial_comm_send(status);
}

#endif /* INFRASTRUCTURE_PERIPHERALS_COMM_PROTOCOL_H */
