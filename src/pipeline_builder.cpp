#include "pipeline_builder.hpp"

#include "ampl.hpp"
#include "normalize.hpp"
#include "silence.hpp"
#include "timestretch.hpp"
#include "lowpass.hpp"
#include "sin_generator.hpp"
#include "am_generator.hpp"
#include "fm_generator.hpp"
#include "reverse.hpp"
#include "sound_cut.hpp"
#include "absolute.hpp"

#include <memory>
#include <stdexcept>

void PipelineBuilder::checkArgumentsCount(const FilterDescriptor& descriptor, size_t expected) const{
    if (descriptor.arguments.size() != expected)
    {
        throw std::runtime_error("Command line error: wrong arguments count for filter " + descriptor.name);
    }
}

Pipeline PipelineBuilder::build(const std::vector<FilterDescriptor>& descriptors) const{
    Pipeline pipeline;

    for (const auto& descriptor : descriptors) {
        // ampl case
        if (descriptor.name == "ampl") 
        {
            checkArgumentsCount(descriptor, 1);
            pipeline.addFilter(std::make_unique<AmplFilter>(toNumber<double>(descriptor.arguments[0])));
        }

        // normalize case
        else if (descriptor.name == "normalize") 
        {
            if (descriptor.arguments.empty()) 
            {
                pipeline.addFilter(std::make_unique<NormalizeFilter>());
            }

            else 
            {
                checkArgumentsCount(descriptor, 1);
                pipeline.addFilter(std::make_unique<NormalizeFilter>(toNumber<double>(descriptor.arguments[0])));
            }
        }

        // silence case
        else if (descriptor.name == "silence") 
        {
            checkArgumentsCount(descriptor, 3);

            pipeline.addFilter(std::make_unique<SilenceFilter>(descriptor.arguments[0],
                    toNumber<double>(descriptor.arguments[1]),
                    toNumber<double>(descriptor.arguments[2])));
        }

        // timestretch case
        else if (descriptor.name == "timestretch") 
        {
            checkArgumentsCount(descriptor, 1);
            pipeline.addFilter(std::make_unique<TimeStretch>(toNumber<double>(descriptor.arguments[0])));
        }

        // lowpass case
        else if (descriptor.name == "lowpass") {
            checkArgumentsCount(descriptor, 1);
            pipeline.addFilter(std::make_unique<LowpassFilter>(toNumber<size_t>(descriptor.arguments[0])));
        }

        // reverse case
        else if (descriptor.name == "reverse")
        {
            checkArgumentsCount(descriptor, 0);
            pipeline.addFilter(std::make_unique<ReverseFilter>());
        }

        // cut case
        else if (descriptor.name == "cut")
        {
            checkArgumentsCount(descriptor, 1);
            pipeline.addFilter(std::make_unique<SoundCut>(toNumber<double>(descriptor.arguments[0])));
        }

        // absolute case
        else if (descriptor.name == "absolute")
        {
            checkArgumentsCount(descriptor, 0);
            pipeline.addFilter(std::make_unique<AbsoluteFilter>());
        }

        // generators
        else if (descriptor.name == "generator") 
        {
            // no gen name
            if (descriptor.arguments.empty())
            {
                throw std::runtime_error("Command line error: generator type is missing");
            }

            // take gen type
            const std::string& generatorType = descriptor.arguments[0];

            // sin generator
            if (generatorType == "sin") 
            {
                checkArgumentsCount(descriptor, 3);

                pipeline.addFilter(
                    std::make_unique<SinGenerator>(
                        toNumber<double>(descriptor.arguments[1]),
                        toNumber<double>(descriptor.arguments[2])));
            }

            // am generator
            else if (generatorType == "am") 
            {
                checkArgumentsCount(descriptor, 6);

                pipeline.addFilter(std::make_unique<AmGenerator>(
                        toNumber<double>(descriptor.arguments[1]),
                        toNumber<double>(descriptor.arguments[2]),
                        toNumber<double>(descriptor.arguments[3]),
                        toNumber<double>(descriptor.arguments[4]),
                        toNumber<double>(descriptor.arguments[5])));
            }

            // fm generator
            else if (generatorType == "fm") 
            {
                checkArgumentsCount(descriptor, 6);

                pipeline.addFilter(std::make_unique<FmGenerator>(
                        toNumber<double>(descriptor.arguments[1]),
                        toNumber<double>(descriptor.arguments[2]),
                        toNumber<double>(descriptor.arguments[3]),
                        toNumber<double>(descriptor.arguments[4]),
                        toNumber<double>(descriptor.arguments[5])));
            }

            // unknown generator type:(
            else 
            {
                throw std::runtime_error("Command line error: unknown generator type " + generatorType);
            }
        }

        // unknown filter
        else 
        {
            throw std::runtime_error("Command line error: unknown filter " + descriptor.name);
        }
    }

    return pipeline;
}