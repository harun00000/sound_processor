#include "sin_generator.hpp"

#include <algorithm>
#include <cmath>

SinGenerator::SinGenerator(double frequencyHz, double durationMs) : 
    AbstractGeneratorFilter(durationMs), frequencyHz_(frequencyHz){
    if (frequencyHz < 0.0) 
    {
        throw std::invalid_argument("Filter argument error: frequency must be >= 0");
    }
}

void SinGenerator::apply(Waveform& sound) const{
    // create new samples
    std::vector<int16_t> newSamples(samplesCount());

    for (size_t idx = 0; idx < newSamples.size(); ++idx)
    {
        // using formula from task
        double time = timeByIndex(idx);
        double value = INT16_MAX * std::sin(2.0 * PI * frequencyHz_ * time);

        newSamples[idx] = static_cast<int16_t>(std::clamp(value, static_cast<double>(INT16_MIN), static_cast<double>(INT16_MAX)));
    }

    sound.samples() = std::move(newSamples);
}