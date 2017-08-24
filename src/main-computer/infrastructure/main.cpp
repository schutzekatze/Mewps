/*
 * main.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "peripherals/Motors.h"
using infrastructure::Motors;

#include <iostream>
using std::cout;
using std::stoi;
using std::stof;

#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
using namespace std::chrono_literals;
using std::chrono::milliseconds;

#include <exception>
using std::exception;

int main(int argc, char** argv) {
	sleep_for(2s);

	if (argc != 4) {
		cout << "Bad arguments\n";
		return -1;
	} else {
		cout << "Start\n";
	}

	try {

		Motors::set_powers(stof(argv[1]), stof(argv[2]));

		sleep_for(milliseconds(stoi(argv[3])));

		Motors::set_powers(0, 0);

		sleep_for(milliseconds(stoi(argv[3])));
	}
	catch (exception &e) {
		cout << e.what() << '\n';
	}

	cout << "End\n";

    return 0;
}
