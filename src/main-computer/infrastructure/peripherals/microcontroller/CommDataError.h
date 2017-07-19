/*
 * CommDataError.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMDATAERROR_H
#define INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMDATAERROR_H

#include <stdexcept>
using std::runtime_error;

namespace infrastructure {
namespace microcontroller {

class CommDataError: public runtime_error
{

public:

    CommDataError(): runtime_error("The transmitted data keeps failing the checksum test.") {}

};

} /* namespace microcontroller */
} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMDATAERROR_H */
