#include "lowpass.hpp"

LowpassFilter::LowpassFilter(size_t windowSize): windowSize_(windowSize){
    if (windowSize < 1)
    {
        throw std::invalid_argument("Filter argument error: window size must be >= 1");
    }

    if (windowSize % 2 == 0)
    {
        throw std::invalid_argument("Filter argument error: window size must be odd");
    }
}

void LowpassFilter::apply(Waveform& sound) const{
    const auto& oldSamples = sound.samples();

    // create new samples
    std::vector<int16_t> newSamples(oldSamples.size());

    // count radius
    const int radius = static_cast<int>(windowSize_ / 2);

    for (size_t idx = 0; idx < oldSamples.size(); ++idx)
    {
        int sum = 0;
        for (int offset = -radius; offset <= radius; ++offset)
        {
            int current = static_cast<int>(idx) + offset;

            // board cases
            if (current < 0) current = 0;
            if (current >= static_cast<int>(oldSamples.size()))
                current = static_cast<int>(oldSamples.size()) - 1;
    
            sum += oldSamples[current];
        }

        newSamples[idx] = static_cast<int16_t>(sum / static_cast<int>(windowSize_));
    }

    sound.samples() = std::move(newSamples);
}
