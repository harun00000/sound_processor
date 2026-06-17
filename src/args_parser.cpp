#include "args_parser.hpp"

#include <stdexcept>
#include <cstddef>

ArgsParser::ArgsParser(int argc, char* argv[]){
    for (size_t idx = 1; idx < argc; ++idx) 
    {
        // current argument
        std::string token = argv[idx];

        // -i filename
        if (token == "-i") 
        {
            if (idx + 1 >= argc)
            {
                throw std::runtime_error("Command line error: input file name is missing");
            }

            inputFileName_ = argv[++idx];
        }

        // -o filename
        else if (token == "-o")
        {
            if (idx + 1 >= argc) 
            {
                throw std::runtime_error("Command line error: output file name is missing");
            }

            outputFileName_ = argv[++idx];
        }

        // ex: -f ampl 0.5 -f normalize 1.0
        else if (token == "-f") 
        {
            if (idx + 1 >= argc)
            {
                throw std::runtime_error("Command line error: filter name is missing");
            }

            FilterDescriptor descriptor;
            descriptor.name = argv[++idx];

            while (idx + 1 < argc && std::string(argv[idx + 1]) != "-i" &&
                std::string(argv[idx + 1]) != "-o" && std::string(argv[idx + 1]) != "-f"){
                descriptor.arguments.push_back(argv[++idx]);
            }

            filters_.push_back(std::move(descriptor));
        }

        else 
        {
            throw std::runtime_error("Command line error: unknown token " + token);
        }
    }
}

const std::string& ArgsParser::inputFileName() const{
    return inputFileName_;
}

const std::string& ArgsParser::outputFileName() const{
    return outputFileName_;
}

const std::vector<FilterDescriptor>& ArgsParser::filters() const{
    return filters_;
}