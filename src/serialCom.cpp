#include "serialCom.h"
#include <iostream>
#include <cstring>

SerialCom::SerialCom( const std::string& device): 
	_device_name(device), _device_fd(0), _isInitialized(false)
	
{
	_device_fd = open(_device_name.c_str(), O_RDWR);

	// Check for errors
	if (_device_fd < 0) {
		std::cout << "Error " <<  errno <<" opening serial port: "<< std::strerror(errno) << std::endl;
	} else {
		std::cout << "Port " << _device_name << " opened." <<std::endl;
		_isInitialized = true;
		//Set up poll file descriptors.
		_ufds.fd = _device_fd;		//Attach socket to watch.
		_ufds.events = POLLIN;	//Set events to notify on.
	}
/*
	struct termios tty ;
	if(isInitialized){
		// get the configuration of the serial port
		if(tcgetattr(_serial_port, &tty) != 0) {
			std::cout << "Error " <<  errno <<" from tcgetattr: "<< std::strerror(errno) << std::endl;
		}
	}

	if (tcsetattr(_serial_port, TCSANOW, &tty) != 0)
		std::cout << "Error " <<  errno <<" from tcsetattr: "<< std::strerror(errno) << std::endl;


	*/
}

SerialCom::~SerialCom() {

	if (close(_device_fd)!=0) {
		std::cout << "Error " <<  errno <<" closing serial port: "<< std::strerror(errno) << std::endl;
	} else {
		std::cout << "Port " << _device_name << " closed." <<std::endl;
	}
	_isInitialized = false;
}

void SerialCom::setBaudrate(uint speed){
	struct termios tty ;

	if(!_isInitialized)
		return;
	if(tcgetattr(_device_fd, &tty) != 0) {
		std::cout << "Error " <<  errno <<" from tcgetattr: "<< std::strerror(errno) << std::endl;
		return;
	}

	switch(speed) {
	case 9600:
		cfsetispeed(&tty, B9600);
		cfsetospeed(&tty, B9600);
		break;
	case 19200:
		cfsetispeed(&tty, B19200);
		cfsetospeed(&tty, B19200);
		break;
	case 38400:
		cfsetispeed(&tty, B38400);
		cfsetospeed(&tty, B38400);
		break;
	case 57600:
		cfsetispeed(&tty, B57600);
		cfsetospeed(&tty, B57600);
		break;
	case 115200:
		cfsetispeed(&tty, B115200);
		cfsetospeed(&tty, B115200);
		break;
	default:
		std::cout << "Speficied Baurate not available, setting to 9600 " << std::endl;
		cfsetispeed(&tty, B9600);
		cfsetospeed(&tty, B9600);
	}

	if (tcsetattr(_device_fd, TCSANOW, &tty) != 0)
		std::cout << "Error " <<  errno <<" from tcsetattr: "<< std::strerror(errno) << std::endl;
}

void SerialCom::readData(){
	char read_buf [256];

	// Read bytes. The behaviour of read() (e.g. does it block?,
	// how long does it block for?) depends on the configuration
	// settings above, specifically VMIN and VTIME
	int n = read(_device_fd , &read_buf, sizeof(read_buf));
	std::cout << read_buf << std::endl;


}

// poll the port and populate buffer with data read, the method return the length of the populated array
int SerialCom::pollRx(std::byte* buffer,size_t nbByte){

	if(!_isInitialized)
		return -1;

	int res = 0;
	//Poll socket for data.
	res = poll(&this->_ufds, 1, POLL_TIMEOUT);

	if (res > 0) { 

		//data received, read the device file
		int count  = read(this->_device_fd , buffer, nbByte);
		//If buffer is filled
		if (count > 0) {
			//Pad end of buffer to ensure there is a termination symbol.
			//buffer[res] = std::byte {0};


			return count;

		} else if (count < 0) {
			//Inform user and exit thread.
			std::cout <<this->_device_name
				<< " disconnected, exiting Thread" << std::endl;
			return -1;
		}

	} else if (res == 0) {
		//Inform user and exit thread.
		std::cout << "Error: no data received on port " << this->_device_name
				<< " after " << POLL_TIMEOUT <<" ms. Exiting Thread" << std::endl;
		return res;
	} else if (res < 0) {
		//Inform user and exit thread.
		std::cout << "Error " <<  errno <<" during poll: "<< std::strerror(errno) << std::endl;
		return res;
	}

	return 0;

}

// poll the port and populate buffer with data read, the method return the length of the populated array
std::string SerialCom::pollRx(){

	if(!this->_isInitialized)
		return std::string();


	int res = 0;
	//Poll socket for data.
	res = poll(&this->_ufds, 1, POLL_TIMEOUT);

	if (res > 0) { 

		char buffer[BUFF_SIZE];

		//data received, read the device file
		int count  = read(this->_device_fd , &buffer, sizeof(buffer));
		//If buffer is filled
		if (count > 0) {
			//Pad end of buffer to ensure there is a termination symbol.
			//buffer[count] = '\0';


			return std::string(buffer, count);

		} else if (count < 0) {
			//Inform user and exit thread.
			std::cout <<this->_device_name
				<< " disconnected, exiting Thread" << std::endl;
			return std::string();
		}

	} else if (res == 0) {
		//Inform user and exit thread.
		std::cout << "Error: no data received on port " << this->_device_name
				<< " after " << POLL_TIMEOUT <<" ms. Exiting Thread" << std::endl;
		return std::string();
	} else if (res < 0) {
		//Inform user and exit thread.
		std::cout << "Error " <<  errno <<" during poll: "<< std::strerror(errno) << std::endl;
		return std::string();
	}

	return std::string();

}


