#pragma once

#include <string>
#include <variant>
#include <map>

#define PACKET_HEADER "UU"

typedef std::variant<uint8_t, uint16_t, uint32_t, uint64_t, float, double, 
				int8_t, int16_t, int32_t, int64_t, std::string> dataVariant;

class OpenIMUdata
{
public :
	OpenIMUdata();
	~OpenIMUdata();
	void newData(std::string& data);
	void setPacketType(std::string& packetType);
	void error(const std::string& msg);
private :
	std::map<std::string, dataVariant> _datas;

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