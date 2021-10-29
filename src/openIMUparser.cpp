#include "openIMUparser.h"
#include "cksum.h"
#include <iostream>
#include <cstring> 	//memcpy

OpenIMUparser::OpenIMUparser():
	_header_found(false),_sync_pattern(std::string("  ")), 
	_packet_code(std::string()),_frame(std::string()),_payload_length(0),_crc_s(std::string()),_crc(false)
{

}


OpenIMUparser::~OpenIMUparser(){

}

void OpenIMUparser::newData(std::string& data){
	for(char& c : data){
		if(_header_found){
			if(_packet_code.length()<2)
				_packet_code.push_back(c);
			else{
				if(_payload_length == 0)
					_payload_length = (uint8_t)c;
				else{
					if(_frame.length()<_payload_length){
						_frame.push_back(c);
					} else {
						if (_crc_s.length()<2)
							_crc_s.push_back(c);
						else{
							//Check CRC
							uint16_t val;
							std::memcpy(&val, _crc_s.c_str(), sizeof(val));

							std::string packet(_packet_code);
							packet.push_back(_payload_length);
							packet.append(_frame);
							
							uint16_t crc = crc16(reinterpret_cast<unsigned char*>(const_cast<char*>(packet.c_str())), packet.length());
							//compute CRC
							if (crc==val)
								_crc=true;
							std::cout << "packet code :"<< _packet_code << " payload: " << (unsigned int) _payload_length
								<< " message :" << _frame
								<< " crc :" << (unsigned int) val
								<< " computed crc :" << (unsigned int) crc
								<< " checked :" << _crc << std::endl;
							_sync_pattern = "  ";
							_header_found = false;
							_packet_code.clear();
							_payload_length = 0;
							_frame.clear();
							_crc_s.clear();
							_crc = false;
						}

					}
				}
			}
			//std::cout << "header found : "<< _frame  <<std::endl;
			//std::cout << c;
			//_header_found = false;
			//_sync_pattern = "  ";
		} else { //searching header
			_sync_pattern.push_back(c);
			_sync_pattern.erase(0, 1);
			if(_sync_pattern.substr( _sync_pattern.length() - 2 ) == PACKET_HEADER){
				_header_found = true;
				std::cout <<std::endl;
			}


		}
	} // for

	/*
	std::smatch m;
	std::cout << data << '\n';
	std::cout << "header found"<< ": " << std::regex_search(data, m, _reHeader) << '\n';
	for(char& c : data) {
			//std::cout << std::hex<<static_cast<int>(c) << " ";
			std::cout << (c) << " ";
	}
	*/

}