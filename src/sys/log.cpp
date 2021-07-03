#include "log.h"
#include <iostream>
namespace cbt
{
namespace log
{

enum log_level
{
  DEBUG,
  WARN,
  ERROR,
  CRIT
};

void write_log(log_level level, std::string &msg,
               const source_location &location)
{
#ifdef __GNUG__
  std::cout << "gnug on\n";
#endif
  // TODO write lines to buffer before output

  // TODO make elegant
  switch (level)
  {
    // TODO give these colors and bold
    case DEBUG: std::cout << "[DEBUG]"; break;
    case WARN: std::cout << "[WARN]"; break;
    case ERROR: std::cout << "[ERROR]"; break;
    case CRIT: std::cout << "[CRITICAL]"; break;
  }

  std::cout << " " << msg;
  if (level != DEBUG)
  {
    std::cout << " (file: " << location.file_name()
              << ", fn: " << location.function_name() << " [" << location.line()
              << ":" << location.column() << "]";
  }
  std::cout << '\n';
}

void msg(std::string msg, const source_location &location)
{
  write_log(DEBUG, msg, location);
}
void warn(std::string msg, const source_location &location)
{
  write_log(WARN, msg, location);
}
void error(std::string msg, const source_location &location)
{
  write_log(ERROR, msg, location);
}
void crit(std::string msg, const source_location &location)
{
  write_log(CRIT, msg, location);
}

} // namespace log
} // namespace cbt
