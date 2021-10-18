#include "speech2text.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "config.hpp"

namespace SPEECH2TEXT {

CONFIG::Config loadConfigFile(const std::string t_config) {
  CONFIG::Config config("config.ini");
  return config;
}

std::vector<CONFIG::OUTPUT::WavData> WavReaderTranscrip(
    CONFIG::Config const &t_config) {
  WAVREADER::WavReader wav(t_config);
  auto data = wav.ConvertToText();
  return data;
}
}  // namespace SPEECH2TEXT
