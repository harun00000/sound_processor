#pragma once

#include <fstream>
#include <string>

/**
 * @brief Writes messages to log file.
 */
class Logger{
private:
    std::ofstream file_;

public:
    /**
     * @brief Opens log file.
     * @param fileName Name of log file.
     */
    explicit Logger(const std::string& fileName);

    /**
     * @brief Writes message to log.
     * @param message Text message.
     */
    void log(const std::string& message);
};