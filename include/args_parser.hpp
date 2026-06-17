#pragma once

#include <string>
#include <vector>

/**
 * @brief Struct with filter name and its' arguments.
 */
struct FilterDescriptor{
    std::string name;
    std::vector<std::string> arguments;
};

/**
 * @brief Parses command line arguments.
 */
class ArgsParser{
private:
    std::string inputFileName_;
    std::string outputFileName_;
    std::vector<FilterDescriptor> filters_;

public:
    /**
     * @brief Creates parser and parses command line.
     * @param argc Number of arguments.
     * @param argv Array with arguments.
     */
    ArgsParser(int argc, char* argv[]);

    /**
     * @brief Returns input file name.
     * @return Input file name.
     */
    const std::string& inputFileName() const;

    /**
     * @brief Returns output file name.
     * @return Output file name.
     */
    const std::string& outputFileName() const;

    /**
     * @brief Returns parsed filters.
     * @return Vector with filter descriptions.
     */
    const std::vector<FilterDescriptor>& filters() const;
};