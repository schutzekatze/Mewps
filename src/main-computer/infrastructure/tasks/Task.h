/*
 * Task.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_TASK_H
#define INFRASTRUCTURE_TASK_H

#include <atomic>
using std::atomic;

#include <mutex>
using std::mutex;

#include <condition_variable>
using std::condition_variable;

namespace infrastructure {

/*
 * A task is an action intended to be performed by the robot.
 * Only one task can be executed at a time.
 */
class Task {

public:

    /*
     * States in which a task can be in, one at a time.
     * CARDINALITY is not a state; it is merely used to obtain the number of the enumerations.
     */
    enum State { INITIAL = 0, RUNNING, INTERRUPTED, ENDED, CARDINALITY };

    /*
     * The calling thread waits until the task reaches the given state.
     * If the task reaches the ending state, all waiting threads are resumed.
     */
    void wait_for_state(State state);

    State get_state();

    virtual ~Task() = default;

    Task(const Task&) = default; Task& operator=(const Task&) = default;
    Task(Task&&) = default; Task& operator=(Task&&) = default;

protected:

    /*
     * The execute method needs to be implemented by the concrete task derived classes
     * and should contain the logic of the task and direct instructions to the robot.
     */
    virtual void execute() = 0;

    /*
     * During execution, a task may receive the interrupt signal which signifies
     * that it should pause as soon as possible.
     * One of the reasons why the interrupt was received can be because another task
     * with higher priority was issued.
     * A task can periodically check if it was interrupted with the is_interrupted() method,
     * or it can override the on_interrupt() method, which is automatically
     * executed on interrupt.
     * It should then stop the current operations (by ending the execute method)
     * and save the current state to resume later.
     * On resume, the execute() method is called again,
     * wherefrom the task should read the previous state and continue executing.
     * It may take a while before a task is resumed, if ever (!),
     * so free any acquired resources before exiting the execute() method.
     */
    bool is_interrupted() const { return interrupted; }
    virtual void on_interrupt() {}

    Task(): interrupted(false), state(INITIAL) {}

private:

    static void on_interrupt_wrapper(Task* task) { task->on_interrupt(); }

    void set_state(State state);

    atomic<bool> interrupted;

    State state;
    mutex state_mutex;
    condition_variable state_conditions[State::CARDINALITY];

    friend class TaskExecuter;

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_TASK_H */
