#include "texprc.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "sys/log.h"
#include <list>
namespace cbt
{
namespace texprc
{

void init() {}

Texture::Texture(const char *filepath)
    : width(0), height(0), nrChannels(0), filename(filepath), gl_texture_ID(0)
{
  filename = filepath;
}
std::list<Texture *> texture_array;
unsigned int quadVAO;

void Texture::bind() { glBindTexture(GL_TEXTURE_2D, gl_texture_ID); }

void Texture::load(const char *filepath)
{
  glGenTextures(1, &gl_texture_ID);
  glBindTexture(GL_TEXTURE_2D, gl_texture_ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    log::error(fmt::format("Failed to load texture {} !", filepath));
  }
  stbi_image_free(data);
}

void add_texture(Texture *tx) { texture_array.push_back(tx); }

} // namespace texprc
} // namespace cbt

