#include "speech2text.hpp"

#include <cstdlib>
#include <iostream>

#include "config.hpp"

namespace SPEECH2TEXT {

CONFIG::Config loadConfigFile(std::string t_config) {
  CONFIG::Config config{};
  config.ReadConfig("config.ini");
  return config;
}

void WavReaderTranscrip(CONFIG::Config const &t_config) {
  WAVREADER::WavReader wav{};
  wav.ReadConfig(t_config);
  wav.ConvertToText();

  for (auto &text : wav.result) {
    std::cout << text << "\n";
  }
}

}  // namespace SPEECH2TEXT
