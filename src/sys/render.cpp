#include "sys/render.h"
#include <cstdint>
//#include <glbinding/gl/gl.h>
//#include <glbinding/Binding.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "sys/log.h"

#include "vulkan/vulkan.h"
#include "common/loadShader.h"

namespace cbt
{
namespace renderer
{
namespace gl_impl
{
GLFWwindow *window;
GLFWwindow *get_glfw_window() { return window; }

static const GLfloat g_vertex_buffer_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f,
                                                0.0f,  0.0f,  1.0f, 0.0f };

GLuint vertexbuffer;
GLuint programID;
GLuint VertexArrayID;

void init()
{
  log::msg("GL render init start");
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
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
  glewExperimental = true;

  // GLEW impl
  if (glewInit() != GLEW_OK)
  {
    log::crit("Failed to initialize GLEW");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glClearColor(0.5, 0.5, 0.5, 1.0);

  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  programID = LoadShaders("src/shader/default.vert", "src/shader/default.frag");

  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data,
               GL_STATIC_DRAW);

  log::msg("GL render init finish");
}
uint32_t update()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // draw all objects

  // triangle test

  glUseProgram(programID);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);

  glfwSwapBuffers(window);
  glfwPollEvents();

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
      glfwWindowShouldClose(window))
  {
    return 0;
  }

  return 1;
}

void kill()
{
  log::msg("gl_impl renderer exit");
  log::error("error test");

  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(programID);

  glfwTerminate();
}

} // namespace gl_impl
} // namespace renderer
} // namespace cbt
