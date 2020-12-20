#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>

enum class LogType
{
	LOG_TYPE_NORMAL,
	LOG_TYPE_POSITIVE,
	LOG_TYPE_WARNING
};

class ServerLogger
{
public:
	void Log(std::string val) {
		Log(val, LogType::LOG_TYPE_NORMAL);
	}
	void Log(std::string val, LogType type) {
		switch (type) {
		case LogType::LOG_TYPE_NORMAL:
			std::cout << val << std::endl;
			break;
		case LogType::LOG_TYPE_POSITIVE:
			std::cout << "[+]: " << val << std::endl;
			break;
		case LogType::LOG_TYPE_WARNING:
			std::cout << "[!]: " << val << std::endl;
			break;
		}
	}
} Logger;
#endif