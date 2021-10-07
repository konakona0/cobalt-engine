#include <cstdint>
namespace cbt
{
namespace texprc
{
class Texture
{
public:
  Texture(const char *filepath);
  void bind();

private:
  void load(const char *filepath);
  int width;
  int height;
  int nrChannels;
  const char *filename;
  unsigned int gl_texture_ID;
};

void init();

} // namespace texprc

} // namespace cbt
