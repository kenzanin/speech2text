#pragma once

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "errorc.hpp"
#include "inipp/inipp.h"

namespace CONFIG {
using std::make_pair;

class Config : ERRORCODE::ErrorCode {
 private:
  inipp::Ini<char> ini{};

  //! register config ini to variable
  const std::map<std::pair<std::string, std::string> const, std::string *const>
      ini_map = {
          {make_pair("location", "source"), &this->wavLoc},
          {make_pair("file", "ext"), &this->wavExt},
          {make_pair("file", "ch1_suffix"), &this->wavSuffix[0]},
          {make_pair("file", "ch2_suffix"), &this->wavSuffix[1]},
          {make_pair("libtorch", "loader"), &this->loader},
          {make_pair("libtorch", "encoder"), &this->encoder},
          {make_pair("libtorch", "decoder"), &this->decoder},
      };

  //! @brief check if file exist and trow exception when doesn't
  //! @param std::string file name
  //! @param int error code
  //! @return bool true if exist
  bool if_file_exist(std::string, int);

  bool validate();

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

  Config(const std::string);
  void WavFind();
};

inline bool Config::if_file_exist(std::string name, int e) {
  try {
    if (!std::filesystem::exists(name)) throw e;
  } catch (int &e) {
    std::fprintf(stderr, errorc.at(e), e, name.c_str());
    throw;
  }
  return true;
}

inline bool Config::validate() {
  //! does the path exist?
  try {
    if (!std::filesystem::is_directory(wavLoc)) throw 1001;
  } catch (int &e) {
    std::fprintf(stderr, errorc.at(e), e, wavLoc.c_str());
    throw;
  }

  //! does loader.zip exist
  if_file_exist(loader, 1000);

  //! does encoder.zip exist
  if_file_exist(encoder, 1000);

  //! does decoder.zip exist
  if_file_exist(decoder, 1000);

  return true;
}

inline void Config::WavFind() {
  for (const auto &i : std::filesystem::directory_iterator(wavLoc)) {
    //! check if file name ended with .wav == wavExt
    std::string tmp = i.path().c_str();
    int ii = 0;
    for (; ii < wavExt.size(); ii++) {
      char x=wavExt[wavExt.size() - ii -1];
      char y=tmp[tmp.size() - ii - 1];
      if (x != y) {
        break;
      }
    }
    
    //! if not back to for
    if (ii < wavExt.size()) continue;

    wavFiles.push_back(i.path());
    std::printf("file: %s\n", i.path().c_str());
  }
}

inline Config::Config(const std::string n) : fileName(n) {
  //! check if file exist
  if_file_exist(fileName, 1000);

  //! parse ini config file
  std::ifstream is(fileName);
  ini.parse(is);
  ini.strip_trailing_comments();

  //! copy value from registered key to variable
  for (auto &e : ini_map) {
    inipp::get_value(ini.sections[e.first.first], e.first.second, *(e.second));
  }

  validate();
  WavFind();
}
}  // namespace CONFIG
