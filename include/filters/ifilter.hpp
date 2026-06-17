#pragma once

#include "waveform.hpp"
#include <stdexcept>

/**
 * @brief Base interface for all filters.
 */
class IFilter {
public:
    virtual ~IFilter() = default;

    /**
     * @brief Applies filter to waveform.
     * @param waveform Waveform.
     */
    virtual void apply(Waveform& waveform) const = 0;
};