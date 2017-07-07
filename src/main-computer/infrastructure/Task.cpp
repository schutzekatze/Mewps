/*
 * Task.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "Task.h"

using std::unique_lock;

namespace infrastructure
{

void Task::wait_for_state(State state)
{
    unique_lock<mutex> lock(state_mutex);

    if (this->state != state)
    {
        state_conditions[state].wait(lock);
    }
}

Task::State Task::get_state()
{
    unique_lock<mutex> lock(state_mutex);

    return state;
}


void Task::set_state(State state)
{
    unique_lock<mutex> lock(state_mutex);

    this->state = state;

    if (state == State::ENDED)
    {
	    for (condition_variable& condition : state_conditions)
	    {
            condition.notify_all();
        }
    }
    else
    {
        state_conditions[state].notify_all();
    }
}

}  /* namespace infrastructure */
