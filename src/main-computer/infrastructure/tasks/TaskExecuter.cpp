/*
 * TaskExecuter.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "TaskExecuter.h"

using std::unique_lock;

namespace infrastructure {

void TaskExecuter::start() {
    unique_lock<mutex> lock(operation_mutex);

    if (!running) {
        running = true;

        running_condition.notify_one();
    }
}

void TaskExecuter::stop() {
    unique_lock<mutex> lock(operation_mutex);

    if (running) {
        running = false;

        if (executing) {
            interrupt_current_task();
        }
        else {
            executing_condition.notify_one();
        }
    }
}

void TaskExecuter::clear() {
    unique_lock<mutex> lock(operation_mutex);

    while (task_pool.size() > 0) task_pool.pop();
    while (interrupted_tasks.size() > 0) interrupted_tasks.pop();
}

void TaskExecuter::enqueue_task(Task* task, Priority priority) {
    unique_lock<mutex> lock(operation_mutex);

    if (executing && (priority > current_task.priority)) {
        interrupt_current_task();
    }

    task_pool.push( { task, priority } );

    if (!executing) {
        executing_condition.notify_one();
    }
}

const TaskExecuter::QueuedTask& TaskExecuter::get_current_task() {
    unique_lock<mutex> lock(operation_mutex);

    if (!executing) {
        throw NoTaskError();
    }

    return current_task;
}

void TaskExecuter::execute_tasks() {
    executer_thread.detach();

    unique_lock<mutex> lock(operation_mutex);

    for (;;) {
        while (!running) running_condition.wait(lock);

        if (!interrupted_tasks.empty() && !task_pool.empty()) {
            if (interrupted_tasks.top().priority >= task_pool.top().priority) {
                current_task = interrupted_tasks.top();
                interrupted_tasks.pop();
            }
            else {
                current_task = task_pool.top();
                task_pool.pop();
            }

            executing = true;
        }
        else if (!interrupted_tasks.empty()) {
            current_task = interrupted_tasks.top();
            interrupted_tasks.pop();

            executing = true;
        }

        else if(!task_pool.empty()) {
            current_task = task_pool.top();
            task_pool.pop();

            executing = true;
        }

        if (executing) {
            lock.unlock();

            current_task.task->set_state(Task::State::RUNNING);

            current_task.task->execute();

            /*
             * executing must be set to false before wait_on_interrupt_end() is called
             * to prevent interrupts after wait_on_interrupt_end() which would cause
             * interrupts that aren't waited for to end.
             */
            executing = false;

            if (wait_on_interrupt_end()) {
                interrupted_tasks.push(current_task);

                current_task.task->set_state(Task::State::INTERRUPTED);
            }
            else {
                current_task.task->set_state(Task::State::ENDED);
            }

            lock.lock();
        } else {
            do { executing_condition.wait(lock); } while (!executing);
        }
    }
}

void TaskExecuter::interrupt_current_task() {
    unique_lock<mutex> lock(interrupt_mutex);

    if (!current_task.task->interrupted) {
        current_task.task->interrupted = true;

        interrupt_thread = new thread(Task::on_interrupt_wrapper, current_task.task);
    }
}

bool TaskExecuter::wait_on_interrupt_end() {
    unique_lock<mutex> lock(interrupt_mutex);

    if (current_task.task->interrupted) {
        interrupt_thread->join();

        delete interrupt_thread;

        current_task.task->interrupted = false;

        return true;
    }

    return false;
}

thread TaskExecuter::executer_thread(TaskExecuter::execute_tasks);

mutex TaskExecuter::interrupt_mutex;
thread* TaskExecuter::interrupt_thread;

TaskExecuter::QueuedTask TaskExecuter::current_task = { nullptr, CHILL };

priority_queue<TaskExecuter::QueuedTask> TaskExecuter::task_pool;

stack<TaskExecuter::QueuedTask> TaskExecuter::interrupted_tasks;

mutex TaskExecuter::operation_mutex;

atomic<bool> TaskExecuter::running(false);
condition_variable TaskExecuter::running_condition;

atomic<bool> TaskExecuter::executing(false);
condition_variable TaskExecuter::executing_condition;

}  /* namespace infrastructure */
