#ifndef LOG_H
#define LOG_H
#include <string>
#include <fmt/core.h>

// source_location header only defined in gnu c++20 (as of july 2021)
#if defined(__clang__)

// use custom header file if clang
#include "source_location.hpp"
using namespace nostd;

#elif defined(__GNUC__) || defined(__GNUG__)

#include <source_location>
using namespace std;

#endif

namespace cbt
{
namespace log
{

void msg(std::string,
         const source_location &location = source_location::current());
void warn(std::string,
          const source_location &location = source_location::current());
void error(std::string,
           const source_location &location = source_location::current());
void crit(std::string,
          const source_location &location = source_location::current());
} // namespace log
} // namespace cbt
#endif
