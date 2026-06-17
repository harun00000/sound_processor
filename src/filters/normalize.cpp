#include "normalize.hpp"
#include <cstdint>

NormalizeFilter::NormalizeFilter(double peak) : peak_(peak){
    if (peak < 0.0 || peak > 1.0)
    {
        throw std::invalid_argument("Filter argument error: peak must be in range [0, 1]");
    }
}

void NormalizeFilter::apply(Waveform& sound) const{
    int16_t curPeak = 0;

    // find max by module
    for (const auto& sample : sound.samples())
    {
        curPeak = std::max(curPeak, static_cast<int16_t>(std::abs(sample)));
    }

    if (curPeak == 0) return;

    // by task
    const double scale = peak_ * 32767 / curPeak;

    // apply to every el of samples
    for (auto& sample : sound.samples())
    {
        sample = static_cast<int16_t>(sample * scale);
    }
}