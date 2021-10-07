#ifndef TRANSFORM_H
#define TRANSFORM_H
#pragma once

#include "cmp/cmp_template.h"
#include "common/gl_shader.h"

namespace cbt
{

class transform : public component
{
public:
  transform();
  transform(rj_value val);
  virtual ~transform() {}

  glm::vec3 get_position() const;
  void set_position(glm::vec3);

  float get_rotation() const;
  void set_rotation(float);

  glm::vec3 get_scale() const;
  void set_scale(glm::vec3);

  glm::mat4 get_matrix() const;
  void set_matrix(glm::mat4);

protected:
  component *clone() const override final;

  void serialize(rj_writer) override final;
  void deserialize(rj_value) override final;

  void load() override final;
  void init() override final;
  uint32_t update(float) override final;
  void exit() override final;
  void unload() override final;

private:
  glm::vec3 position;
  float rotation;
  glm::vec3 scale;

  bool dirty;
  glm::mat4 matrix;
};
} // namespace cbt
#endif
