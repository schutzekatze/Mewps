/*
 * CommTimeoutError.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMTIMEOUTERROR_H
#define INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMTIMEOUTERROR_H

#include <stdexcept>
using std::runtime_error;

namespace infrastructure {
namespace microcontroller {

class CommTimeoutError: public runtime_error
{

public:

    CommTimeoutError():
        runtime_error("Microcontroller failed to respond within the timeout window.") {}

};

} /* namespace microcontroller */
} /* namespace infrastructure */

#endif /* INFRASTRUCTURE_PERIPHERALS_MICROCONTROLLER_COMMTIMEOUTERROR_H */
