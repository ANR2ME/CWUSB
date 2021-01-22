#pragma once
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

class Timer {
    private:
        std::chrono::steady_clock::time_point mStartTime{};
        std::stringstream mLogFile{};
        
    public: 
        void Start();
        void Stop(const std::string& aName);
};

