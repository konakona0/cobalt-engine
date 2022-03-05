#include "parser.h"
#include "sys/log.h"
#include "sys/object.h"
#include "sys/objprc.h"
#include "console.h"
#include <sstream>
#include <vector>

namespace cbt
{
  namespace parser{
    
    // TODO serialize all help text messages

    std::vector<std::string> split(std::string& input);
    void object_handle(std::vector<std::string>& commands);
    void print_help();

    void init() {}
    void update(float dt)
    {

    }
    void kill()
    {

    }

    void parse_command(std::string &input) 
    {
      // people are saying strstr works fine here
      // define vector of keywords for commands 
      // create sub-actions
      // rect topleft_X topleft_Y bottomright_X bottomright_Y COLOR

      // split line into words split by space
      
      // commands
      //  - help
      //  - object <>
      //  - exit

      std::vector<std::string> commands = split(input);

      if (commands[0] == "help")
      {
        console::print_line("help msg");
        return;
      }
      if (commands[0] == "object")
      {
        object_handle(commands);
        return;
      }
      log::warn(fmt::format("command {} not recognized", commands[0]));
    }

    void print_help()
    {

    }

    void object_handle(std::vector<std::string>& commands)
    {
      // commands :
      // - list -- shows list of objects, base objects with index
      //   - active -- active objects 
      //   - base   -- base objects   
      
      if (commands[1] == "create")
      {
        // if no parameters
        if (commands.size() < 3)
        {
          // create blank object 
          auto obj_id = objprc::create_obj();
          console::print_line(
              std::string(fmt::format("object id <{}> added to inactive list", obj_id)));
        }
      }

      if (commands[1] == "list")
      {
        console::print_line("printing inactive objects\n");
        for (auto &i : objprc::get_inactive_objlist())
        {
          console::print_line(std::string(fmt::format
              ("id: [{}] name: \"{}\"", i->get_id(),i->get_name())));
        }

      }

    }

    std::vector<std::string> split(std::string &input)
    {
      
      std::vector<std::string> ret;
      std::string buf;
      std::stringstream ss(input);
      while (std::getline(ss, buf, ' '))
      {
        ret.push_back(std::string(buf));
      }
      return ret;
    }

  }
}
