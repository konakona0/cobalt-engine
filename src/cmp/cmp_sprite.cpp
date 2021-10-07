#include "cmp/cmp_sprite.h"
#include "sys/render.h"
#include "sys/log.h"
#include "sys/object.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace cbt
{
sprite::sprite(rj_value val)
    : component(cmp_type::sprite), shader(renderer::get_default_shader())
{
  deserialize(val);
}

sprite::~sprite() {}

component *sprite::clone() const { return nullptr; }

void sprite::deserialize(rj_value val) {}
void sprite::serialize(rj_writer writer) {}
void sprite::load() {}
void sprite::init() {}
uint32_t sprite::update(float dt)
{
  dt;
  return 1;
}
void sprite::exit() {}
void sprite::unload() {}

gl_shader const &sprite::get_shader() { return shader; }

void sprite::draw(glm::mat4 matrix)
{
  shader.setMatrix4("model", matrix);
  shader.setVector3f("spriteColor", color);

  glActiveTexture(GL_TEXTURE0);
  tex->bind();

  glBindVertexArray(quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

} // namespace cbt
