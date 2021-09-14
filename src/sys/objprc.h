// combination of object manager and object class

#pragma once
#include <cstdint>
#include <list>
namespace cbt
{
namespace obj
{
namespace objman
{
void spawn_object(uint32_t);
uint32_t init();
uint32_t update(float);
uint32_t exit();

} // namespace objman
} // namespace obj
} // namespace cbt
