/*
** main.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:42:03 2017 gastal_r
** Last update	Sat Mar 11 23:51:37 2017 gastal_r
*/

#include  "Core.hpp"

int       main(int ac, char *av[])
{
  void    *handle;
  void    (*fptr)(void);
  void    (*fptr2)(void);

  handle = Core::Dlopen("libs/lib_arcade_ncurses.so", RTLD_LOCAL | RTLD_LAZY);
  *(void **)(&fptr) = Core::Dlsym(handle, "test");
  handle = Core::Dlopen("games/lib_arcade_snake.so", RTLD_LOCAL | RTLD_LAZY);
  *(void **)(&fptr2) = Core::Dlsym(handle, "play");

  (*fptr)();
  (*fptr2)();

  return (0);
}
