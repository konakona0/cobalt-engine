#ifndef GLYPH_H
#define GLYPH_H
#include <glm/glm.hpp>
#include "common/gl_shader.h"
namespace cbt
{
namespace glyph
{
void init();
void render(std::string text, float x, float y, float scale, glm::vec3 color);
} // namespace glyph
} // namespace cbt
#endif
