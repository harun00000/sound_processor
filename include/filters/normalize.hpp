#pragma once

#include "ifilter.hpp"

/**
 * @brief Normalizes waveform to selected peak.
 */
class NormalizeFilter : public IFilter{
private:
    double peak_;

public:
    /**
     * @brief Creates normalize filter.
     * @param peak Peak value.
     */
    explicit NormalizeFilter(double peak = 1.0);

    /**
     * @brief Applies normalize filter.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};