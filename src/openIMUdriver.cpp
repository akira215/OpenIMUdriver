#include "openIMUdriver.h"
#include <iostream>

OpenIMUdriver::OpenIMUdriver(): 
	_communicator(nullptr), _parser(nullptr), _rx_process(nullptr), _rx_thread(nullptr),
	_isProcessing(false),_isListening(false)
{
	
	_communicator = new SerialCom("/dev/ttyUSB0");
	
	_communicator->setBaudrate(115200);

	_parser = new OpenIMUparser();


	startCom();

	//_communicator->startThread();
	
}


OpenIMUdriver::~OpenIMUdriver(){

	stopCom();

	std::cout << "Driver Queue count :" << _rx_queue.size() << std::endl;

}

void OpenIMUdriver::startCom(){
	if (_isListening)
		return;
	
	_isProcessing = true;
	_rx_process=std::unique_ptr<std::thread>(new std::thread(&OpenIMUdriver::Process_rx, this));

	_isListening = true;
	_rx_thread=std::unique_ptr<std::thread>(new std::thread(&OpenIMUdriver::ListeningCom, this));
}

void OpenIMUdriver::stopCom()
{
	_isListening = false;
	_rx_thread->join();
	_rx_thread = nullptr;

	_isProcessing = false;
	_rx_cv.notify_one();
	_rx_process->join();
	_rx_process = nullptr;
	
}
/*
void OpenIMUdriver::ListeningCom(){

	std::byte read_buf[BUFF_SIZE];

	while (this->_isListening)
	{

		int count = _communicator->pollRx(read_buf, BUFF_SIZE);

		if(count>0) {
			std::unique_lock<std::mutex> lk(this->_rx_mutex);
			for(int i=0; i < count;i++){
				std::cout << std::hex<<static_cast<int>(read_buf[i]) << " ";
				this->_rx_queue.push(read_buf[i]);
				
			}
			this->_rx_cv.notify_one();
			std::cout << std::endl;
		}

	}

}
*/

void OpenIMUdriver::ListeningCom(){
	
	while (this->_isListening)
	{
		std::string data;

		data = _communicator->pollRx();
		//data.assign(_communicator->pollRx());


		if(!data.empty()) {
			std::unique_lock<std::mutex> lk(this->_rx_mutex);
			/*
			std::cout << "len: " << data.length()<< " data: ";
			for(char& c : data) {
				std::cout << std::hex<<static_cast<int>(c) << " ";
			}
			std::cout << " End "<< std::endl;;
			*/
			this->_rx_queue.push(data);
			this->_rx_cv.notify_one();
		}

	}

}

void OpenIMUdriver::Process_rx(){

	std::string data;

	while (this->_isProcessing)
	{
		{
			// Wait for a message to be added to the queue
			std::unique_lock<std::mutex> lk(this->_rx_mutex);
			while ((this->_rx_queue.empty())&&(this->_isProcessing))
				this->_rx_cv.wait(lk);

			if (this->_rx_queue.empty())
				continue;

			while (!_rx_queue.empty()){
				//std::cout << "queue" <<_rx_queue.front()<<std::endl;
				data.append(this->_rx_queue.front()); // copy the front element
				//data.assign(this->_rx_queue.front()); // copy the front element
				this->_rx_queue.pop();
				//this->_parser->newData(data);
			}
		}

		this->_parser->newData(data);
		data.clear();

	}

}