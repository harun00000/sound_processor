#include "am_generator.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <vector>

AmGenerator::AmGenerator(double amplitude, double carrierHz, double modulationHz, double depth, double durationMs)
    : AbstractGeneratorFilter(durationMs), amplitude_(amplitude), 
    carrierHz_(carrierHz), modulationHz_(modulationHz), depth_(depth){

    if (amplitude < 0.0 || amplitude > 1.0) 
    {
        throw std::invalid_argument("Filter argument error: amplitude must be in range [0, 1]");
    }

    if (carrierHz < 0.0) 
    {
        throw std::invalid_argument("Filter argument error: carrier frequency must be >= 0");
    }

    if (modulationHz < 0.0) 
    {
        throw std::invalid_argument("Filter argument error: modulation frequency must be >= 0");
    }

    if (depth < 0.0 || depth > 1.0) 
    {
        throw std::invalid_argument("Filter argument error: depth must be in range [0, 1]");
    }
}

void AmGenerator::apply(Waveform& sound) const{
    // create new samples
    std::vector<int16_t> newSamples(samplesCount());

    for (std::size_t idx = 0; idx < newSamples.size(); ++idx) 
    {
        // using formulas from task 
        const double time = timeByIndex(idx);
        const double envelope = 1.0 + depth_ * std::sin(2.0 * PI * modulationHz_ * time);
        const double carrier = std::sin(2.0 * PI * carrierHz_ * time);
        const double value = amplitude_ * INT16_MAX * envelope * carrier;

        newSamples[idx] = static_cast<int16_t>(std::clamp(value, 
            static_cast<double>(INT16_MIN), static_cast<double>(INT16_MAX)));
    }

    sound.samples() = std::move(newSamples);
}