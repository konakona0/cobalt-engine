#ifndef INPUT_H
#define INPUT_H
#pragma once
#include <cstdint>
namespace cbt
{
namespace input
{
void init();
bool key_down(int);
bool key_held(int);
bool key_up(int);
uint32_t update(float dt);
} // namespace input
} // namespace cbt
#endif
