cmake_minimum_required(VERSION 3.0)

project(speech2text LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(inipp)
include_directories(inipp)

add_library(speech2text INTERFACE
  config.hpp
  errorc.hpp
  wavreader.hpp
)
target_link_libraries(speech2text INTERFACE inipp::inipp)
target_include_directories(speech2text INTERFACE speech2text)
set(CMAKE_CXX_CPPCHECK "cppcheck")
set(CMAKE_CXX_CPPLINT "cpplint")