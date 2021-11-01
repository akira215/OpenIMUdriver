#include "openIMUdata.h"
#include <json.hpp>
#include <fstream>	// std::ifstream
#include <iostream>
#include <cstring> 	//memcpy

using json = nlohmann::json;

OpenIMUdata::OpenIMUdata() {

}

OpenIMUdata::~OpenIMUdata() {
	
}

void OpenIMUdata::setPacketType(std::string& packetType){
	// read a JSON file
	std::ifstream i("../openimu.json");
	json j;
	i >> j;
	std::cout << "json" << j <<std::endl;
}

void OpenIMUdata::newData(std::string& data){
	auto it = data.begin();

	std::memcpy(&timeITOW, &(*it), sizeof(timeITOW));
	std::cout  << "timeITOW: " << timeITOW << "ms";
	std::advance(it,sizeof(timeITOW));

	std::memcpy(&time, &(*it), sizeof(time));
	std::cout  << " - time: " << time << "s";
	std::advance(it,sizeof(time));

	std::memcpy(&roll, &(*it), sizeof(roll));
	std::cout  << " - roll: " << roll << "rad";
	std::advance(it,sizeof(roll));

	std::memcpy(&pitch, &(*it), sizeof(pitch));
	std::cout  << " - roll: " << roll << "rad";
	std::advance(it,sizeof(pitch));
	
	std::cout << "\r";


}
void OpenIMUdata::error(const std::string& msg){
	std::cout << msg <<std::endl;
}
/*
"type": "uint32",
						"name": "timeITOW",
						"unit": "msec"
					},
					{
						"type": "double",
						"name": "time",
						"unit": "s"
					},
					{
						"type": "float",
						"name": "roll",
						"unit": "rad"
					},
					{
						"type": "float",
						"name": "pitch",
						"unit": "rad"
					},
					{
						"type": "float",
						"name": "xRate",
						"unit": "rad/s"
					},
					{
						"type": "float",
						"name": "yRate",
						"unit": "rad/s"
					},
					{
						"type": "float",
						"name": "zRate",
						"unit": "rad/s"
					},
					{
						"type": "float",
						"name": "xAccel",
						"unit": "m/s/s"
					},
					{
						"type": "float",
						"name": "yAccel",
						"unit": "m/s/s"
					},
					{
						"type": "float",
						"name": "zAccel",
						"unit": "m/s/s"
					},
					{
						"type": "uint8",
						"name": "opMode",
						"unit": "unitless"
					},
					{
						"type": "uint8",
						"name": "linAccSw",
						"unit": "unitless"
					},
					{
						"type": "uint8",
						"name": "turnSw",
						"unit": "unitless"
					}
				],
*/