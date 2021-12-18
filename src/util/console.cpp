#include "util/console.h"
#include <iostream>
#include <list>
#include "glyph.h"
#include "sys/log.h"

namespace cbt
{
namespace console
{
// const uint32_t CONSOLE_MAX_LENGTH_CURLINE = 1024;
bool active;
std::string console_buffer;
std::list<std::string> history;

unsigned history_display_max   = 10;
float blinking_cursor_duration = 0.4f;
float blinking_cursor_timer    = 0.f;
bool blinking_cursor_blink     = false;

glm::vec2 console_position;
glm::vec3 console_color;

void return_current_line()
{
  log::msg("returning current console line");
  history.push_front(std::string(console_buffer));
  console_buffer.clear();
}

std::string &get_history_entry(int index)
{
  std::list<std::string>::iterator it = history.begin();
  std::advance(it, index);
  if (it == history.end())
  {
    log::error("attempted to access invalid index of console history");
    return *(history.begin());
  }
  return *it;
}

std::string &get_line_buffer() { return console_buffer; }

void set_active(bool val)
{
  log::msg(fmt::format("console active: {}", active));
  active = val;
}
void init()
{
  history.clear();

  console_buffer   = "";
  active           = false;
  console_position = { 24, 12 };
  console_color    = { 0.5f, 0.8f, 0.2f };

  glyph::init();
}
uint32_t update(float dt)
{
  // update blinking cursor
  if (blinking_cursor_timer <= 0.f)
  {
    blinking_cursor_timer = blinking_cursor_duration;
    blinking_cursor_blink = !blinking_cursor_blink;
  }
  blinking_cursor_timer -= dt;
  return 1;
}
void draw()
{
  if (active)
  {
    char blinky = blinking_cursor_blink ? '|' : ' ';
    glyph::render(fmt::format("{}{}", console_buffer, blinky),
                  console_position.x, console_position.y, 1.f, console_color);
    for (size_t i = 0; i < history_display_max; ++i)
    {
      if (i < history.size())
        glyph::render(get_history_entry(i), console_position.x,
                      (console_position.y + ((i + 1) * (16))), 1.f,
                      console_color * 0.8f);
    }
  }
}
bool get_active() { return active; }
void toggle_active()
{
  active = !active;
  log::msg(fmt::format("console active: {}", active));
}
void kill() {}
} // namespace console

} // namespace cbt
