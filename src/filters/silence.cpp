#include "silence.hpp"

SilenceFilter::SilenceFilter(const std::string& unit, double start, double end) : 
    unit_(unit), start_(start), end_(end){
        if (unit != "sec" && unit != "ms") 
        {
            throw std::invalid_argument("Filter argument error: undefined value of unit");
        } 
        if (start < 0.0)
        {
            throw std::invalid_argument("Filter argument error: silence-filter start parametr must be >= 0");
        }
        if (end < start)
        {
            throw std::invalid_argument("Filter argument error: silence-filter end parametr must be >= start parametr");
        } 
};

size_t SilenceFilter::timeToSampleIndex(double time) const{
    // case with sec
    if (unit_ == "sec")
    {
        return static_cast<size_t>(time * Waveform::SAMPLING_RATE);
    }

    // case with ms
    return static_cast<size_t>(time / 1000.0 * Waveform::SAMPLING_RATE);    
}

void SilenceFilter::apply(Waveform& sound) const{
    // find start/end index and count length
    const size_t startIdx = timeToSampleIndex(start_);
    const size_t endIdx = timeToSampleIndex(end_);
    const size_t length = endIdx - startIdx + 1;

    // start insert position should be < endIdx
    const size_t insertPos = std::min(sound.samples().size(), startIdx);

    // insert 0
    sound.samples().insert(sound.samples().begin() + insertPos, length, 0);
}