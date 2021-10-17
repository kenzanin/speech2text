#pragma once

#include <string>
#include <vector>

#include "config.hpp"
#include "errorc.hpp"
#include "wavreader.hpp"

namespace SPEECH2TEXT {
CONFIG::Config loadConfigFile(const std::string);
std::vector<CONFIG::OUTPUT::WavData> WavReaderTranscrip(CONFIG::Config const&);
}  // namespace SPEECH2TEXT
