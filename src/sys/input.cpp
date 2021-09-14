#include <GLFW/glfw3.h>
#include "sys/input.h"
#include "sys/render.h"
namespace cbt
{
namespace input
{
bool key_down(int key)
{
  GLFWwindow *win = renderer::gl_impl::get_glfw_window();
  if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) return true;
  return false;
}
} // namespace input
} // namespace cbt

