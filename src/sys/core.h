#ifndef CORE_H
#define CORE_H
#pragma once
// CODENAME: Compliance, protocol, directive

//
// Tentative names:
//  Compile
//

#include <chrono>
namespace cbt
{
namespace core
{
static decltype(std::chrono::high_resolution_clock::now()) frame_begin,
    frame_end;
static float dt = 0.f;

// taken from Acid engine Sources/Utils/NonCopyable.hpp
class non_copy
{
protected:
  non_copy()          = default;
  virtual ~non_copy() = default;

public:
  non_copy(const non_copy &) = delete;
  non_copy &operator=(const non_copy &) = delete;

  non_copy(non_copy &&) noexcept = default;
  non_copy &operator=(non_copy &&) noexcept = default;
};
} // namespace core
} // namespace cbt
#endif
