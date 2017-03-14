/*
** main.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:42:03 2017 gastal_r
** Last update	Tue Mar 14 11:03:40 2017 gastal_r
*/

#include  "Core.hpp"

int       main(int ac, char *av[])
{
  if (ac != 2)
  {
    std::cout << "Need argument" << std::endl;
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
