#include <cstdlib>
#include <iostream>

#include "config.hpp"
#include "wavreader.hpp"

int main() {
  CONFIG::Config test("config.ini");
  std::printf(
      "Filename: %s\n"
      "Wav Folder 1: %s\n"
      "Wav Ext: %s\n"
      "Wav CH1 name suffix: %s\n"
      "Wav CH2 name suffix: %s\n",
      test.fileName.c_str(), test.wavLoc.c_str(), test.wavExt.c_str(),
      test.wavSuffix[0].c_str(), test.wavSuffix[1].c_str());
  test.WavFind();

  return 0;
}
