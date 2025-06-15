/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.h
Project:    CS230 Engine
Author:     Jeonghun Byeon
Created:    March 16, 2025
*/
#pragma once
#include <string>
#include <fstream>
#include <raylib.h>
#include <chrono>
namespace CS230 {
    class Logger {
    public:
        enum class Severity {
            Verbose,  
            Debug,    
            Event,    
            Error
        };
        Logger(Severity severity, bool use_console, std::chrono::system_clock::time_point paramstart);

        ~Logger();
        void LogError(std::string text) {
            log(Severity::Error, text);
        }
        void LogEvent(std::string text) {
            log(Severity::Event, text);
        }
        void LogDebug(std::string text) {
            log(Severity::Debug, text);
        }
        void LogVerbose(std::string text) {
            log(Severity::Verbose, text);
        }
    private:
        Severity min_level;
        std::ofstream out_stream;
        std::chrono::system_clock::time_point start_time;
        double seconds_since_start() const {
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            return  std::chrono::duration<double>(now - start_time).count();
        }
        void log(Severity severity, std::string message);
    };
}