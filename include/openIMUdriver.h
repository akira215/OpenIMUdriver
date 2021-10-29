#pragma once

#include "serialCom.h"
#include "openIMUparser.h"
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

class OpenIMUdriver
{
public :
	OpenIMUdriver();
	~OpenIMUdriver();
	void startCom();
	void stopCom();
private:
	void Process_rx();
	void ListeningCom();
	SerialCom* _communicator;
	OpenIMUparser* _parser;
	std::queue<std::string> _rx_queue;
	std::mutex _rx_mutex;
	std::condition_variable _rx_cv;
	std::unique_ptr<std::thread> _rx_process;
	std::unique_ptr<std::thread> _rx_thread;
	std::atomic<bool> _isProcessing;
	std::atomic<bool> _isListening;
};