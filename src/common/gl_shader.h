#ifndef GL_SHADER_H
#define GL_SHADER_H
#pragma once
#include <string>
#include <fstream>
#include <glm/glm.hpp>

namespace cbt
{
class gl_shader
{

public:
  gl_shader(const char *vert_path, const char *frag_path);

  void use();
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMatrix4(const std::string &name, glm::mat4 matrix) const;
  void setVector3f(const std::string &name, glm::vec3 vector) const;

  unsigned int ID;
};
} // namespace cbt
#endif
