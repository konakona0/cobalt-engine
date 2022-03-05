#include <GLFW/glfw3.h>
#include "sys/input.h"
#include "sys/render.h"
#include "util/console.h"
#include "sys/log.h"
#include <iostream>
#include <vector>
namespace cbt
{
namespace input
{
GLFWwindow *window;
uint32_t exit_code = 1;

std::string ACTION[3] = { "Release", "Press", "Repeat" };
enum key_state
{
  pressed,
  idle,
  held,
  released
};
std::vector<key_state> key_array;

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);
void character_callback(GLFWwindow *window, unsigned int codepoint);

void init()
{
  log::msg("input init start");
  window = renderer::get_glfw_window();
  glfwSetCharCallback(renderer::get_glfw_window(), character_callback);
  glfwSetKeyCallback(window, key_callback);
  key_array.resize(GLFW_KEY_LAST);
  log::msg("input init done");
}

bool key_held(int key)
{
  return key_array[key] == key_state::held ||
         key_array[key] == key_state::pressed;
}
bool key_down(int key)
{
  if (key_array[key] == pressed)
  {
    key_array[key] = held;
    return true;
  }
  return false;
}

bool key_up(int key) { return key_array[key] == released; }

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods)
{

  char c_key = static_cast<char>(key);
  if (action == GLFW_REPEAT) return; // Because keyboard autorepeat is evil.
  //log::msg(fmt::format("key callback {}({}) s:{} {}", c_key, key, scancode,
                       //ACTION[action].c_str()));

  if (console::get_active())
  {
    if (action == GLFW_PRESS)
    {
      switch (key)
      {
        case GLFW_KEY_GRAVE_ACCENT: console::toggle_active(); break;
        case GLFW_KEY_ESCAPE: console::set_active(false); break;
        case GLFW_KEY_ENTER: console::execute_current_buffer(); break;
        case GLFW_KEY_BACKSPACE: console::get_line_buffer().pop_back(); break;
      }
    }
  }
  else
  {
    if (action == GLFW_PRESS)
    {
      switch (key)
      {
        case GLFW_KEY_GRAVE_ACCENT: console::toggle_active(); break;
        case GLFW_KEY_ESCAPE: exit(0); break;
        default: key_array[key] = pressed;
      }
    }
    if (action == GLFW_RELEASE) { key_array[key] = released; }
  }
}

void character_callback(GLFWwindow *window, unsigned int codepoint)
{
  if (console::get_active())
  {
    std::string &console_line = console::get_line_buffer();
    switch (codepoint)
    {
      case GLFW_KEY_ENTER:
        console_line.clear();
        console::set_active(false);
        break;
      case GLFW_KEY_GRAVE_ACCENT: console_line.clear(); break;
      default: console_line.push_back(static_cast<char>(codepoint));
    }
  }
}

uint32_t update(float dt)
{
  glfwPollEvents();
  // if (glfwGetKey(renderer::get_glfw_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS
  // || glfwWindowShouldClose(window))
  //{
  // return 0;
  //}
  return 1;
}
} // namespace input
} // namespace cbt

