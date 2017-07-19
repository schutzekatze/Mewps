/*
* code.ino
*
*  Copyright 2017 Vladimir Nikolić
*/

#include "../main-computer/infrastructure/peripherals/microcontroller/comm_protocol.h"

// Left and right motor pins respectively
const unsigned MOTOR_PINS[] = { 10, 11, 5, 6 };

void serial_comm_send(const uint16_t msg)
{
    uint16_t network_msg = ((msg << 8) & 0xff00) | ((msg >> 8) & 0x00ff);
    unsigned bytes;
    uint8_t checksum, response;

    unsigned i;
    for(i = 0; i < ATTEMPTS_BEFORE_ABORT; i++)
    {
        bytes = 0;
        while (bytes < sizeof(network_msg))
        {
            bytes += Serial.write((const uint8_t*)&network_msg + bytes, sizeof(network_msg) - bytes);
        }

        checksum = (network_msg & 0x00ff) + (network_msg >> 8 & 0x00ff);
        Serial.write(&checksum, sizeof(checksum));

        while (Serial.available() == 0);
        response = Serial.read();

        if (fabs((int)response - ACKNOWLEDGE) < fabs((int)response - NEGATIVE_ACKNOWLEDGE))
        {
            break;
        }
    }
}

uint16_t serial_comm_receive()
{
    uint16_t network_msg;
    uint8_t *byte, checksum;

    unsigned i, j;
    for(i = 0; i < ATTEMPTS_BEFORE_ABORT; i++)
    {
        byte = (uint8_t*)&network_msg;
        for (j = 0; j < sizeof(network_msg); j++)
        {
            while (Serial.available() == 0);

            *byte = Serial.read();
            byte++;
        }

        while (Serial.available() == 0);
        checksum = Serial.read();

        if ((uint8_t)((network_msg & 0x00ff) + (network_msg >> 8 & 0x00ff)) == checksum)
        {
            Serial.write((const uint8_t*)&ACKNOWLEDGE, sizeof(ACKNOWLEDGE));

            break;
        }
        else
        {
            Serial.write((const uint8_t*)&NEGATIVE_ACKNOWLEDGE, sizeof(NEGATIVE_ACKNOWLEDGE));
        }
    }

    return ((network_msg << 8) & 0xff00) | ((network_msg >> 8) & 0x00ff);
}

inline void set_motors_power(int16_t power_left, int16_t power_right)
{
    if (power_left < -255 || power_left > 255) return;
    if (power_right < -255 || power_right > 255) return;

    int16_t powers[] = { power_left, 0, power_right, 0 };

    if (power_left < 0)
    {
        powers[0] = 0;
        powers[1] = -power_left;
    }

    if (power_right < 0)
    {
        powers[2] = 0;
        powers[3] = -power_right;
    }

    unsigned i;
    for(i = 0; i < sizeof(MOTOR_PINS) / sizeof(unsigned); i++)
    {
        analogWrite(MOTOR_PINS[i], powers[i]);
    }
}

inline void read_distance(int16_t *distance)
{
    *distance = 0;
}

inline void read_accelerometer_data(int16_t *ax, int16_t *ay, int16_t *az)
{
    *ax = 0;
    *ay = 0;
    *az = 0;
}

inline void read_compass_orientation(int16_t *orientation) {
    *orientation = 0;
}

inline void read_power_status(int16_t *status)
{
    *status = 0;
}

void setup()
{
    unsigned pin;
    for (pin = 0; pin < sizeof(MOTOR_PINS) / sizeof(unsigned); pin++)
    {
        pinMode(MOTOR_PINS[pin], OUTPUT);
    }

    Serial.begin(BAUD_RATE);
}

void loop()
{
    int16_t preamble = receive_preamble();
    switch (preamble)
    {
        case MOTORS_COMMAND:
        {
            int16_t power_left;
            int16_t power_right;

            receive_motors_command(&power_left, &power_right);
            set_motors_power(power_left, power_right);

            break;
        }
        case DISTANCE_REQUEST:
        {
            int16_t distance;

            read_distance(&distance);
            respond_distance(distance);

            break;
        }
        case ACCELEROMETER_REQUEST:
        {
            int16_t ax;
            int16_t ay;
            int16_t az;

            read_accelerometer_data(&ax, &ay, &az);
            respond_accelerometer_data(ax, ay, az);

            break;
        }
        case COMPASS_REQUEST:
        {
            int16_t orientation;

            read_compass_orientation(&orientation);
            respond_compass_orientation(orientation);

            break;
        }
        case POWER_STATUS_REQUEST:
        {
            int16_t status;

            read_power_status(&status);
            respond_power_status(status);

            break;
        }
    }
}
