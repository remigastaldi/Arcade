/*
** main.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:42:03 2017 gastal_r
** Last update	Sun Mar 12 17:27:23 2017 gastal_r
*/

#include  "Core.hpp"

int       main(int ac, char *av[])
{
  (void)ac;
  (void)av;
  void    *handle;
  void    (*grap)(void);
  void    (*play)(void);

  handle = Core::Dlopen("libs/lib_arcade_ncurses.so", RTLD_LOCAL | RTLD_LAZY);
  *(void **)(&grap) = dlsym(handle, "test");
  handle = Core::Dlopen("games/lib_arcade_snake.so", RTLD_LOCAL | RTLD_LAZY);
  *(void **)(&play) = Core::Dlsym(handle, "play");

  (*play)();
  (*grap)();

  return (0);
}
