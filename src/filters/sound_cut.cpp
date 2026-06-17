#include "sound_cut.hpp"

#include <algorithm>
#include <cstdint>
#include <stdexcept>

SoundCut::SoundCut(double value) : value_(value){
    if (value <= 0.0 || value > 1.0)
    {
        throw std::invalid_argument("Filter argument error: value must be in range (0, 1]");
    }
}

void SoundCut::apply(Waveform& sound) const{
    // define limit 
    const int16_t limit = static_cast<int16_t>(value_ * INT16_MAX);

    // do all samples in range [-limit, limit]
    for (auto& sample : sound.samples())
    {
        sample = std::clamp(sample, static_cast<int16_t>(-limit), limit);
    }
}