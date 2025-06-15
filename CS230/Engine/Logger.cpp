/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.cpp
Project:    CS230 Engine
Author:     Jeonghun Byeon
Created:    March 3, 2025
Updated:    March 14, 2025
*/

#include <array>
#include <iostream>
#include "Logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool use_console, std::chrono::system_clock::time_point paramstart) : min_level(severity), out_stream("Trace.log"), start_time(paramstart) {
	SetTraceLogLevel(LOG_NONE);
	if (use_console == true) {
		out_stream.set_rdbuf(std::cout.rdbuf());
	}
}

CS230::Logger::~Logger() {
	out_stream.flush();
	out_stream.close();
}

void CS230::Logger::log(Severity severity, std::string message) {
	const char* SevStr[] = { "Verbose", "Debug", "Event", "Error" };
	if ((severity >= min_level) && ((static_cast<int>(severity) <= 3))) {
		out_stream.precision(4);
		out_stream << '[' << std::fixed << seconds_since_start() << "]\t";
		out_stream << SevStr[static_cast<int>(severity)] << "\t" << message << std::endl;
	}
	return;
}