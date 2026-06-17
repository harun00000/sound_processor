#pragma once

#include "ifilter.hpp"

#include <memory>
#include <vector>

/**
 * @brief Gets filters and applies them in order.
 */
class Pipeline{
private:
    std::vector<std::unique_ptr<IFilter>> filters_;

public:
    Pipeline() = default;

    /**
     * @brief Adds filter to pipeline.
     * @param filter Filter for adding.
     */
    void addFilter(std::unique_ptr<IFilter> filter);

    /**
     * @brief Applies all filters to waveform.
     * @param waveform Waveform.
     */
    void apply(Waveform& waveform) const;
};