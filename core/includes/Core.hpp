/*
** core.hpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 19:09:59 2017 gastal_r
** Last update	Mon Mar 13 00:40:45 2017 gastal_r
*/

#ifndef         _CORE_HPP_
#define         _CORE_HPP_

#include        <dlfcn.h>
#include        <iostream>
#include        "ICore.hh"
#include        "Protocol.hpp"

class           Core : public ICore
{
public:
  Core ();
  virtual       ~Core ();
  Core(const    Core &obj);
  Core &operator=(const Core &obj);

  void          startGame();
  void          initGraphicalLib();
  void          nextGame();

  static void   *Dlopen(const char *filename, int flag);
  static void   *Dlsym(void *handle, const char *symbol);

private:
  int _test;
};


#endif /* !_CORE_HPP_ */
