/*
 * TestTask2.h
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#ifndef TESTTASK2_H_
#define TESTTASK2_H_

#include <thread>
#include <chrono>

#include <iostream>
using std::cout;
using std::endl;

#include "infrastructure/Task.h"
using infrastructure::Task;

class TestTask2: public Task
{

public:

    void execute() override
	{
        cout << "a" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << "b" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

};

#endif /* TESTTASK2_H_ */
