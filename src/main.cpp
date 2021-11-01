/* simple.c or simple.cpp */
#include <iostream>
#include <string>
//#include "serialCom.h"
#include "openIMUdriver.h"

#include <chrono>
#include <thread>


int main() {
	//SerialCom* com = new SerialCom("/dev/ttyUSB0");
	
	//com->setBaudrate(115200);
	/*
	for (int i=1;i<100;++i)
		com->readData();
		*/
	//com->startThread();
	OpenIMUdriver* driver = new OpenIMUdriver();
	std::cout << "Hello, World! " <<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	//com->stopThread();

	delete driver;
	//delete com;
	return 0;
}