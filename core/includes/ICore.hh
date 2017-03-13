/*
** ICore.hh for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 12 21:30:45 2017 gastal_r
** Last update	Sun Mar 12 22:05:00 2017 gastal_r
*/

#ifndef         _ICORE_HH_
#define         _ICORE_HH_

class           ICore
{
public:
  virtual       ~ICore () {};
  virtual void  initGraphicalLib() = 0;
  virtual void  nextGame() = 0;
};

#endif           /* !_ICORE_HH_ */
