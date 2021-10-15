#pragma once

#include <string>

#include "config.hpp"
#include "errorc.hpp"
#include "wavreader.hpp"

namespace SPEECH2TEXT {
CONFIG::Config loadConfigFile(const std::string);
void WavReaderTranscrip(CONFIG::Config const&);
}  // namespace SPEECH2TEXT
