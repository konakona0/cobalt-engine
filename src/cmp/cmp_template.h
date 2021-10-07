#ifndef CMP_TEMPLATE_H
#define CMP_TEMPLATE_H
#pragma once
#include <cstdint>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/ostreamwrapper.h>
#include <glm/glm.hpp>

// forward declaration
typedef class object object;

/// \brief custom typedef for writing rapidjson object
typedef rapidjson::PrettyWriter<rapidjson::StringBuffer> &rj_writer;

/// \brief custom typedef for readonly rapidjson object
typedef const rapidjson::Value &rj_value;

namespace cbt
{
enum class cmp_type
{
  transform,
  sprite,
  physics,
  collider,
  script,
  cmp_MAX
};

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
  object *parent_;

private:
  cmp_type type_;
  friend class object;
};
} // namespace cbt
#endif
