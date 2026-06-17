#pragma once

#include "ifilter.hpp"

#include <string>

/**
 * @brief Inserts silence into waveform.
 */
class SilenceFilter : public IFilter{
private:
    std::string unit_;
    double start_;
    double end_;

    /**
     * @brief Converts time to sample index.
     * @param time Time.
     */
    size_t timeToSampleIndex(double time) const;

public:
    /**
     * @brief Creates silence filter.
     * @param unit Time, sec or ms.
     * @param start Start time.
     * @param end End time.
     */
    SilenceFilter(const std::string& unit, double start, double end);

    /**
     * @brief Applies silence filter.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};