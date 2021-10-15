#pragma once

#include <ATen/core/ivalue.h>

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "config.hpp"
#include "errorc.hpp"
#include "torch/script.h"

namespace WAVREADER {
class WavReader : public CONFIG::Config {
 public:
  std::vector<std::string> result{};

  //  void ReadConfig(CONFIG::Config &);
  void ConvertToText();

 private:
  // CONFIG::Config config{};
};

// inline void WavReader::ReadConfig(CONFIG::Config &t_config) {
//  config.ReadConfig(t_config);
// }

inline void WavReader::ConvertToText() {
  torch::jit::script::Module torch_loader, torch_encoder, torch_decoder;
  std::cout << "loading module loader from: " << loader << "\n";
  std::cout << "loading module encoder from: " << encoder << "\n";
  std::cout << "loading module decoder from: " << decoder << "\n";
  torch_loader = torch::jit::load(loader);
  torch_encoder = torch::jit::load(encoder);
  torch_decoder = torch::jit::load(decoder);

  for (auto &d : data) {
    std::cout << "Processing: " << d.fileName << "\n";
    std::cout << "loading the audio\n";
    auto waveform = torch_loader.forward({c10::IValue(d.fileName)});
    std::cout << "Running inference\n";
    auto emission = torch_encoder.forward({waveform});
    std::cout << "Generating the transcription\n";
    auto result = torch_decoder.forward({emission});
    std::cout << result.toString()->string() << std::endl;
    std::cout << "Done." << std::endl;

    this->result.push_back(result.toString()->string());
    d.text = result.toString()->string();
  }
}

}  // namespace WAVREADER
