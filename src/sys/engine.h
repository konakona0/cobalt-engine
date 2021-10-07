#ifndef ENGINE_H
#define ENGINE_H
#pragma once
// engine definition

//
// static engine with Engine::Engine instance

#include <cstdint>
namespace cbt
{
namespace engine
{
float get_dt();
uint32_t init();
uint32_t update();
uint32_t exit();
} // namespace engine
} // namespace cbt
#endif
