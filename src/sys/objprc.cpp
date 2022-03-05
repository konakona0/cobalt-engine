//! \brief
//    cobalt engine object processor

#include "sys/objprc.h"
#include "sys/object.h"
#include "cmp/cmp_template.h"
#include <glm/glm.hpp>
#include <memory>
#include "log.h"

namespace cbt
{

namespace objprc
{

std::list<object*> active_objlist;

std::list<object*>& get_active_objlist()
{
  return active_objlist;
}

// object archetypes are obj pointers and unsigned int IDs
std::list<object*> inactive_objlist;

std::list<object*> &get_inactive_objlist()
{
  return inactive_objlist;
}

unsigned int create_obj()
{
  // blank object
  
  auto obj = new object("unnamed object");
  inactive_objlist.push_front(obj);
  return obj->get_id();
}

uint32_t init() 
{ 
  // TODO stream from json
  return 0; 
}

uint32_t update(float dt)
{
  for (auto &i : active_objlist)
  {
    if (!i->update(dt)) return 0;
  }
  for (auto &i : active_objlist) i->draw();
  return 1;
}
uint32_t exit()
{
  // TODO free all objects
  return 0;
}


} // namespace objprc
} // namespace cbt
