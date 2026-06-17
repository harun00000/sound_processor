#pragma once

#include <string>

/**
 * @brief Base class for file path checks (for WavReader and WavWriter).
 */
class FileProcessor{
protected:
    std::string fileName_;

    /**
     * @brief Creates file processor.
     * @param fileName File name.
     */
    explicit FileProcessor(const std::string& fileName);

    /**
     * @brief Checks input file before reading.
     */
    void checkInputFile() const;

    /**
     * @brief Checks output file before writing.
     */
    void checkOutputFile() const;
};