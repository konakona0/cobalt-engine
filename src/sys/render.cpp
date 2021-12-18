#include "sys/render.h"
#include "util/console.h"
#include "sys/engine.h"
#include "sys/core.h"
#include <cstdint>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "sys/log.h"
#include "util/glyph.h"
#include <GL/glu.h>

#define CHECKERROR                                                             \
  {                                                                            \
    GLenum err = glGetError();                                                 \
    if (err != GL_NO_ERROR)                                                    \
    {                                                                          \
      fprintf(stderr, "OpenGL error (at line %d): %s\n", __LINE__,             \
              gluErrorString(err));                                            \
      exit(-1);                                                                \
    }                                                                          \
  }

// thanks gary

namespace cbt
{
namespace renderer
{

glm::vec4 clear_color;
GLFWwindow *window;

GLuint vertexbuffer;
GLuint programID;
GLuint VertexArrayID;

unsigned int quadVAO;

gl_shader *default_shader;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void init()
{
  log::msg("GL render init start");
  if (!glfwInit())
  {
    exit(EXIT_FAILURE);
    // TODO print exit reason to log
  }

  // ripped https://www.opengl-tutorial.org/beginners-tutorials
  // glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GL Window", NULL, NULL);

  if (!window)
  {
    // TODO log
    log::crit("GLFW window failed to open!");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  CHECKERROR;
  // glfwSwapInterval(1);

  // GLEW impl
  if (glewInit() != GLEW_OK)
  {
    log::crit("Failed to initialize GLEW");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  CHECKERROR;
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  CHECKERROR;

  default_shader =
      new gl_shader("src/shader/default.vert", "src/shader/default.frag");

  log::msg("GL render init finish");
  CHECKERROR;
  console::init();
}

gl_shader get_default_shader() { return *default_shader; }

float test_char_timer        = 0.f;
const float TEST_TIMER_LIMIT = 0.8f;

uint32_t update()
{
  // credit: gary herron
  // anatomy of a pass
  // - choose a shader
  // - choose an FBO/Render-Target
  // - set the viewport
  // - clear the screen
  // - set uniform variables depended by the shader
  // - draw geometry
  // - unset FBO
  // - unset shader

  glClearColor(0, 0, 0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  CHECKERROR;

  console::draw();
  glfwSwapBuffers(window);
  CHECKERROR;

  return 1;
}

void kill()
{
  log::msg("gl_impl renderer exit");

  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(programID);

  glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

GLFWwindow *get_glfw_window() { return window; }

} // namespace renderer
} // namespace cbt
