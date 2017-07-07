/*
 * comm_protocol.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_COMM_PROTOCOL_H_
#define INFRASTRUCTURE_PERIPHERALS_COMM_PROTOCOL_H_

#include "hardware/serial_comm.h"

// Unique preambles to identify message type
const int16_t MICROPHONE_REQUEST = 0;
const int16_t MOTORS_COMMAND = 1;
const int16_t DISTANCE_REQUEST = 2;
const int16_t ACCELEROMETER_REQUEST = 3;
const int16_t POWER_STATUS_REQUEST = 4;

// Protocol wrappers
inline int16_t receive_preamble()
{
    return serial_comm_receive();
}

inline void request_microphone_data(int16_t* intensity1, int16_t* intensity2, int16_t* intensity3)
{
    serial_comm_send(MICROPHONE_REQUEST);
    *intensity1 = serial_comm_receive();
    *intensity2 = serial_comm_receive();
    *intensity3 = serial_comm_receive();
}

inline void send_microphone_data(const int16_t intensity1, const int16_t intensity2, const int16_t intensity3)
{
    serial_comm_send(intensity1);
    serial_comm_send(intensity2);
    serial_comm_send(intensity3);
}

inline void issue_motors_command(const int16_t power_left, const int16_t power_right)
{
    serial_comm_send(MOTORS_COMMAND);
    serial_comm_send(power_left);
    serial_comm_send(power_right);
}

inline void receive_motors_command(int16_t* power_left, int16_t* power_right)
{
    *power_left = serial_comm_receive();
    *power_right = serial_comm_receive();
}

inline void request_distance(int16_t* distance)
{
    serial_comm_send(DISTANCE_REQUEST);
    *distance = serial_comm_receive();
}

inline void send_distance(const int16_t distance)
{
    serial_comm_send(distance);
}

inline void request_accelerometer_data(int16_t *ax, int16_t *ay, int16_t *az)
{
    serial_comm_send(ACCELEROMETER_REQUEST);
    *ax = serial_comm_receive();
    *ay = serial_comm_receive();
    *az = serial_comm_receive();
}

inline void send_accelerometer_data(const int16_t ax, const int16_t ay, const int16_t az)
{
    serial_comm_send(ax);
    serial_comm_send(ay);
    serial_comm_send(az);
}

inline void request_power_status(int16_t* status)
{
    serial_comm_send(POWER_STATUS_REQUEST);
    *status = serial_comm_receive();
}

inline void send_power_status(const int16_t status)
{
    serial_comm_send(status);
}

#endif /* INFRASTRUCTURE_PERIPHERALS_COMM_PROTOCOL_H_ */
