#pragma once

#include <string>
#include <unordered_map>

namespace ERRORCODE {
class ErrorCode {
 public:
  const std::unordered_map<int, const char*> errorc{
      {1000, "Error %d: File %s not Exist\n"}};
};

}  // namespace ERRORCODE
