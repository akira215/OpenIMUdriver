#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include <map>

namespace OpenIMU{
	typedef std::variant<uint8_t, uint16_t, uint32_t, uint64_t, float, double, 
					int8_t, int16_t, int32_t, int64_t, std::string> io_value;


	const std::map<std::string, int> mapType = {
		{ "uint8", 0 },
		{ "char8", 0},
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

	const std::map<std::string, uint> mapSize = {
		{ "uint8", 1 },
		{ "char8", 1 },
		{ "uint16", 2 },
		{ "uint32", 4 },
		{ "uint64", 8 },
		{ "float", 4 },
		{ "double", 8 },
		{ "char", 1 },
		{ "int16", 2 },
		{ "int32", 4 },
		{ "int64", 8 },
		{ "string", 8 },
	};
}

class IMUData{
public:
	IMUData(){};
	IMUData(std::string n):name(n){};
	std::string name;
	std::string unit;
	int type;	// type shall be in line with typedef OpenIMU::data variant declaration
	uint size; // size in bytes
	OpenIMU::io_value value;
	void setType(std::string s_type){
		type = OpenIMU::mapType.at(s_type);
		size = OpenIMU::mapSize.at(s_type);
	}
	void setSize(std::string s_size){
		size = OpenIMU::mapSize.at(s_size);
	}

	void setValue(const char* buffer){
		switch (type){
			case 0 : value = read_object<uint8_t>(buffer);
					break;
			case 1 : value = read_object<uint16_t>(buffer);
					break;
			case 2 : value = read_object<uint32_t>(buffer);
					break;
			case 3 : value = read_object<uint64_t>(buffer);
					break;
			case 4 : value = read_object<float>(buffer);
					break;
			case 5 : value = read_object<double>(buffer);
					break;
			case 6 : value = read_object<int8_t>(buffer);
					break;
			case 7 : value = read_object<int16_t>(buffer);
					break;
			case 8 : value = read_object<int32_t>(buffer);
					break;
			case 9 : value = read_object<int64_t>(buffer);
					break;
		}
	}

private:
	template<typename T>
	T read_object(const char *buffer) {
		T val = *reinterpret_cast<const T*>(buffer);
		return val;
	}
};

