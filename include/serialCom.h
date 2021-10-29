#pragma once

#include <string>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <poll.h>


#define POLL_TIMEOUT 2000 //ms
#define BUFF_SIZE 512 //bytes

class SerialCom
{
public :
	SerialCom(const std::string& device = "/dev/ttyACM0");
	~SerialCom();
	void setBaudrate(uint speed);
	void readData();
	int pollRx(std::byte* buffer, size_t nbByte);
	std::string pollRx();
private:
	std::string _device_name;
	int _device_fd; // device file descriptor

	struct pollfd _ufds;
	bool _isInitialized;

};
/*
	struct termios {
	tcflag_t c_iflag;		// input mode flags 
	tcflag_t c_oflag;		// output mode flags 
	tcflag_t c_cflag;		// control mode flags
	tcflag_t c_lflag;		// local mode flags 
	cc_t c_line;			// line discipline 
	cc_t c_cc[NCCS];		// control characters 
	};

	tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	tty.c_cflag |= PARENB;  // Set parity bit, enabling parity
	
	tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	tty.c_cflag |= CSTOPB;  // Set stop field, two stop bits used in communication

	tty.c_cflag &= ~CSIZE; // Clear all the size bits, then use one of the statements below
	tty.c_cflag |= CS5; // 5 bits per byte
	tty.c_cflag |= CS6; // 6 bits per byte
	tty.c_cflag |= CS7; // 7 bits per byte
	tty.c_cflag |= CS8; // 8 bits per byte (most common)

	tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
	tty.c_cflag |= CRTSCTS;  // Enable RTS/CTS hardware flow control
	tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

	tty.c_lflag &= ~ICANON; // Disable canonical mode

	tty.c_lflag &= ~ECHO; // Disable echo
	tty.c_lflag &= ~ECHOE; // Disable erasure
	tty.c_lflag &= ~ECHONL; // Disable new-line echo

	tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl

	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	ty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
	// tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT IN LINUX)
	// tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT IN LINUX)

	tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	tty.c_cc[VMIN] = 0;


*/



