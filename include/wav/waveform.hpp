#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>

/**
 * @brief Saves audio samples and format parametrs.
 */
class Waveform{
private:
    std::vector<int16_t> samples_;

public:
    static constexpr int SAMPLING_RATE = 44100;
    static constexpr int CHANNELS_COUNT = 1;
    static constexpr int NUMBER_OF_BITS_PER_SAMPLE = 16;

    /**
     * @brief Returns samples for changing.
     * @return Samples vector.
     */
    std::vector<int16_t>& samples();

    /**
     * @brief Returns samples for reading.
     * @return Constant samples vector.
     */
    const std::vector<int16_t>& samples() const;

    /**
     * @brief Returns count of samples.
     * @return Samples vector size.
     */
    size_t size() const;

    /**
     * @brief Checks if waveform is empty.
     * @return True if there are no samples.
     */
    bool empty() const;
};