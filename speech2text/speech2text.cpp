#include "speech2text.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

#include "config.hpp"

namespace SPEECH2TEXT {

CONFIG::Config loadConfigFile(std::string t_config) {
  CONFIG::Config config{};
  config.ReadConfig("config.ini");
  return config;
}

std::vector<CONFIG::WavData> WavReaderTranscrip(
    CONFIG::Config const &t_config) {
  WAVREADER::WavReader wav{};
  wav.ReadConfig(t_config);
  wav.ConvertToText();

  for (auto &text : wav.result) {
    std::cout << text << "\n";
  }
  return wav.data;
}

}  // namespace SPEECH2TEXT
