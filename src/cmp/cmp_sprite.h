// sprite needs to get current impl to draw anything
// ZERO render calls should be made here!!
// sprite will store texture pointers and data about texture
// draw function should reside in objproc
#ifndef SPRITE_H
#define SPRITE_H
#include "cmp/cmp_template.h"
#include "common/gl_shader.h"
#include "cmp/cmp_transform.h"
#include "sys/texprc.h"
#include <list>
namespace cbt
{

class sprite : public component
{
public:
  void draw(glm::mat4);

protected:
  sprite(rj_value);
  component *clone() const override final;
  ~sprite();

  void serialize(rj_writer) override final;
  void deserialize(rj_value) override final;

  void load() override final;
  void init() override final;
  uint32_t update(float) override final;
  void exit() override final;
  void unload() override final;
  sprite() = delete;

  gl_shader const &get_shader();

private:
  gl_shader shader;
  unsigned int quadVAO;
  glm::vec3 color;
  texprc::Texture *tex;
};
} // namespace cbt
#endif
