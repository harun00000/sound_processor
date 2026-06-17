#include "absolute.hpp"

#include <cstdlib>

void AbsoluteFilter::apply(Waveform& sound) const{
    for (auto& sample : sound.samples())
    {
        sample = std::abs(sample);
    }
}