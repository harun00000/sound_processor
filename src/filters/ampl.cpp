#include "ampl.hpp"
#include <algorithm>
#include <cstdint>

AmplFilter::AmplFilter(double factor) : factor_(factor){
    if (factor < 0.0)
    {
        throw std::invalid_argument("Filter argument error: ampl factor must be non-negative");
    }
}

void AmplFilter::apply(Waveform& sound) const{
    for (int16_t& sample : sound.samples())
    {
        const double newValue = sample * factor_;
     
        // clamp(value, minValueOfDiapason, maxValueOfDiapason)
        sample = static_cast<int16_t>(std::clamp(newValue,
             static_cast<double>(INT16_MIN), static_cast<double>(INT16_MAX)));
    }
}