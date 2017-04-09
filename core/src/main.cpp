/*
** main.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:42:03 2017 gastal_r
** Last update	Sun Apr 09 15:07:13 2017 gastal_r
*/

#include  "Core.hpp"

int       main(int ac, char *av[])
{
  if (ac != 2)
  {
    std::cout << "Usage : ./arcade lib/libname"  << std::endl;
    return (0);
  }
  try
  {
    std::string filename(av[1]);
    Core  core(filename);
    core.startCore();
  }
  catch (std::exception const &error)
  {
    std::cerr << "Error: " << error.what() << std::endl;
    return (-1);
  }
  return (0);
}
