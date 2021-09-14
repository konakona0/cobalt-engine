#include <cstdint>
#include "render.h"
#include "sys/log.h"
#include "sys/core.h"
#include "vulkan/vulkan.h"

namespace cbt
{

// engine - core engine loop
// gonna hardcode the subsystems for now,
// dont think this engine will develop enough
// to require additional option subsystems

uint32_t init()
{
  // init renderer
  cbt::renderer::gl_impl::init();
  // init input
  // init audio
  // init object
  // init state
  // init editor?

  // TODO get return code
  core::frame_end = core::frame_begin =
      std::chrono::high_resolution_clock::now();

  return 0;
}

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

