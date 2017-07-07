/*
 * Microphones.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: schutzekatze
 */

#include "Microphones.h"

#include "CommProtocolThreadsafe.h"

namespace infrastructure
{

void Microphones::get_intensities(float *intensity1, float *intensity2, float *intensity3)
{
    int16_t int_intensity1, int_intensity2, int_intensity3;

    CommProtocolThreadsafe::request_microphone_data_ts(&int_intensity1, &int_intensity2, &int_intensity3);

    *intensity1 = CONVERSION_FACTOR * int_intensity1;
    *intensity2 = CONVERSION_FACTOR * int_intensity2;
    *intensity3 = CONVERSION_FACTOR * int_intensity3;
}

}  /* namespace infrastructure */
