#include "sys/engine.h"

// TODO
// - logging

int main()
{
  // cobalt engine start
  cbt::init();
  int exit_code = 1;
  while (exit_code != 0) exit_code = cbt::update();
  cbt::exit();
  return 0;
}
