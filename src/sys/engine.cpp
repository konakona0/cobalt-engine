#include <cstdint>
#include "sys/render.h"
#include "sys/log.h"
#include "sys/core.h"
#include "sys/objprc.h"
#include "sys/input.h"
#include "util/console.h"

namespace cbt
{
namespace engine
{

// engine - core engine loop
// gonna hardcode the subsystems for now,
// dont think this engine will develop enough
// to require additional option subsystems

uint32_t init()
{
  // init renderer
  renderer::init();
  // init input
  input::init();
  // init audio
  // init object
  objprc::init();
  // init state
  // init editor?

  // TODO get return code
  core::frame_end = core::frame_begin =
      std::chrono::high_resolution_clock::now();

  return 0;
}

float get_dt() { return core::dt; }

uint32_t update()
{
  core::frame_end = std::chrono::high_resolution_clock::now();
  core::dt =
      std::chrono::duration<float>(core::frame_end - core::frame_begin).count();
  core::frame_begin = std::chrono::high_resolution_clock::now();

  // TODO impl frame limiter here
  // also just smarter dt generally

  // update all sub-systems

  // anatomy of update
  //  - get inputs
  //  - apply behavior and physics
  //  - check collisions, update physics/behavior accordingly
  //  - send final positional data to renderer
  //  - renderer draws all objects
  //

  // next
  // - get dt
  // - make main loop
  // - hardcode test rects/textures
  // - figure out render/update structure
  // - fuck

  renderer::update();
  input::update(core::dt);
  console::update(core::dt);
  return 1;

  // return opcode 0
  // return 0;
}
uint32_t exit()
{
  renderer::kill();
  return 0;
}
} // namespace engine
} // namespace cbt

