#include <cstdint>

// so render.h doesnt need to include GL.h
typedef class GLFWwindow GLFWwindow;

namespace cbt
{
namespace renderer
{

namespace gl_impl
{
// OpenGL 3 implementation

void init();
void draw();
uint32_t update();
GLFWwindow *get_glfw_window();
// TODO TEMPORARY!!
void object_draw();

void kill();

} // namespace gl_impl
} // namespace renderer
} // namespace cbt
