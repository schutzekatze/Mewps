/*
 * InvalidTaskError.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_INVALIDTASKERROR_H_
#define INFRASTRUCTURE_INVALIDTASKERROR_H_

#include <exception>
using std::runtime_error;

namespace infrastructure
{

class InvalidTaskError: public runtime_error
{

public:

    InvalidTaskError(): runtime_error("Invalid task acquired.") {}

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_INVALIDTASKERROR_H_ */
