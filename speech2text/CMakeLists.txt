cmake_minimum_required(VERSION 3.0)

project(speech2text LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CPPCHECK "cppcheck")
set(CMAKE_CXX_CPPLINT "cpplint")
set(TORCH_SRC /home/kenzanin/build/audio)
set(TORCH_BIN libtorchaudio)

add_subdirectory(inipp)
include_directories(inipp)

add_library(speech2text speech2text.cpp speech2text.hpp config.hpp errorc.hpp
                        wavreader.hpp)

find_package(Torch REQUIRED)
message("libtorchaudio CMakeLists: ${TORCH_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_subdirectory(${TORCH_SRC} ${TORCH_BIN})
set(BUILD_SOX
    ON
    CACHE BOOL "Build libsox into libtorchaudio")
target_include_directories(speech2text INTERFACE ./)

target_link_libraries(speech2text "${TORCH_LIBRARIES}" "${TORCHAUDIO_LIBRARY}"
                      inipp::inipp)
