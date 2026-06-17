#pragma once

#include "ifilter.hpp"

/**
 * @brief Changes waveform samples by amplitude limit.
 */
class SoundCut : public IFilter{
private:
    double value_;

public:
    /**
     * @brief Creates sound cut filter.
     * @param value Limit coefficient in range (0, 1].
     */
    explicit SoundCut(double value);

    /**
     * @brief Applies sound cut filter.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};