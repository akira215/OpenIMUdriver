#include "openIMUdata.h"
#include <iostream>
#include <cstring> 	//memcpy

OpenIMUdata::OpenIMUdata() {

}

OpenIMUdata::~OpenIMUdata() {
	
}

void OpenIMUdata::newData(std::string& data){

	std::memcpy(&timeITOW, data.c_str(), sizeof(timeITOW));
	std::cout  << "timeITOW: " << timeITOW << "ms" << std::endl;
//<< "\r"


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