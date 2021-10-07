#include "sys/engine.h"

// TODO
// - logging
// -

int main()
{
  // cobalt engine start
  cbt::engine::init();
  int exit_code = 1;
  while (exit_code != 0) exit_code = cbt::engine::update();
  cbt::engine::exit();
  return 0;
}
