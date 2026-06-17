#include "timestretch.hpp"
#include <cmath>

TimeStretch::TimeStretch(double factor) : factor_(factor){
    if (factor <= 0)
    {
        throw std::invalid_argument("Filter argument error: timestretch factor must be > 0");
    }
}

void TimeStretch::apply(Waveform& sound) const{
    // count newSize
    const size_t oldSize = sound.samples().size();
    const size_t newSize = static_cast<size_t>(std::round(oldSize * factor_));   

    // create new vector
    std::vector<int16_t> newSamples(newSize);

    // fill in new vector
    for (size_t idx = 0; idx < newSamples.size(); ++idx)
    {
        // find pos by formula 
        double pos = static_cast<double>(idx) / factor_;

        // count pos whole part and fractal part
        size_t wholePart = static_cast<size_t>(pos);
        double frac = pos - wholePart;

        // for last sample
        if (wholePart + 1 >= oldSize)
        {
            newSamples[idx] = sound.samples()[wholePart];
        } 
        else
        {
            // using formula of interpollution from the task
            const double value = sound.samples()[wholePart] * (1.0 - frac)
                + sound.samples()[wholePart + 1] * frac;

            newSamples[idx] = static_cast<int16_t>(value);
        }
    }
    sound.samples() = std::move(newSamples);
}