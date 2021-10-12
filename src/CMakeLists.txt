project(speech2text LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../inipp)

add_library(speech2text INTERFACE
  config.hpp
  errorc.hpp
)

target_link_libraries(speech2text INTERFACE inipp::inipp)
