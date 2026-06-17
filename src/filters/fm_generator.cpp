#include "fm_generator.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <vector>

FmGenerator::FmGenerator(double amplitude, double carrierHz, double modulationHz, double deviationHz, double durationMs)
    : AbstractGeneratorFilter(durationMs), amplitude_(amplitude), 
    carrierHz_(carrierHz), modulationHz_(modulationHz), deviationHz_(deviationHz){

    if (amplitude < 0.0 || amplitude > 1.0)
    {
        throw std::invalid_argument("Filter argument error: amplitude must be in range [0, 1]");
    }

    if (carrierHz < 0.0)
    {
        throw std::invalid_argument("Filter argument error: carrier frequency must be >= 0");
    }

    if (modulationHz <= 0.0)
    {
        throw std::invalid_argument("Filter argument error: modulation frequency must be > 0");
    }

    if (deviationHz < 0.0)
    {
        throw std::invalid_argument("Filter argument error: deviation frequency must be >= 0");
    }
}

void FmGenerator::apply(Waveform& sound) const{
    // create new samples
    std::vector<int16_t> newSamples(samplesCount());

    for (std::size_t idx = 0; idx < newSamples.size(); ++idx)
    {
        // using formulas from task
        const double time = timeByIndex(idx);
        const double phase = 2.0 * PI * carrierHz_ * time
            + (deviationHz_ / modulationHz_) * std::sin(2.0 * PI * modulationHz_ * time);

        const double value = amplitude_ * INT16_MAX * std::sin(phase);

        newSamples[idx] = static_cast<int16_t>(
            std::clamp(value, static_cast<double>(INT16_MIN), static_cast<double>(INT16_MAX)));
    }

    sound.samples() = std::move(newSamples);
}