/*
 * main.cpp
 *
 *  Copyright 2017 Vladimir Nikolić
 */

#include "peripherals/hardware/serial_comm.h"

#include <iostream>
using std::cout;
using std::endl;

#include <exception>
using std::exception;

#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

int main()
{
	sleep_for(milliseconds(2000));

	cout << "start" << endl;

	try
	{
		int16_t msg, response;
		while (true)
		{
            msg = -7;

            serial_comm_send(msg);

            response = serial_comm_receive();

            cout << response << endl;
		}
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}

    return 0;
}


