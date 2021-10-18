#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include "ATen/core/ivalue.h"
#include "error_code.hpp"
#include "inipp/inipp.h"
#include "torch/script.h"

namespace CONFIG {
namespace OUTPUT {
//! @struct WavData
//! @brief this container supposedly hold all data that required by csv
struct WavData {
  std::string fileName{};
  std::uint8_t status{};
  std::string comment{};
  std::string text{};
};
}  // namespace OUTPUT

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<const T1, const T2> &pair) const {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

class Config : public ERRORCODE::ErrorCode {
 private:
  inipp::Ini<char> ini{};

  //! register config ini to variable
  const std::unordered_map<
      const std::pair<const std::string, const std::string>, std::string *const,
      pair_hash>
      ini_map{
          {{"location", "source"}, &this->wavLoc},
          {{"file", "ext"}, &this->wavExt},
          {{"file", "ch1_suffix"}, &this->wavSuffix[0]},
          {{"file", "ch2_suffix"}, &this->wavSuffix[1]},
          {{"libtorch", "loader"}, &this->loader},
          {{"libtorch", "encoder"}, &this->encoder},
          {{"libtorch", "decoder"}, &this->decoder},
      };

  //! @brief check if file exist and trow exception when doesn't
  //! @param std::string file name
  //! @param int error code
  //! @return bool true if exist
  bool IfFileExist(std::string, int);

  //! @brief filter wav file only based on extension .wav == wavExt
  void WavFind();

  //! @brief check if the file exist
  bool Validate();

 public:
  //! config file name
  std::string fileName{};
  //! wav extension
  std::string wavExt{};
  //! wav folder location
  std::string wavLoc{};
  //! wav ch1 and ch2 suffix
  std::string wavSuffix[2]{};
  //! loader.zip
  std::string loader{};
  //! encoder.zip
  std::string encoder{};
  //! decoder.zip
  std::string decoder{};
  //! list of wav in wavLoc
  std::vector<std::string> wavFiles{};

  void ReadConfig(const std::string);
  void ReadConfig(Config const &);

  // Config &operator=(const Config &t_config) {
  //   fileName = t_config.fileName;
  //   wavExt = t_config.wavExt;
  //   wavLoc = t_config.wavLoc;
  //   std::copy(t_config.wavSuffix->begin(), t_config.wavSuffix->end(),
  //             wavSuffix);
  //   loader = t_config.loader;
  //   encoder = t_config.encoder;
  //   decoder = t_config.decoder;
  //   wavFiles = t_config.wavFiles;
  //   return *this;
  // }
  // Config(Config const &t_other) {}
  explicit Config(const std::string);
  Config(Config const &);
};

inline Config::Config(Config const &t_other) {
  fileName = t_other.fileName;
  wavExt = t_other.wavExt;
  wavLoc = t_other.wavLoc;
  std::copy(t_other.wavSuffix->begin(), t_other.wavSuffix->end(), wavSuffix);
  loader = t_other.loader;
  encoder = t_other.encoder;
  decoder = t_other.decoder;
  wavFiles = t_other.wavFiles;
}

inline Config::Config(const std::string t_config) {
  fileName = t_config;
  //! check if file exist
  IfFileExist(fileName, 1000);

  //! parse ini config file
  std::ifstream is(fileName);
  ini.parse(is);
  ini.strip_trailing_comments();

  //! copy value from registered key to variable
  for (auto &e : ini_map) {
    inipp::get_value(ini.sections.at(e.first.first), e.first.second,
                     *(e.second));
  }

  Validate();
  WavFind();
}

inline void Config::ReadConfig(Config const &t_other) {
  fileName = t_other.fileName;
  wavExt = t_other.wavExt;
  wavLoc = t_other.wavLoc;
  std::copy(t_other.wavSuffix->begin(), t_other.wavSuffix->end(), wavSuffix);
  loader = t_other.loader;
  encoder = t_other.encoder;
  decoder = t_other.decoder;
  wavFiles = t_other.wavFiles;
}

inline bool Config::IfFileExist(std::string t_name, int t_e) {
  try {
    if (!std::filesystem::exists(t_name)) throw t_e;
  } catch (int &e) {
    std::fprintf(stderr, error_code.at(e), e, t_name.c_str());
    throw;
  }
  return true;
}

inline bool Config::Validate() {
  //! does the path exist?
  try {
    if (!std::filesystem::is_directory(wavLoc)) throw 1001;
  } catch (int &e) {
    std::fprintf(stderr, error_code.at(e), e, wavLoc.c_str());
    throw;
  }

  //! does loader.zip exist
  IfFileExist(loader, 1000);

  //! does encoder.zip exist
  IfFileExist(encoder, 1000);

  //! does decoder.zip exist
  IfFileExist(decoder, 1000);

  return true;
}

inline void Config::WavFind() {
  for (const auto &i : std::filesystem::directory_iterator(wavLoc)) {
    //! check if file name ended with .wav == wavExt
    std::string tmp = i.path().c_str();
    int check_ext =
        wavExt.compare(std::string(tmp.end() - wavExt.size(), tmp.end()));
    //! if not jump to for
    if (check_ext != 0) {
      continue;
    }

    wavFiles.push_back(i.path());
    // std::printf("file: %s\n", i.path().c_str());
  }
}

inline void Config::ReadConfig(const std::string t_config) {
  fileName = t_config;
  //! check if file exist
  IfFileExist(fileName, 1000);

  //! parse ini config file
  std::ifstream is(fileName);
  ini.parse(is);
  ini.strip_trailing_comments();

  //! copy value from registered key to variable
  for (auto &e : ini_map) {
    inipp::get_value(ini.sections.at(e.first.first), e.first.second,
                     *(e.second));
  }

  Validate();
  WavFind();
}
}  // namespace CONFIG
