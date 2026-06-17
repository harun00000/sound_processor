#include "file_processor.hpp"

#include <filesystem>
#include <stdexcept>

FileProcessor::FileProcessor(const std::string& fileName) : fileName_(fileName) {}

void FileProcessor::checkInputFile() const{
    // any object exists by this path
    if (!std::filesystem::exists(fileName_))
    {
        throw std::runtime_error("File reading error: input file does not exist");
    }

    // is file or not
    if (!std::filesystem::is_regular_file(fileName_))
    {
        throw std::runtime_error("File reading error: input path is not a regular file");
    }
}

void FileProcessor::checkOutputFile() const{
    // create object path, ex: "results/out.wav"
    std::filesystem::path outputPath(fileName_);

    // if directory was chosen and doesn't exist
    if (outputPath.has_parent_path() && !std::filesystem::exists(outputPath.parent_path()))
    {
        throw std::runtime_error("File writing error: output directory does not exist");
    }

    // if object has already existed and is not a file
    if (std::filesystem::exists(outputPath) && !std::filesystem::is_regular_file(outputPath))
    {
        throw std::runtime_error("File writing error: output path is not a regular file");
    }
}