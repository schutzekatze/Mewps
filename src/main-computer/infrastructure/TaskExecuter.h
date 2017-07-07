/*
 * TaskExecuter.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef INFRASTRUCTURE_TASKEXECUTER_H_
#define INFRASTRUCTURE_TASKEXECUTER_H_

#include <queue>
using std::priority_queue;

#include <stack>
using std::stack;

#include <thread>
using std::thread;

#include <atomic>
using std::atomic;

#include <mutex>
using std::mutex;

#include <condition_variable>
using std::condition_variable;

#include "../infrastructure/Task.h"

#include "../infrastructure/InvalidTaskError.h"

namespace infrastructure
{

/*
 * TaskExecuter executes given tasks one at a time based on their priority.
 */
class TaskExecuter
{

public:

    enum Priority { CHILL, LOW, NORMAL, HIGH, EMERGENCY };

    /*
     * Use these methods to start and stop active execution of tasks.
     * Calling the stop method does not wait for the task currently being executed to stop.
     * You can, however, acquire the current task and wait for it to be interrupted.
     */
    static void start();
    static void stop();

    /*
     * Removes all queued and interrupted tasks. (Does not stop the task currently being executed, if any.)
     */
    static void clear();

    /*
     * After starting the TaskExecuter, it is in the running state.
     * While in the running state, it can either be executing or idle.
     * Executing means a task has been acquired and is being actively executed.
     */
    static bool is_running() { return running; }
    static bool is_executing() { return executing; }

    struct QueuedTask
    {
        Task* task;
        Priority priority;

        bool operator<(const QueuedTask& rhs) const { return priority < rhs.priority; }

    private:

        QueuedTask(Task* task, Priority priority): task(task), priority(priority) {}

        friend class TaskExecuter;

    };

    /*
     * Enqueues the given task to be executed with given priority.
     */
    static void enqueue_task(Task* task, Priority priority);

    /*
     * Returns the task currently being executed.
     * The return task is only valid if executing is true,
     * and will throw an InvalidTaskError if called otherwise.
     */
    static const QueuedTask& get_current_task();

private:

    TaskExecuter() = delete;

    static void execute_tasks();
    static thread executer_thread;

    static void interrupt_current_task();
    static bool wait_on_interrupt_end();
    static mutex interrupt_mutex;
    static thread* interrupt_thread;

    static QueuedTask current_task;

    static priority_queue<QueuedTask> task_pool;
    static stack<QueuedTask> interrupted_tasks;

    static mutex operation_mutex;

    static atomic<bool> running;
    static condition_variable running_condition;

    //If executing is true, it means the current_task member contains a valid task.
    static atomic<bool> executing;
    static condition_variable executing_condition;

};

}  /* namespace infrastructure */

#endif /* INFRASTRUCTURE_TASKEXECUTER_H_ */
