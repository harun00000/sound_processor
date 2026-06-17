#include "wav_reader.hpp"

WavReader::WavReader(const std::string& fileName) : FileProcessor(fileName) {}

Waveform WavReader::read() const{
    // input file check
    checkInputFile();

    // for binary WAV file
    std::ifstream file(fileName_, std::ios::binary);

    // open check
    if (!file.is_open())
    {
        throw std::runtime_error("File reading error: input file cannot be read");
    }

    RiffChunk riffChunk{};
    FormatChunk formatChunk{};
    DataChunk dataChunk{};

    // fill in corresponding chunks
    file.read(reinterpret_cast<char*>(&riffChunk), sizeof(riffChunk));
    file.read(reinterpret_cast<char*>(&formatChunk), sizeof(formatChunk));

    if (!file) 
    {
        throw std::runtime_error("File reading error: WAV header cannot be read");
    }
    
    riffChunkChecker(riffChunk);
    formatChunkChecker(formatChunk);
    
    // skip extra chunks between fmt and data (for seminarist's file)
    while (true)
    {
        file.read(reinterpret_cast<char*>(&dataChunk), sizeof(dataChunk));

        if (!file.good())
        {
            throw std::runtime_error("File reading error: data header is absent");
        }

        if (dataChunk.chunkId == ChunkId{'d', 'a', 't', 'a'})
        {
            break;
        }

        file.seekg(dataChunk.chunkDataSize, std::ios::cur);
    }

    dataChunkChecker(dataChunk);
    
    Waveform waveform{};

    // fill samplesCount size = data / int16
    const size_t samplesCount = dataChunk.chunkDataSize / sizeof(int16_t);

    // allocate data for sound
    waveform.samples().resize(samplesCount);

    file.read(reinterpret_cast<char*>(waveform.samples().data()), dataChunk.chunkDataSize);
    
    if (!file) 
    {
        throw std::runtime_error("File reading error: audio data cannot be read");
    }

    return waveform;
}

void WavReader::riffChunkChecker(const RiffChunk& chunk) const{
    if (chunk.chunkId != ChunkId{'R', 'I', 'F', 'F'}) 
    {
        throw std::runtime_error("File format error: RIFF section is not found");
    }

    if (chunk.waveid != ChunkId{'W', 'A', 'V', 'E'})
    {
        throw std::runtime_error("File format error: WAVE section is not found");
    }
}

void WavReader::formatChunkChecker(const FormatChunk& chunk) const{
    if (chunk.chunkId != ChunkId{'f', 'm', 't', ' '})
    {
        throw std::runtime_error("File format error: format section is not found");
    }

    if (chunk.chunkDataSize != 16)
    {
        throw std::runtime_error("File format error: invalid format section size. Expected value: 16");
    }

    if (chunk.compressionCode != 1)
    {
        throw std::runtime_error("File format error: only PCM is supported");
    }

    if (chunk.numberOfChannels != Waveform::CHANNELS_COUNT)
    {
        throw std::runtime_error("File format error: only mono audio is supported");
    }

    if (chunk.samplingRate != Waveform::SAMPLING_RATE)
    {
        throw std::runtime_error("File format error: sampling rate must be 44100 Hz");
    }

    if (chunk.significantBitsPerSample != Waveform::NUMBER_OF_BITS_PER_SAMPLE)
    {
        throw std::runtime_error("File format error: sample size must be 16 bits");
    }
}

void WavReader::dataChunkChecker(const DataChunk& chunk) const{
    if (chunk.chunkId != ChunkId{'d', 'a', 't', 'a'})
    {
        throw std::runtime_error("File format error: data section is not found");
    }

    if (chunk.chunkDataSize % sizeof(int16_t) != 0)
    {
        throw std::runtime_error("File format error: invalid audio data size");
    }
}

