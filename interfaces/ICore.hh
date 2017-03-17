/*
** ICore.hh for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 12 21:30:45 2017 gastal_r
** Last update	Fri Mar 17 03:56:05 2017 gastal_r
*/

#ifndef           _ICORE_HH_
#define           _ICORE_HH_

#include         <string>
#include         "Save.hpp"
#include "IGraph.hh"

namespace	        arcade
{
  enum MoveType
  {
    NEXT,
    PREV
  };
  class             ICore
  {
  public:
    virtual         ~ICore () {};

    virtual void    switchGame(const arcade::CommandType) = 0;
    virtual void    switchLib(const arcade::CommandType) = 0;
    virtual void    refreshGui() = 0;
    virtual Save    &getSave() = 0;
    virtual arcade::IGraph  *getLib() const = 0;
  };
}

#endif           /* !_ICORE_HH_ */
