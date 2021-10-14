#pragma once

#include <string>
#include <unordered_map>

namespace ERRORCODE {
class ErrorCode {
 public:
  std::unordered_map<int, const char*> const errorc{
      {1000, "Error %d: File %s does not exist\n"},
      {1001, "Error %d: Directory %s does not exist\n"}};
};
}  // namespace ERRORCODE
