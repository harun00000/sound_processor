#include "logger.hpp"

Logger::Logger(const std::string& fileName) : file_(fileName){
    if (!file_.is_open())
    {
        throw std::runtime_error("Logger error: cannot open log file");
    }
}

void Logger::log(const std::string& message)
{
    file_ << message << '\n';
}