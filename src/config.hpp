#pragma once

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "errorc.hpp"
#include "inipp/inipp.h"

namespace CONFIG {
class Config : ERRORCODE::ErrorCode {
  inipp::Ini<char> ini{};

 public:
  std::string fileName{};
  std::string wavLoc[2]{};

  Config(const std::string);
};

inline Config::Config(const std::string n) : fileName(n) {
  try {
    if (!std::filesystem::exists(fileName)) throw 1000;
  } catch (int e) {
    std::fprintf(stderr, errorc.at(e), e, fileName.c_str());
    throw;
  }
  std::ifstream is(fileName);
  ini.parse(is);
  ini.strip_trailing_comments();
  inipp::get_value(ini.sections["location"], "one", wavLoc[0]);
  inipp::get_value(ini.sections["location"], "two", wavLoc[1]);
}
}  // namespace CONFIG
