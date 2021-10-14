#pragma once

#include <ATen/core/ivalue.h>

#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "config.hpp"
#include "errorc.hpp"
#include "torch/script.h"

namespace WAVREADER {
class WavReader {
 public:
  std::vector<std::string> result{};

  void ReadConfig(CONFIG::Config &);
  void ConvertToText();

 private:
  CONFIG::Config config{};
};

inline void WavReader::ReadConfig(CONFIG::Config &t_config) {
  config = t_config;
}

inline void WavReader::ConvertToText() {
  torch::jit::script::Module loader, encoder, decoder;
  std::cout << "loading module loader from" << config.loader << "\n";
  std::cout << "loading module encoder from" << config.encoder << "\n";
  std::cout << "loading module decoder from" << config.decoder << "\n";
  loader = torch::jit::load(config.loader);
  encoder = torch::jit::load(config.encoder);
  decoder = torch::jit::load(config.decoder);

  for (auto &w : config.wavFiles) {
    std::cout << "Processing: " << w << "\n";
    std::cout << "loading the audio\n";
    auto waveform = loader.forward({c10::IValue(w)});
    std::cout << "Running inference\n";
    auto emission = encoder.forward({waveform});
    std::cout << "Generating the transcription\n";
    auto result = decoder.forward({emission});
    std::cout << result.toString()->string() << std::endl;
    std::cout << "Done." << std::endl;

    this->result.push_back(result.toString()->string());
  }
}

}  // namespace WAVREADER
