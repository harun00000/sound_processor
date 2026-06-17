#pragma once

#include "ifilter.hpp"

static constexpr double PI = 3.141592653589793238;

/**
 * @brief Base class for audio generators.
 */
class AbstractGeneratorFilter : public IFilter{
private:
    double durationMs_;

protected:
    /**
     * @brief Creates generator with selected duration.
     * @param durationMs Signal duration in ms.
     */
    explicit AbstractGeneratorFilter(double durationMs);

    /**
     * @brief Returns number of samples.
     * @return Samples count.
     */
    size_t samplesCount() const;

    /**
     * @brief Converts sample index to time.
     * @param index Sample index.
     * @return Time in seconds.
     */
    double timeByIndex(size_t index) const;
};