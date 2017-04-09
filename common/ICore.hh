/*
** ICore.hh for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 12 21:30:45 2017 gastal_r
** Last update	Sun Apr 09 22:41:12 2017 gastal_r
*/

#ifndef           _ICORE_HH_
#define           _ICORE_HH_

#include          <dlfcn.h>
#include          <iostream>
#include          <vector>
#include          <string>
#include          "../core/includes/Gui.hpp"
#include          "../core/includes/Save.hpp"
#include          "Protocol.hpp"
#include          "IGraph.hh"
#include          "IGame.hh"
#include	        "Exception.hpp"
#include          "File.hpp"

#define CORE_RES  "core/res/"


namespace	        arcade
{
  class             ICore
  {
  public:
    virtual         ~ICore () {};

    virtual void    switchGame(arcade::CommandType) = 0;
    virtual void    switchLib(arcade::CommandType) = 0;

    virtual void    refreshGui() = 0;

    virtual void    gameWin() = 0;
    virtual void    gameOver() = 0;

    virtual Save                     &getSave() = 0;
    virtual std::vector<std::string> getSounds() = 0;
    virtual arcade::IGraph           *getLib() const = 0;
    virtual const std::string        &getCurrentGame() const = 0;

    virtual void    saveScore(size_t score) = 0;
    virtual void    setScore(const std::string &score) = 0;
  };
}

#endif           /* !_ICORE_HH_ */
