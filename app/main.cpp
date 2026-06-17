#include "args_parser.hpp"
#include "pipeline_builder.hpp"
#include "wav_reader.hpp"
#include "wav_writer.hpp"
#include "logger.hpp"

#include <exception>
#include <filesystem>
#include <iostream>
#include <string>

int main(int argc, char* argv[]){
    try 
    {
        Logger logger("log.txt");
        logger.log("Program started");

        ArgsParser parser(argc, argv);
        logger.log("Arguments parsed");

        Waveform sound;

        if (!parser.inputFileName().empty()) 
        {
            WavReader reader(parser.inputFileName());
            sound = reader.read();
            logger.log("Waveform loaded");
        }

        PipelineBuilder builder;
        Pipeline pipeline = builder.build(parser.filters());
        logger.log("Pipeline built");

        for (const auto& filter : parser.filters())
        {
            logger.log("Filter added: " + filter.name);
        }

        pipeline.apply(sound);
        logger.log("Audio processing completed");

        if (!parser.outputFileName().empty()) 
        {
            if (std::filesystem::exists(parser.outputFileName()))
            {
                std::cout << "Output file already exists. Overwrite? (y/n): ";

                char answer;
                std::cin >> answer;

                if (answer != 'y' && answer != 'Y')
                {
                    logger.log("Output file overwrite cancelled");
                    return 0;
                }

                logger.log("Output file overwrite confirmed");
            }

            WavWriter writer(parser.outputFileName());
            writer.write(sound);
            logger.log("Waveform saved");
        }

        logger.log("Program finished");
        return 0;
    }
    catch(const std::exception& error) 
    {
        Logger logger("log.txt");
        logger.log(std::string("ERROR: ") + error.what());

        std::cerr << error.what() << '\n';
        return 1;
    }
}