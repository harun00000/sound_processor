#pragma once

#include <ifilter.hpp>

/**
 * @brief Multiplies waveform samples by factor.
 */
class AmplFilter : public IFilter{
private:
    double factor_;

public:
    /**
     * @brief Creates ampl filter.
     * @param factor Multiplier for samples.
     */
    explicit AmplFilter(double factor);

    /**
     * @brief Applies ampl filter.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};