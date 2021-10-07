//  https://learnopengl.com/Getting-started/Shaders
#include "common/gl_shader.h"
#include "sys/log.h"
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace cbt
{
// gl_shader::gl_shader()
//{
// gl_shader("shader/default.vert", "shader/default.frag");
//}

gl_shader::gl_shader(const char *vert_path, const char *frag_path)
{
  // load glsl src
  std::string vert_code;
  std::string frag_code;
  std::ifstream vert_file;
  std::ifstream frag_file;

  vert_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  frag_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try
  {
    // open files
    log::msg("Opening vertex file");
    vert_file.open(vert_path);

    log::msg("Opening fragment file");
    frag_file.open(frag_path);

    std::stringstream vert_stream, frag_stream;

    log::msg("buffering shaders");
    // read file into stream
    vert_stream << vert_file.rdbuf();
    frag_stream << frag_file.rdbuf();

    // close files
    vert_file.close();
    frag_file.close();

    vert_code = vert_stream.str();
    frag_code = frag_stream.str();
  }
  catch (std::ifstream::failure &e)
  {
    log::error(fmt::format("Shader file WAS NOT read successfully! Error {}",
                           e.what()));
    return;
  }

  const char *v_code = vert_code.c_str();
  const char *f_code = frag_code.c_str();

  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  log::msg("Creating vertex shader");
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &v_code, NULL);
  glCompileShader(vertex);

  // print errors if any
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    log::error(
        fmt::format("Shader compilation failed for vertex shader {} : {}",
                    vert_path, infoLog));
  }

  log::msg("Creating fragment shader");
  // fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &f_code, NULL);
  glCompileShader(fragment);

  // print errors if any
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    log::error(
        fmt::format("Shader compilation failed for fragment shader {} : {}",
                    frag_path, infoLog));
  }

  // shader program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);

  // print linking errors if any
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    log::error(
        fmt::format("Shader linking failed for {}\n{}", vert_path, infoLog));
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void gl_shader::use() { glUseProgram(ID); }

void gl_shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void gl_shader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void gl_shader::setFloat(const std::string &name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void gl_shader::setMatrix4(const std::string &name, glm::mat4 matrix) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, false,
                     &matrix[0][0]);
}
void gl_shader::setVector3f(const std::string &name, glm::vec3 vector) const
{
  glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vector[0]);
}
} // namespace cbt
