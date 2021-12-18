#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "common/gl_shader.h"
#include "sys/render.h"
#include "sys/log.h"

#include <ft2build.h>
#include FT_FREETYPE_H

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

namespace cbt
{
namespace glyph
{

// built off of
// https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/7.in_practice/2.text_rendering/text_rendering.cpp

struct glyph
{
  unsigned int textureID;
  glm::ivec2 size;
  glm::ivec2 bearing;
  unsigned int advance;
};

std::map<char, glyph> glyph_map;
unsigned int VAO, VBO;
glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f,
                                  static_cast<float>(SCR_HEIGHT));
gl_shader *shader;
void ft_errorcheck(FT_Error error, const char *message)
{
  if (error)
  {
    const char *ft_error_str = FT_Error_String(error);
    log::error(fmt::format("{} : {}",
                           message,
                           (ft_error_str)
                               ? ft_error_str
                               : "(FreeType returned no error message)"));
  }
}

void init()
{
  log::msg("Glyph init start");
  shader = new gl_shader("src/shader/text.vs", "src/shader/text.fs");

  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f,
                                    static_cast<float>(SCR_HEIGHT));
  shader->use();
  glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1,
                     GL_FALSE, glm::value_ptr(projection));
  CHECKERROR;
  FT_Library ft;

  FT_Error ft_error;
  ft_error = FT_Init_FreeType(&ft);
  ft_errorcheck(ft_error, "Freetype failed to init");

  // cool pixel fonts
  // tobi *
  // proggytiny
  // proggysquare
  // crisp
  // gohu
  // pixelcarnage
  // const char *font_name = "resource/fonts/Hack-Regular.ttf";
  const char *font_name = "resource/fonts/ProggySquare.ttf";
  // const char *font_name = "resource/fonts/CodingFontTobi1.pcf";

  FT_Face face;
  ft_error = FT_New_Face(ft, font_name, 0, &face);
  ft_errorcheck(
      ft_error,
      fmt::format("Freetype failed to load font, {}", font_name).c_str());

  FT_Set_Pixel_Sizes(face, 0, 16);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (unsigned char c = 0; c < 128; c++)
  {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      log::error(fmt::format("failed to load glyph {}", c));
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RED,
                 face->glyph->bitmap.width,
                 face->glyph->bitmap.rows,
                 0,
                 GL_RED,
                 GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    CHECKERROR;

    glyph g = { texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x) };
    glyph_map.insert(std::pair<char, glyph>(c, g));
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  CHECKERROR;

  FT_Done_Face(face);

  FT_Done_FreeType(ft);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  CHECKERROR;
  log::msg("Glyph init end");
}

void render(std::string text, float x, float y, float scale, glm::vec3 color)
{
  shader->use();

  glUniform3f(glGetUniformLocation(shader->ID, "textColor"), color.x, color.y,
              color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);
  // iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++)
  {
    glyph ch = glyph_map[*c];

    float xpos = x + ch.bearing.x * scale;
    float ypos = y - (ch.size.y - ch.bearing.y) * scale;

    float w = ch.size.x * scale;
    float h = ch.size.y * scale;
    // update VBO
    float vertices[6][4] = { { xpos, ypos + h, 0.0f, 0.0f },
                             { xpos, ypos, 0.0f, 1.0f },
                             { xpos + w, ypos, 1.0f, 1.0f },

                             { xpos, ypos + h, 0.0f, 0.0f },
                             { xpos + w, ypos, 1.0f, 1.0f },
                             { xpos + w, ypos + h, 1.0f, 0.0f } };
    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices); // be sure to use glBufferSubData and not glBufferData

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    x += (ch.advance >> 6) * scale;
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace glyph
} // namespace cbt
