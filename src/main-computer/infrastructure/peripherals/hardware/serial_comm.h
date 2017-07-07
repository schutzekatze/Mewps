/*
 * serial_comm.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIAL_COMM_H_
#define INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIAL_COMM_H_

/*
 * This header declares routines for serial communication between
 * the main computer and the microcontroller.
 *
 * The mode used is 8N1, 8 bit character size, no parity and 1 stop bit.
 * All messages are fixed size of 2 bytes in network byte order,
 * that is, big endian.
 * Every message is followed by a checksum byte, a simple sum of message bytes.
 * If on receive the checksum is correct, an ACKNOWLEDGE byte is sent back.
 * If the checksum is incorrect, a NEGATIVE_ACKNOWLEDGE byte is sent back.
 * If an error occurs with an acknowledge byte, assume
 * values greater than 127 to be ACKNOWLEDGE, and less than or equal to 127
 * to be NEGATIVE_ACKNOWLEDGE.
 * On negative acknowledge, the message is resent up to 3 times.
 * If all three attempts fail, the communication should abort and
 * an error should be thrown.
 * Both sides of the communication should include this header, and implement
 * the send and receive functions specific to their platform.
 */

#include <stdint.h>

constexpr int BAUD_RATE = 9600;

const uint8_t ACKNOWLEDGE = 255;
const uint8_t NEGATIVE_ACKNOWLEDGE = 0;

const int ATTEMPTS_BEFORE_ABORT = 3;

// These functions require platform specific implementations to use serial communication.
void serial_comm_send(const uint16_t msg);
uint16_t serial_comm_receive();

#endif /* INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIAL_COMM_H_ */
