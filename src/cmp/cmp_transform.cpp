#include "cmp/cmp_transform.h"
#include <glm/gtx/transform.hpp>

namespace cbt
{

transform::transform() : component(cmp_type::transform) {}

transform::transform(rj_value val) : component(cmp_type::transform) {}

glm::vec3 transform::get_position() const { return position; }
void transform::set_position(glm::vec3 new_pos)
{
  position = new_pos;
  dirty    = true;
}

float transform::get_rotation() const { return rotation; }
void transform::set_rotation(float new_rot)
{
  rotation = new_rot;
  dirty    = true;
}

glm::vec3 transform::get_scale() const { return scale; }
void transform::set_scale(glm::vec3 new_scl)
{
  scale = new_scl;
  dirty = true;
}

glm::mat4 transform::get_matrix() const { return matrix; }
void transform::set_matrix(glm::mat4 matr) { matrix = matr; }

component *transform::clone() const { return nullptr; }

void transform::serialize(rj_writer writer) {}
void transform::deserialize(rj_value val) {}

void transform::load() {}
void transform::init() {}

uint32_t transform::update(float dt)
{
  if (dirty)
  {
    matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);
    matrix = glm::translate(
        matrix, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.5f * scale.z));
    matrix = glm::rotate(matrix, glm::radians(rotation),
                         glm::vec3(0.0f, 0.0f, 0.0f));
    matrix = glm::translate(
        matrix, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, -0.5f * scale.z));
    matrix = glm::scale(matrix, scale);
  }
  return 1;
}

void transform::exit() {}
void transform::unload() {}

} // namespace cbt
