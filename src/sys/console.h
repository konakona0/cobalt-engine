#ifndef CONSOLE_H
#define CONSOLE_H
#include <cstdint>
namespace cbt
{
namespace console
{

void init();
uint32_t update(float dt);
void draw();
void kill();

} // namespace console

} // namespace cbt
#endif
