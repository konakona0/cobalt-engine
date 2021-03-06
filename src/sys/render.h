#ifndef RENDERER_H
#define RENDERER_H
#pragma once
#include <cstdint>
#include <common/gl_shader.h>

#define SCR_WIDTH 1280
#define SCR_HEIGHT 720

typedef class GLFWwindow GLFWwindow;

namespace cbt
{
namespace renderer
{
gl_shader get_default_shader();
GLFWwindow *get_glfw_window();
void init();
void draw();
uint32_t update();
void kill();
} // namespace renderer
} // namespace cbt
#endif
