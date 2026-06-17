#pragma once

#include "ifilter.hpp"

/**
 * @brief Reverses waveform samples.
 */
class ReverseFilter : public IFilter{
public:
    /**
     * @brief Applies reverse filter.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};