#pragma once

#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "config.hpp"
#include "errorc.hpp"

//! @input: input wav file
//! @process: feed to libtorch
//! @output: string of transcrib
namespace WAVREADER {

class WavReader {
 public:
  //! @brief get all wav file from system directory
  //! @param std::string filesystem path
  //! @result std::vector<std::string> array of wav file name
  WavReader(std::string);

 private:
  std::vector<std::string> wavFiles{};
};

inline WavReader::WavReader(std::string path) {

}

}  // namespace WAVREADER
