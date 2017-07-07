/*
 * SerialCommConnectionError.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMCONNECTIONERROR_H_
#define INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMCONNECTIONERROR_H_

#include <stdexcept>
using std::runtime_error;

namespace infrastructure
{

class SerialCommConnectionError: public runtime_error
{

public:

    SerialCommConnectionError(): runtime_error("Serial communication is having connectivity problems.") {}

};

} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMCONNECTIONERROR_H_ */
