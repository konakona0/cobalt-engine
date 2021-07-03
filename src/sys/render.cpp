#include <cstdint>
//#include <glbinding/gl/gl.h>
//#include <glbinding/Binding.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "log.h"

namespace cbt
{
namespace renderer
{
namespace gl_impl
{
GLFWwindow *window;
GLFWwindow *get_glfw_window() { return window; }

void init()
{
  // glbinding::Binding::initialize(nullptr);
  if (!glfwInit())
  {
    exit(EXIT_FAILURE);
    // TODO print exit reason to log
  }

  // ripped https://www.opengl-tutorial.org/beginners-tutorials
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(1280, 720, "GL Window", NULL, NULL);
  if (!window)
  {
    // TODO log
    log::crit("GLFW window failed to open!");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  // GLEW impl
  if (glewInit() != GLEW_OK)
  {
    log::crit("Failed to initialize GLEW");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glClearColor(0.5, 0.5, 0.5, 1.0);
}
uint32_t update()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // draw all objects

  glfwSwapBuffers(window);
  glfwPollEvents();

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
      glfwWindowShouldClose(window))
  {
    return 0;
  }
  return 1;
}

// TODO TEMPORARY!!
void object_draw() {}

void kill()
{
  log::msg("gl_impl renderer exit");
  log::error("error test");
  glfwTerminate();
}

} // namespace gl_impl
} // namespace renderer
} // namespace cbt
