#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <iostream>

#include "speech2text.hpp"

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  auto config_ini = SPEECH2TEXT::loadConfigFile("config.ini");
  auto data = SPEECH2TEXT::WavReaderTranscrip(config_ini);

  for (auto &e : data) {
    std::cout << e.fileName << "\n" << e.text << "\n";
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microsecond\n" << std::endl;
  return 0;
}
