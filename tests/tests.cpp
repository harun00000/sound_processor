#include <catch2/catch_test_macros.hpp>

#include "waveform.hpp"
#include "wav_reader.hpp"
#include "wav_writer.hpp"
#include "pipeline.hpp"
#include "args_parser.hpp"
#include "pipeline_builder.hpp"
#include "ampl.hpp"
#include "normalize.hpp"
#include "silence.hpp"
#include "timestretch.hpp"
#include "lowpass.hpp"
#include "sin_generator.hpp"
#include "am_generator.hpp"
#include "fm_generator.hpp"
#include "reverse.hpp"
#include "sound_cut.hpp"
#include "absolute.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

TEST_CASE("Waveform", "[Waveform]"){
    Waveform sound;
    sound.samples() = {1945, -1946, 1947};

    CHECK(sound.size() == 3);
    CHECK(sound.empty() == false);
    CHECK(sound.samples()[1] == -1946);
}

TEST_CASE("WavReader", "[WavReader]"){
    WavReader reader("unexistedFile.wav");

    CHECK_THROWS_AS(reader.read(), std::runtime_error);
}

TEST_CASE("WavWriter", "[WavWriter]"){
    Waveform sound;
    sound.samples() = {0, 1945, -1945};

    const std::string fileName = "test_output.wav";

    WavWriter writer(fileName);
    writer.write(sound);

    CHECK(std::filesystem::exists(fileName));
    std::filesystem::remove(fileName);
}

TEST_CASE("Pipeline", "[Pipeline]"){
    Waveform sound;
    sound.samples() = {-1945, 1946, -1947};

    Pipeline pipeline;
    pipeline.addFilter(std::make_unique<AbsoluteFilter>());
    pipeline.addFilter(std::make_unique<ReverseFilter>());

    pipeline.apply(sound);

    CHECK(sound.samples() == std::vector<int16_t>{1947, 1946, 1945});
}

TEST_CASE("ArgsParser", "[ArgsParser]"){
    const char* argv[] = {
        "program",
        "-i", "input.wav",
        "-o", "output.wav",
        "-f", "reverse",
        "-f", "cut", "0.5"
    };

    ArgsParser parser(10, const_cast<char**>(argv));

    CHECK(parser.inputFileName() == "input.wav");
    CHECK(parser.outputFileName() == "output.wav");
    CHECK(parser.filters().size() == 2);
    CHECK(parser.filters()[0].name == "reverse");
    CHECK(parser.filters()[1].name == "cut");
    CHECK(parser.filters()[1].arguments[0] == "0.5");
}

TEST_CASE("PipelineBuilder", "[PipelineBuilder]"){
    PipelineBuilder builder;

    std::vector<FilterDescriptor> descriptors = {
        {"unknown_filter", {}}
    };

    CHECK_THROWS_AS(builder.build(descriptors), std::runtime_error);
}

TEST_CASE("AmplFilter", "[AmplFilter]"){
    Waveform sound;
    sound.samples() = {1000, -2000, 20000};

    AmplFilter filter(2.0);
    filter.apply(sound);

    CHECK(sound.samples()[0] == 2000);
    CHECK(sound.samples()[1] == -4000);
    CHECK(sound.samples()[2] == INT16_MAX);
}

TEST_CASE("NormalizeFilter", "[NormalizeFilter]"){
    Waveform sound;
    sound.samples() = {0, 0, 0};

    NormalizeFilter filter(1.0);
    filter.apply(sound);

    CHECK(sound.samples() == std::vector<int16_t>{0, 0, 0});
}

TEST_CASE("SilenceFilter", "[SilenceFilter]"){
    Waveform sound;
    sound.samples() = {1, 2, 3};

    SilenceFilter filter("ms", 0.0, 0.0);
    filter.apply(sound);

    CHECK(sound.size() == 4);
    CHECK(sound.samples()[0] == 0);
}

TEST_CASE("TimeStretch", "[TimeStretch]"){
    Waveform sound;
    sound.samples() = {0, 100};

    TimeStretch filter(2.0);
    filter.apply(sound);

    CHECK(sound.samples() == std::vector<int16_t>{0, 50, 100, 100});
}

TEST_CASE("LowpassFilter", "[LowpassFilter]"){
    Waveform sound;
    sound.samples() = {0, 0, 300, 0, 0};

    LowpassFilter filter(3);
    filter.apply(sound);

    CHECK(sound.samples() == std::vector<int16_t>{0, 100, 100, 100, 0});
}

TEST_CASE("SinGenerator creates requested number of samples", "[SinGenerator]"){
    Waveform sound;

    SinGenerator generator(440.0, 1000.0);
    generator.apply(sound);

    CHECK(sound.size() == Waveform::SAMPLING_RATE);
}

TEST_CASE("AmGenerator", "[AmGenerator]"){
    Waveform sound;

    AmGenerator generator(0.5, 440.0, 5.0, 0.5, 100.0);
    generator.apply(sound);

    CHECK(sound.empty() == false);
}

TEST_CASE("FmGenerator", "[FmGenerator]"){
    Waveform sound;

    FmGenerator generator(0.5, 440.0, 5.0, 20.0, 100.0);
    generator.apply(sound);

    CHECK(sound.empty() == false);
}

TEST_CASE("ReverseFilter", "[ReverseFilter]"){
    Waveform sound;
    sound.samples() = {11, -22, 33, -44, 55};

    ReverseFilter filter;
    filter.apply(sound);

    CHECK(sound.samples().front() == 55);
    CHECK(sound.samples().back() == 11);
    CHECK(sound.samples()[2] == 33);
}

TEST_CASE("SoundCut", "[SoundCut]"){
    Waveform sound;
    sound.samples() = {-32000, -100, 0, 100, 32000};

    SoundCut filter(0.25);
    filter.apply(sound);

    const int16_t limit = static_cast<int16_t>(0.25 * INT16_MAX);

    CHECK(sound.samples()[0] == -limit);
    CHECK(sound.samples()[1] == -100);
    CHECK(sound.samples()[4] == limit);
}

TEST_CASE("AbsoluteFilter", "[AbsoluteFilter]"){
    Waveform sound;
    sound.samples() = {-300, -1, 0, 1, 300};

    AbsoluteFilter filter;
    filter.apply(sound);

    CHECK(sound.samples() == std::vector<int16_t>{300, 1, 0, 1, 300});
}
