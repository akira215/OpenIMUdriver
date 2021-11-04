#pragma once

#include "openIMUdataTypes.h"
#include <map>
#include <string>
#include <vector>

#define CONFIG_FILE "../openimu.json" //TODO move that !

#define USER_MESSAGES "userMessages"
#define OUTPUT_PACKETS "outputPackets"


//typedef std::variant<uint8_t, uint16_t, uint32_t, uint64_t, float, double, 
//				int8_t, int16_t, int32_t, int64_t, std::string> dataVariant;

class OpenIMUdata
{
public :
/*
	inline constexpr static std::string _types[] = {
		"uchar", "uint16", "uint32", "uint64", "float", "double", "char","int16","int32","int64", "string"
	};
	*/

	OpenIMUdata();
	~OpenIMUdata();
	void newData(std::string& data);
	void setPacketType(std::string& packetType);
	void error(const std::string& msg);
private :
	void clearData();
	std::vector<IMUData*> _data_vector;			// each data pointer is stored twice
	std::map<std::string, IMUData*> _data_map; // key :name of data / value 

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