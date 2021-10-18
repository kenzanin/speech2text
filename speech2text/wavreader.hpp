#pragma once

#include <ATen/core/ivalue.h>

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "config.hpp"
#include "torch/script.h"

namespace WAVREADER {
class WavReader : public CONFIG::Config {
 public:
  std::vector<CONFIG::OUTPUT::WavData> ConvertToText();
  explicit WavReader(CONFIG::Config const &);

 private:
  torch::jit::script::Module torch_loader{};
  torch::jit::script::Module torch_encoder{};
  torch::jit::script::Module torch_decoder{};

  void LoadTorch();
};

inline WavReader::WavReader(CONFIG::Config const &t_config)
    : CONFIG::Config(t_config) {
  // CONFIG::Config(t_config);
  LoadTorch();
}

inline void WavReader::LoadTorch() {
  std::cout << "loading module loader from: " << loader << "\n";
  std::cout << "loading module encoder from: " << encoder << "\n";
  std::cout << "loading module decoder from: " << decoder << "\n";

  try {
    torch_loader = torch::jit::load(loader);
  } catch (const c10::Error &error) {
    std::cerr << error.what();
    std::fprintf(stderr, error_code.at(1002), 1002, loader.c_str());
    throw 1002;
  }

  try {
    torch_encoder = torch::jit::load(encoder);
  } catch (const c10::Error &error) {
    std::cerr << error.what();
    std::fprintf(stderr, error_code.at(1002), 1002, loader.c_str());
    throw 1002;
  }

  try {
    torch_decoder = torch::jit::load(decoder);
  } catch (const c10::Error &error) {
    std::cerr << error.what();
    std::fprintf(stderr, error_code.at(1002), 1002, loader.c_str());
    throw 1002;
  }
}

inline std::vector<CONFIG::OUTPUT::WavData> WavReader::ConvertToText() {
  std::vector<CONFIG::OUTPUT::WavData> data{};

  for (auto &d : wavFiles) {
    //! std::cout << "Processing: " << d << "\n";
    //! std::cout << "loading the audio\n";
    auto waveform = torch_loader.forward({c10::IValue(d)});
    //! std::cout << "Running inference\n";
    auto emission = torch_encoder.forward({waveform});
    //! std::cout << "Generating the transcription\n";
    auto result = torch_decoder.forward({emission});
    //! std::cout << result.toString()->string() << std::endl;
    //! std::cout << "Done." << std::endl;

    CONFIG::OUTPUT::WavData tmp{.fileName = d,
                                .text = result.toString()->string()};
    data.push_back(tmp);
  }
  return data;
}

}  // namespace WAVREADER
