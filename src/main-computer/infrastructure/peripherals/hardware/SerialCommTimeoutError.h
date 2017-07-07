/*
 * SerialCommTimeoutError.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMTIMEOUTERROR_H_
#define INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMTIMEOUTERROR_H_

#include <stdexcept>
using std::runtime_error;

namespace infrastructure
{

class SerialCommTimeoutError: public runtime_error
{

public:

    SerialCommTimeoutError(): runtime_error("Serial communication has timed out.") {}

};

} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_HARDWARE_SERIALCOMMTIMEOUTERROR_H_ */
