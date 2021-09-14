#pragma once
#include <cstdint>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/ostreamwrapper.h>
#include <glm/glm.hpp>

/// \brief custom typedef for writing rapidjson object
typedef rapidjson::PrettyWriter<rapidjson::StringBuffer> &rj_writer;

/// \brief custom typedef for readonly rapidjson object
typedef const rapidjson::Value &rj_value;

namespace cbt
{
enum cmp_type
{
  cmp_transform,
  cmp_sprite,
  cmp_physics,
  cmp_collider,
  cmp_script,
  cmp_MAX
};

// TODO
//
// wtf do we do about unique/global attributes
// should there be a blank void* in here that can be overridden by any
// component, since they will always have one
class component
{
public:
  cmp_type get_type() const { return type_; }

  virtual component *clone() const = 0;

  virtual void serialize(rj_writer)  = 0;
  virtual void deserialize(rj_value) = 0;

  virtual void load()               = 0;
  virtual void init()               = 0;
  virtual uint32_t update(float dt) = 0;
  virtual void exit()               = 0;
  virtual void unload()             = 0;

protected:
  component() = delete;
  component(cmp_type type) : type_(type) {}
  virtual ~component() {}

private:
  cmp_type type_;
};
} // namespace cbt
