#pragma once

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "errorc.hpp"
#include "inipp/inipp.h"

namespace CONFIG {
class Config : public ERRORCODE::ErrorCode {
 private:
  inipp::Ini<char> ini{};

  //! register config ini to variable
  const std::map<std::pair<std::string, std::string> const, std::string *const>
      ini_map = {
          {std::make_pair("location", "source"), &this->wavLoc},
          {std::make_pair("file", "ext"), &this->wavExt},
          {std::make_pair("file", "ch1_suffix"), &this->wavSuffix[0]},
          {std::make_pair("file", "ch2_suffix"), &this->wavSuffix[1]},
          {std::make_pair("libtorch", "loader"), &this->loader},
          {std::make_pair("libtorch", "encoder"), &this->encoder},
          {std::make_pair("libtorch", "decoder"), &this->decoder},
      };

  //! @brief check if file exist and trow exception when doesn't
  //! @param std::string file name
  //! @param int error code
  //! @return bool true if exist
  bool IfFileExist(std::string, int);
  void WavFind();
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

  Config &operator=(const Config &t_config) {
    fileName = t_config.fileName;
    wavExt = t_config.wavExt;
    wavLoc = t_config.wavLoc;
    std::copy(t_config.wavSuffix->begin(), t_config.wavSuffix->end(),
              wavSuffix);
    loader = t_config.loader;
    encoder = t_config.encoder;
    decoder = t_config.decoder;
    wavFiles = t_config.wavFiles;
    return *this;
  }
  Config(const Config &t_other) {}
  Config() {}
};

inline bool Config::IfFileExist(std::string name, int e) {
  try {
    if (!std::filesystem::exists(name)) throw e;
  } catch (int &e) {
    std::fprintf(stderr, errorc.at(e), e, name.c_str());
    throw;
  }
  return true;
}

inline bool Config::Validate() {
  //! does the path exist?
  try {
    if (!std::filesystem::is_directory(wavLoc)) throw 1001;
  } catch (int &e) {
    std::fprintf(stderr, errorc.at(e), e, wavLoc.c_str());
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
    int test_string =
        wavExt.compare(std::string(tmp.end() - wavExt.size(), tmp.end()));
    //! if not jump to for
    if (test_string != 0) {
      continue;
    }

    wavFiles.push_back(i.path());
    // std::printf("file: %s\n", i.path().c_str());
  }
}

inline void Config::ReadConfig(const std::string n) {
  fileName = n;
  //! check if file exist
  IfFileExist(fileName, 1000);

  //! parse ini config file
  std::ifstream is(fileName);
  ini.parse(is);
  ini.strip_trailing_comments();

  //! copy value from registered key to variable
  for (auto &e : ini_map) {
    inipp::get_value(ini.sections[e.first.first], e.first.second, *(e.second));
  }

  Validate();
  WavFind();
}
}  // namespace CONFIG
