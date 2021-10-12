#include <cstdlib>
#include <iostream>

#include "config.hpp"

int main() {
  CONFIG::Config test("config.ini");
  std::printf("Filename: %s\nWav Folder 1: %s\nWav Folder 2: %s\n",
              test.fileName.c_str(), test.wavLoc[0].c_str(),
              test.wavLoc[1].c_str());
  return 0;
}
