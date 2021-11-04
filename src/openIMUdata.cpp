#include "openIMUdata.h"
#include <json.hpp>
#include <fstream>	// std::ifstream
#include <iostream>
#include <cstring> 	//memcpy

using json = nlohmann::json;

OpenIMUdata::OpenIMUdata() {

}

OpenIMUdata::~OpenIMUdata() {
	clearData();	
}

void OpenIMUdata::clearData(){
	// delete old objects
	for (IMUData* el : _data_vector) {
		delete el;
		el=nullptr;
	}
	_data_vector.clear();
	_data_map.clear();
}

void OpenIMUdata::setPacketType(std::string& packetType){
	// read a JSON file
	std::ifstream i(CONFIG_FILE);
	json j;
	i >> j;

	for(const auto& packetDesc : j[USER_MESSAGES][OUTPUT_PACKETS] ){
		if(packetDesc["name"]==packetType){
			
			// delete old objects
			clearData();

			// create new data vector
			for(const auto& payloadDesc : packetDesc["payload"] ){
				std::cout << payloadDesc <<std::endl;
				IMUData* newItem = new IMUData();
				newItem->name = payloadDesc["name"];
				newItem->unit = payloadDesc["unit"];
				newItem->setType(payloadDesc["type"]);
				//newItem->setSize(payloadDesc["type"]);
				std::cout << newItem->name << " type: " << newItem->type
						<< " size: "<< newItem->size <<std::endl;
				// Store in 2 containers
				_data_vector.push_back(newItem);
				_data_map[newItem->name] = newItem;
				
			}
		}
	}
	//std::cout << "json" << j[USER_MESSAGES][OUTPUT_PACKETS] <<std::endl;
}

void OpenIMUdata::newData(std::string& data){
	//auto it = data.begin();
	const char* str = data.c_str();

	for (IMUData* el : _data_vector) {

		//std::memcpy(value, &(*it), el->size);
		//el->setValue(&(*it));
		//std::advance(it, el->size);
		el->setValue(str);
		str += el->size;
		
		std::cout  << el->name << ": ";
		std::visit([](const auto &x) { std::cout << x; }, el->value);
		std::cout << " " << el->unit << std::endl;
		
	}
/*
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
	std::cout  << " - pitch: " << pitch << "rad";
	std::advance(it,sizeof(pitch));
	
	std::cout << "\r";
	*/


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