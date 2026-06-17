#include "abstract_generator.hpp"
#include <cmath>

AbstractGeneratorFilter::AbstractGeneratorFilter(double durationMs) : durationMs_(durationMs){
    if (durationMs < 0.0) 
    {
        throw std::invalid_argument("Filter argument error: duration must be >= 0");
    }
}

size_t AbstractGeneratorFilter::samplesCount() const{
    // ms to sec and multiply on rate
    return (static_cast<size_t>(std::round(durationMs_ / 1000.0 * Waveform::SAMPLING_RATE)));
}

double AbstractGeneratorFilter::timeByIndex(std::size_t index) const{
    // by task
    return (static_cast<double>(index) / Waveform::SAMPLING_RATE);  
}