// Engine class(?) (06-11-21)
// wtf should it be a class or static idk
// there's probably a better way to handle it with modern c++
// i wish i was taught modern c++ but nope
//
// all we need is an engine loop.
// classes will complicate things here, a class is suited for things
// that live and die, things that need dynamically allocated memory
// the engine starts and stops with the application, so a class is
// not necessary.

// look at other c++ graphical engine loops.
// it's a mistake to only look at game engines.
// anything with a GUI runs with a main loop, with a render at the end

#include <cstdint>
#include "render.h"
#include "log.h"

namespace cbt
{

uint32_t init()
{
  log::msg("ugly");
  cbt::renderer::gl_impl::init();
  return 0;
}

uint32_t update()
{
  // update all sub-systems

  // anatomy of update
  //  - get inputs
  //  - apply behavior and physics
  //  - check collisions, update physics/behavior accordingly
  //  - send final positional data to renderer
  //  - renderer draws all objects
  //

  return renderer::gl_impl::update();

  // return opcode 0
  // return 0;
}
uint32_t exit()
{
  printf("cbt exit\n");
  renderer::gl_impl::kill();
  return 0;
}
} // namespace cbt

