/*
 * ComInitError.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMINITERROR_H
#define INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMINITERROR_H

#include <stdexcept>
using std::runtime_error;

namespace infrastructure {
namespace microcontroller {

class CommInitError: public runtime_error
{

public:

    CommInitError():
        runtime_error("Communication with the microcontroller could not be initialized.") {}

};

} /* namespace microcontroller */
} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMINITERROR_H */
