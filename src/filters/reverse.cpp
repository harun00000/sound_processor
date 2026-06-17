#include "reverse.hpp"

#include <algorithm>

void ReverseFilter::apply(Waveform& sound) const{
    std::reverse(sound.samples().begin(), sound.samples().end());
}