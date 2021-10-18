#pragma once

#include <string>
#include <unordered_map>

namespace ERRORCODE {
struct ErrorCode {
  std::unordered_map<int, const char*> const error_code{
      {1000, "Error %d: File %s does not exist\n"},
      {1001, "Error %d: Directory %s does not exist\n"},
      {1002, "Error %d: File %s can't be loaded"}};
};
}  // namespace ERRORCODE
