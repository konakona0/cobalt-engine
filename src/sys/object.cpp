#include "sys/object.h"
#include "sys/log.h"
#include "cmp/cmp_sprite.h"
#include "cmp/cmp_transform.h"
#include "cmp/cmp_template.h"

namespace cbt
{

// TODO serialized next obj ID

static unsigned int next_ID = 0;

object::object(const char *name) 
{ 
  // TODO steps
  // all from console
  // create object archetype
  // spawn object from archetype
  ID = next_ID;
  next_ID++;
  _name = name;
}

object::object(const object &rhs) {}
object::object(rapidjson::Document &doc, const char *name) {}
void object::readComponents(const rj_array &components) 
{

}

void object::init()
{
  for (auto i = 0; i < static_cast<int>(cmp_type::cmp_MAX); i++)
  {
    cmp_list[i] = nullptr;
  }
}

uint32_t object::update(float dt)
{
  for (auto i = 0; i < static_cast<int>(cmp_type::cmp_MAX); i++)
  {
    cmp_list[i]->update(dt);
  }
  return 0;
}

void object::destroy() { destroyed = true; }

void object::purge()
{
  for (unsigned i = 0; i < static_cast<int>(cmp_type::cmp_MAX); i++)
  {
    component **tmp = &cmp_list[i];
    cmp_list[i]     = nullptr;
    delete *tmp;
  }
}

bool object::is_destroyed() const { return destroyed; }

component *object::get_cmp(cmp_type _type) const
{
  return cmp_list[static_cast<int>(_type)];
}


unsigned int object::get_id() const
{
  return ID;
}

const char *object::get_name() const
{
  return _name;
}

void object::add_cmp(component *new_cmp)
{
  auto newcmp_type = new_cmp->get_type();
  if (cmp_list[static_cast<int>(newcmp_type)])
  {
    log::warn("Attempted to assign pre-existing component");
  }
  else
  {
    cmp_list[static_cast<int>(newcmp_type)] = new_cmp;
  }
}

void object::draw()
{
  if (cmp_list[static_cast<int>(cmp_type::transform)] == nullptr)
  {
    log::error(fmt::format("Object {} (ID {}) has no transform, cannot draw",
                           _name, ID));
    return;
  }
  if (cmp_list[static_cast<int>(cmp_type::sprite)] == nullptr)
  {
    log::error(
        fmt::format("Object {} (ID {}) has no sprite, cannot draw", _name, ID));
    return;
  }

  auto tr = GET_CMP(transform);
}

} // namespace cbt
