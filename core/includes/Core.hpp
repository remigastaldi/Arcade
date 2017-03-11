/*
** core.hpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 19:09:59 2017 gastal_r
** Last update	Sat Mar 11 23:40:25 2017 gastal_r
*/

#ifndef         _CORE_HPP_
#define         _CORE_HPP_
#include        <dlfcn.h>

class           Core
{
public:
  Core ();
  virtual       ~Core ();
  Core(const    Core &obj);
  Core &operator=(const Core &obj);

  static void   *Dlopen(const char *filename, int flag);
  static void   *Dlsym(void *handle, const char *symbol);

private:
  /* data */
};


#endif /* !_CORE_HPP_ */
