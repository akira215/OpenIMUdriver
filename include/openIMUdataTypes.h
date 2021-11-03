#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include <map>

namespace OpenIMU{
	typedef std::variant<uint8_t, uint16_t, uint32_t, uint64_t, float, double, 
					int8_t, int16_t, int32_t, int64_t, std::string> data;


	const std::map<std::string, int> mapType = {
		{ "uint8", 0 },
		{ "uint16", 1 },
		{ "uint32", 2 },
		{ "uint64", 3 },
		{ "float", 4 },
		{ "double", 5 },
		{ "char", 6 },
		{ "int16", 7 },
		{ "int32", 8 },
		{ "int64", 9 },
		{ "string", 10 },
	};
}

class IMUData{
	public:
		IMUData(){};
		IMUData(std::string n):name(n){};
		std::string name;
		std::string unit;
		int type;
		OpenIMU::data value;
		void setType(std::string s_type){
			type = OpenIMU::mapType.at(s_type);
		}
};

