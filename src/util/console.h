#ifndef CONSOLE_H
#define CONSOLE_H
#include <cstdint>
#include <iostream>
namespace cbt
{
namespace console
{

std::string &get_line_buffer();
void execute_current_buffer();

// TODO overload with various str types
void print_line(std::string); 

void set_active(bool);
bool get_active();
void toggle_active();
void init();
uint32_t update(float dt);
void draw();
void kill();

} // namespace console

} // namespace cbt
#endif
