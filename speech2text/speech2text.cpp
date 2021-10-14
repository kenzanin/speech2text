#include "speech2text.hpp"

#include <cstdlib>
#include <iostream>

namespace SPEECH2TEXT {

void loadConfigFile() {
  CONFIG::Config config{};
  config.ReadConfig("config.ini");
  WAVREADER::WavReader wav{};
  wav.ReadConfig(config);
  wav.ConvertToText();

  for (auto &text : wav.result) {
    std::cout << text << "\n";
  }
}
}  // namespace SPEECH2TEXT
