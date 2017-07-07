/*
 * TestTask.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef TESTTASK_H_
#define TESTTASK_H_

#include <thread>
#include <chrono>

#include <iostream>
using std::cout;
using std::endl;

#include "infrastructure/Task.h"
using infrastructure::Task;

class TestTask: public Task
{

public:

    void on_interrupt() override
	{
        cout << "interrupted!" << endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    void execute() override {
        while (counter <= 3)
        {
            if (is_interrupted())
            {
                return;
            }

            cout << counter++ << endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

private:

    int counter = 1;

};

#endif /* TESTTASK_H_ */
