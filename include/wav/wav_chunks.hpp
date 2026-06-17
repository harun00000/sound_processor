#pragma once

#include <cstdint>
#include <array>

using ChunkId = std::array<char, 4>;

/**
 * @brief RIFF chunk of WAV file.
 */
struct __attribute__((packed)) RiffChunk{
    ChunkId chunkId;           // "RIFF"
    uint32_t chunkDataSize;    // file size - 8 bytes (by task, 88236)
    ChunkId waveid;            // "WAVE"
};  

/**
 * @brief Format chunk of WAV file.
 */
struct __attribute__((packed)) FormatChunk{
    ChunkId chunkId;           // "fmt "
    uint32_t chunkDataSize;    // bytes in chunk (16) (data section)

    uint16_t compressionCode;  // 1 = PCM
    uint16_t numberOfChannels; // 1 

    uint32_t samplingRate;     // 44100 Hz
    uint32_t byteRate;         // bytes per second

    uint16_t blockAlign;       // bytes per sample
    uint16_t significantBitsPerSample; // 16
};

/**
 * @brief Data chunk of WAV file.
 */
struct __attribute__((packed)) DataChunk{
    ChunkId chunkId;           // "data"
    uint32_t chunkDataSize;    // size of data section(88200)
};
