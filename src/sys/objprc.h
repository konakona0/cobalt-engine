#ifndef OBJPRC_H
#define OBJPRC_H
// combination of object manager and object class

#pragma once
#include <cstdint>
#include <list>
#include "cmp/cmp_template.h"
#include "sys/object.h"
namespace cbt
{
// object class
namespace objprc
{
unsigned int create_obj();
void spawn_object(uint32_t);

std::list<object*> &get_active_objlist();
std::list<object*> &get_inactive_objlist();

uint32_t init();
uint32_t update(float);
uint32_t exit();

} // namespace objprc
} // namespace cbt
#endif
