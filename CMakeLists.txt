cmake_minimum_required(VERSION 3.22)
project(sound_processor)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Werror=return-type")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(sound_processor_lib
    src/wav/waveform.cpp
    src/wav/wav_reader.cpp
    src/wav/wav_writer.cpp
    src/pipeline.cpp
    src/args_parser.cpp
    src/pipeline_builder.cpp
    src/filters/ampl.cpp
    src/filters/normalize.cpp
    src/filters/silence.cpp
    src/filters/timestretch.cpp
    src/filters/lowpass.cpp
    src/filters/abstract_generator.cpp
    src/filters/sin_generator.cpp
    src/filters/am_generator.cpp
    src/filters/fm_generator.cpp
    src/filters/reverse.cpp
    src/filters/sound_cut.cpp
    src/filters/absolute.cpp
    src/logger.cpp
    src/wav/file_processor.cpp
)

target_include_directories(sound_processor_lib
    PUBLIC 
    include
    include/wav
    include/filters
)

add_executable(sound_processor
    app/main.cpp
)

target_link_libraries(sound_processor PRIVATE sound_processor_lib)

if (BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)

    enable_testing()

    add_executable(tests
        tests/tests.cpp
    )

    target_include_directories(tests PRIVATE include)

    target_link_libraries(tests
        PRIVATE
        Catch2::Catch2WithMain
        sound_processor_lib
    )

    add_test(NAME Tests COMMAND $<TARGET_FILE:tests>)
endif()