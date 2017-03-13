/*
** main.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:42:03 2017 gastal_r
** Last update	Mon Mar 13 17:37:37 2017 gastal_r
*/

#include  "Core.hpp"

int       main(int ac, char *av[])
{
  if (ac != 2)
  {
    std::cout << "Need argument" << std::endl;
    return (0);
  }
  Core *core = new Core(std::string(av[1]));
  (void) core;

  return (0);
}
