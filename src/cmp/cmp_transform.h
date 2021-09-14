#include "cmp/cmp_template.h"

namespace cbt
{

class transform : public component
{
public:
  transform() = delete;

protected:
  transform(rj_value val);

private:
  struct traits
  {
    glm::vec3 position;
    float rotation;
    glm::vec3 scale;
  };
};
} // namespace cbt
