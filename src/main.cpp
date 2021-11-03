/* simple.c or simple.cpp */
#include <iostream>
#include <string>
//#include "serialCom.h"
#include "openIMUdriver.h"

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include <chrono>
#include <thread>


int main() {

	OpenIMUdriver* driver = new OpenIMUdriver();
	std::cout << "Starting OpenIMU test ................ " <<std::endl;

	
	std::cout << "Press ESC to exit." <<std::endl;
	
	// Get stdin read without pressing enter
	struct termios old_tio, new_tio;
	tcgetattr(STDIN_FILENO, &old_tio);
	new_tio = old_tio;
	new_tio.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
	
	int userInput;
	while(true){ //Loop until Esc
		userInput = getchar();
		if (userInput == 27)
			break;
	}

	tcsetattr(STDIN_FILENO,TCSANOW,&old_tio); // restore console settings
	//std::this_thread::sleep_for(std::chrono::milliseconds(5000));


	delete driver;

	return 0;
}