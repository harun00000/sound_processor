#pragma once

#include "abstract_generator.hpp"

/**
 * @brief Generates sin wave.
 */
class SinGenerator : public AbstractGeneratorFilter{
private:
    double frequencyHz_;

public:
    /**
     * @brief Creates sin generator.
     * @param frequencyHz Sin frequency (in Hz).
     * @param durationMs Sound duration in ms.
     */
    SinGenerator(double frequencyHz, double durationMs);

    /**
     * @brief Generates sin samples.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};