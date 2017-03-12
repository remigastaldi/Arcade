/*
** core.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 22:59:05 2017 gastal_r
** Last update	Sat Mar 11 23:01:26 2017 gastal_r
*/

#include        "Core.hpp"

void            *Core::Dlopen(const char *filename, int flag)
{
  return (dlopen(filename, flag));
}

void            *Core::Dlsym(void *handle, const char *symbol)
{
  return (dlsym(handle, symbol));
}
