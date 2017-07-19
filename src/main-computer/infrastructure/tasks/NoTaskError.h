/*
 * NoTaskError.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_INVALIDTASKERROR_H
#define INFRASTRUCTURE_INVALIDTASKERROR_H

#include <exception>
using std::runtime_error;

namespace infrastructure {

class NoTaskError: public runtime_error {

public:

    NoTaskError(): runtime_error("There's no task to acquire.") {}

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_INVALIDTASKERROR_H */
