#pragma once

#include <string>

#define PACKET_HEADER "UU"

class OpenIMUparser
{
public :
	OpenIMUparser();
	~OpenIMUparser();
	void newData(std::string& data);
private :
	bool _header_found;
	std::string _sync_pattern;
	std::string _frame;
	std::string _packet_code;
	uint8_t _payload_length;
	std::string _crc_s;
	bool _crc;
};