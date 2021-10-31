#pragma once

#include <string>

#define PACKET_HEADER "UU"

class OpenIMUdata
{
public :
	OpenIMUdata();
	~OpenIMUdata();
	void newData(std::string& data);
private :
	uint32_t timeITOW; //msec
	double time; // s
	float roll; // rad
	float pitch; // rad
	float xRate; // rad/s
	float yRate; // rad/s
	float zRate; // rad/s
	float xAccel; // m/s/s
	float yAccel; // m/s/s
	float zAccel; // m/s/s
	uint8_t opMode;
	uint8_t linAccSw;
	uint8_t turnSw;
};