#pragma once

#include "waveform.hpp"
#include "wav_chunks.hpp"
#include "file_processor.hpp"

#include <string>
#include <fstream>

/**
 * @brief Writes waveform to WAV file.
 */
class WavWriter : public FileProcessor{
private:
    /**
     * @brief Creates RIFF chunk for output WAV file.
     * @param dataSize Size of audio data (in bytes).
     */
    RiffChunk createRiffChunk(std::size_t dataSize) const;

    /**
     * @brief Creates format chunk for output WAV file.
     */
    FormatChunk createFormatChunk() const;

    /**
     * @brief Creates data chunk for output WAV file.
     * @param dataSize Size of audio data (in bytes).
     */
    DataChunk createDataChunk(std::size_t dataSize) const;

public:
    /**
     * @brief Creates writer for output file.
     * @param fileName Output file name.
     */
    explicit WavWriter(const std::string& fileName);

    /**
     * @brief Writes waveform samples to output file.
     * @param waveform Waveform for writing.
     */
    void write(const Waveform& waveform) const;
};