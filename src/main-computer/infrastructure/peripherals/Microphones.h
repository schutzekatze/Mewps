/*
 * Microphones.h
 *
 *  Created on: Jan 24, 2017
 *      Author: schutzekatze
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_MICROPHONES_H_
#define INFRASTRUCTURE_PERIPHERALS_MICROPHONES_H_

namespace infrastructure
{

class Microphones
{

public:

	// Returns registered intensities for each microphone
	static void get_intensities(float *intensity1, float *intensity2, float *intensity3);

private:

	static constexpr float CONVERSION_FACTOR = 0.1;

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_MICROPHONES_H_ */
