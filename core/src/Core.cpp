/*
** core.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 22:59:05 2017 gastal_r
** Last update	Mon Mar 13 00:41:19 2017 gastal_r
*/

#include        "Core.hpp"

Core::Core()
{}

Core::~Core()
{}

void          Core::nextGame()
{
  std::cout << "NEXT_GAME" << '\n';
}


void            Core::initGraphicalLib()
{
  void    *handle;
  void    (*grap)(void);

  handle = Core::Dlopen("libs/lib_arcade_ncurses.so", RTLD_LOCAL | RTLD_LAZY);
  *(void **)(&grap) = dlsym(handle, "test");

  (*grap)();
}

void          Core::startGame()
{
  void    *handle;
  void    (*play)(ICore &);

  handle = Core::Dlopen("games/lib_arcade_snake.so", RTLD_LOCAL | RTLD_LAZY);
  *(void **)(&play) = Core::Dlsym(handle, "play");

  (*play)(*this);
}

void            *Core::Dlopen(const char *filename, int flag)
{
  return (dlopen(filename, flag));
}

void            *Core::Dlsym(void *handle, const char *symbol)
{
  return (dlsym(handle, symbol));
}
