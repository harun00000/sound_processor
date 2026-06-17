#pragma once

#include "ifilter.hpp"

/**
 * @brief Replaces negative samples with positive values.
 */
class AbsoluteFilter : public IFilter{
public:
    /**
     * @brief Applies absolute filter.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};