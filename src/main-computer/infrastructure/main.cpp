/*
 * main.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "peripherals/Motors.h"
using infrastructure::Motors;

#include <iostream>
using std::cout;

#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
using namespace std::chrono_literals;

#include <exception>
using std::exception;

int main() {
	sleep_for(2s);

	cout << "start\n";

	try {

		Motors::set_powers(127, 127);

		sleep_for(1s);

		Motors::set_powers(0, 0);

	}
	catch (exception &e) {
		cout << e.what() << '\n';
	}

    return 0;
}
