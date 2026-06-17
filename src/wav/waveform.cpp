#include "waveform.hpp"

std::vector<int16_t>& Waveform::samples(){
    return samples_;
}

const std::vector<int16_t>& Waveform::samples() const{
    return samples_;
}

size_t Waveform::size() const{
    return samples_.size();
}

bool Waveform::empty() const{
    return samples_.empty();
}