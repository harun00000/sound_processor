#pragma once

#include "ifilter.hpp"

/**
 * @brief Changes waveform by moving average window.
 */
class LowpassFilter : public IFilter{
private:
    size_t windowSize_;

public:
    /**
     * @brief Creates lowpass filter.
     * @param windowSize Size of window.
     */
    explicit LowpassFilter(std::size_t windowSize);

    /**
     * @brief Applies lowpass filter.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};