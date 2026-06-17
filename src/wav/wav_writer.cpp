#include "wav_writer.hpp"

WavWriter::WavWriter(const std::string& fileName) : FileProcessor(fileName) {}

void WavWriter::write(const Waveform& waveform) const{
    // check path
    checkOutputFile();

    std::ofstream file(fileName_, std::ios::binary);

    // check open
    if (!file.is_open()) 
    {
        throw std::runtime_error("File writing error: output file cannot be opened");
    }

    // create dataSize in correct format
    const size_t dataSize = waveform.samples().size() * sizeof(int16_t);

    // create chunks
    const RiffChunk riffChunk = createRiffChunk(dataSize);
    const FormatChunk formatChunk = createFormatChunk();
    const DataChunk dataChunk = createDataChunk(dataSize);

    // write in file chuncks and samples
    file.write(reinterpret_cast<const char*>(&riffChunk), sizeof(riffChunk));
    file.write(reinterpret_cast<const char*>(&formatChunk), sizeof(formatChunk));
    file.write(reinterpret_cast<const char*>(&dataChunk), sizeof(dataChunk));
    file.write(reinterpret_cast<const char*>(waveform.samples().data()), static_cast<std::streamsize>(dataSize));

    if (!file){
        throw std::runtime_error("File writing error: audio data cannot be written");
    }
}

RiffChunk WavWriter::createRiffChunk(std::size_t dataSize) const{
    uint32_t chunksSize = static_cast<uint32_t>(sizeof(RiffChunk) + sizeof(FormatChunk) 
        + sizeof(DataChunk) + dataSize);

    return {
        ChunkId{'R', 'I', 'F', 'F'},

        static_cast<uint32_t>(chunksSize - 8),

        ChunkId{'W', 'A', 'V', 'E'}
    };
}

FormatChunk WavWriter::createFormatChunk() const{
    // bytes per second
    uint32_t bytesRate = Waveform::SAMPLING_RATE * Waveform::CHANNELS_COUNT
        * Waveform::NUMBER_OF_BITS_PER_SAMPLE / 8;
    
    // 
    uint16_t blockAlign = Waveform::CHANNELS_COUNT
        * Waveform::NUMBER_OF_BITS_PER_SAMPLE / 8;

    return {
        ChunkId{'f', 'm', 't', ' '},

        16,     // bytes in chank (data section)

        1,      // PCM

        Waveform::CHANNELS_COUNT,

        Waveform::SAMPLING_RATE,

        bytesRate,

        blockAlign,

        Waveform::NUMBER_OF_BITS_PER_SAMPLE
    };
}

DataChunk WavWriter::createDataChunk(std::size_t dataSize) const{
    return {
        ChunkId{'d', 'a', 't', 'a'},
        
        static_cast<uint32_t>(dataSize)
    };
}
