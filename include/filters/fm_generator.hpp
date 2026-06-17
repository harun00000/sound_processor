#pragma once

#include "abstract_generator.hpp"

/**
 * @brief Generates fm signal.
 */
class FmGenerator : public AbstractGeneratorFilter{
private:
    double amplitude_;
    double carrierHz_;
    double modulationHz_;
    double deviationHz_;

public:
    /**
     * @brief Creates fm generator.
     * @param amplitude Amplitude.
     * @param carrierHz Carrier in Hz.
     * @param modulationHz Modulation in Hz.
     * @param deviationHz Deviation in Hz.
     * @param durationMs Sound duration in ms.
     */
    FmGenerator(double amplitude, double carrierHz, double modulationHz, double deviationHz, double durationMs);

    /**
     * @brief Generates FM samples.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};