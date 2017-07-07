/*
 * SerialCommInitError.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMINITERROR_H_
#define INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMINITERROR_H_

#include <stdexcept>
using std::runtime_error;

namespace infrastructure
{

class SerialCommInitError: public runtime_error
{

public:

    SerialCommInitError(): runtime_error("Serial communication could not be initialized.") {}

};

} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMINITERROR_H_ */
