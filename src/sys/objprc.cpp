//! \brief
//    cobalt engine object processor

#include "sys/objprc.h"
#include "cmp/cmp_template.h"
#include <memory>
#include "log.h"

namespace cbt
{

namespace obj
{

// object class
class object
{
public:
  uint32_t update(float);
  void draw();

private:
  // component list
  // TODO support chained objects later,
  // just lock one component type for now
  // std::vector<std::shared_ptr<cbt::component>> ;
  cbt::component *cmp_list[cbt::cmp_MAX];

  // new approach: no more unique/global traits
  // if ANY component is altered, it will be registered as a new
  // object, in turn a new archetype, and be serialized as such
  object *archetype_origin_ = nullptr;
};

uint32_t object::update(float dt)
{
  for (auto i = 0; i < cbt::cmp_MAX; i++) { cmp_list[i]->update(dt); }
  return 0;
}

void object::draw()
{

  // TODO
  //  - check for invalids (no sprite/transform)
  //  - send transform data and texture data to renderer
}

namespace objman
{

static std::list<std::shared_ptr<object>> active_objlist;

// object archetypes are obj pointers and unsigned int IDs
static std::list<std::pair<std::unique_ptr<object>, uint32_t>> inactive_objlist;

uint32_t init()
{ // TODO read in objects from a json somewhere hoo hoo
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
} // namespace objman
} // namespace obj
} // namespace cbt
