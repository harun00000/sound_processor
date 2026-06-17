#pragma once

#include "waveform.hpp"
#include "wav_chunks.hpp"
#include "file_processor.hpp"

#include <string>
#include <fstream>

/**
 * @brief Reads WAV file and creates waveform.
 */
class WavReader : public FileProcessor{
private:
    /**
     * @brief Checks RIFF chunk format.
     * @param chunk RIFF chunk.
     */
    void riffChunkChecker(const RiffChunk& chunk) const;

    /**
     * @brief Checks format chunk format.
     * @param chunk Format chunk.
     */
    void formatChunkChecker(const FormatChunk& chunk) const;

    /**
     * @brief Checks data chunk format.
     * @param chunk Data chunk.
     */
    void dataChunkChecker(const DataChunk& chunk) const;

public:
    /**
     * @brief Creates WAV reader.
     * @param fileName Input file name.
     */
    explicit WavReader(const std::string& fileName);

    /**
     * @brief Reads samples from WAV file.
     * @return Waveform with samples.
     */
    Waveform read() const;
};