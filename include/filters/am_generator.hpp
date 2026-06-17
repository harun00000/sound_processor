#pragma once

#include "abstract_generator.hpp"

/**
 * @brief Generates am signal.
 */
class AmGenerator : public AbstractGeneratorFilter{
private:
    double amplitude_;
    double carrierHz_;
    double modulationHz_;
    double depth_;

public:
    /**
     * @brief Creates AM generator.
     * @param amplitude Amplitude.
     * @param carrierHz Carrier in Hz.
     * @param modulationHz Modulation in Hz.
     * @param depth Modulation depth.
     * @param durationMs Sound duration in ms.
     */
    AmGenerator(double amplitude, double carrierHz, double modulationHz, double depth, double durationMs);

    /**
     * @brief Generates AM samples.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};