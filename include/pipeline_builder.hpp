#pragma once

#include "args_parser.hpp"
#include "pipeline.hpp"

#include <string>
#include <vector>

/**
 * @brief Creates pipeline from filter descriptions.
 */
class PipelineBuilder{
private:
    /**
     * @brief Gets string and converst to selected number type.
     * @param value String from command line.
     */
    template <typename T>
    T toNumber(const std::string& value) const;

    /**
     * @brief Checks count of filter arguments.
     * @param descriptor Filter descriptor.
     * @param expected Expected arguments count.
     */
    void checkArgumentsCount(const FilterDescriptor& descriptor, size_t expected) const;

public:
    /**
     * @brief Builds pipeline with filters.
     * @param descriptors List of filter descriptions.
     * @return Pipeline.
     */
    Pipeline build(const std::vector<FilterDescriptor>& descriptors) const;
};

template <>
inline double PipelineBuilder::toNumber<double>(const std::string& value) const{
    try
    {
        return std::stod(value);
    }
    catch (...)
    {
        throw std::runtime_error("Command line error: cannot convert argument to double");
    }
}

template <>
inline size_t PipelineBuilder::toNumber<size_t>(const std::string& value) const{
    try
    {
        return static_cast<size_t>(std::stoul(value));
    }
    catch (...)
    {
        throw std::runtime_error("Command line error: cannot convert argument to integer");
    }
}