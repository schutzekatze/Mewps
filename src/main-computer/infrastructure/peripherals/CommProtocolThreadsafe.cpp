/*
 * CommProtocolThreadsafe.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: schutzekatze
 */

#include "CommProtocolThreadsafe.h"

namespace infrastructure
{

mutex CommProtocolThreadsafe::threadsafety;

} /* namespace infrastructure */
