#ifndef OBJECT_H
#define OBJECT_H
#pragma once
#include "cmp/cmp_template.h"
#include "cmp/cmp_sprite.h"
#include "cmp/cmp_transform.h"

//#define GET_CMP(q) comp_helper_fnc<q>(cmp_type::q)
#define GET_CMP(tp) comp_helper_fnc<tp>(cmp_type::tp)

namespace cbt
{

typedef rapidjson::GenericArray<false,
                                rapidjson::GenericValue<rapidjson::UTF8<>>>
    rj_array;
// object class
class object
{
public:
  object() = delete;
  object(const char *);
  object(const object &);
  object(rapidjson::Document &, const char *);
  void readComponents(const rj_array &);
  virtual ~object() {}

  void init();
  uint32_t update(float);
  void destroy();
  void purge();

  bool is_destroyed() const;

  void draw();

  unsigned int get_id() const;
  const char *get_name() const;

  component *get_cmp(cmp_type) const;

  template <typename T>
  T *comp_helper_fnc(cmp_type type)
  {
    return dynamic_cast<T *>(get_cmp(type));
  }
protected:
  void add_cmp(component *new_cmp);
private:
  // component list
  // TODO support chained objects later,
  // just lock one component type for now
  // std::vector<std::shared_ptr<cbt::component>> ;
  cbt::component *cmp_list[static_cast<int>(cbt::cmp_type::cmp_MAX)];

  // new approach: no more unique/global traits
  // if ANY component is altered, it will be registered as a new
  // object, in turn a new archetype, and be serialized as such
  object *archetype_origin_ = nullptr;


  const char *_name;
  unsigned int ID;
  bool destroyed;
};
} // namespace cbt
#endif
