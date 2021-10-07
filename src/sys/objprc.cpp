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

namespace obj
{

namespace objprc
{

static std::list<std::shared_ptr<object>> active_objlist;

// object archetypes are obj pointers and unsigned int IDs
static std::list<std::pair<std::unique_ptr<object>, uint32_t>> inactive_objlist;

uint32_t init() { return 0; }

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
} // namespace obj
} // namespace cbt
