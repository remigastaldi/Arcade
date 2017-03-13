/*
** core.hpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 19:09:59 2017 gastal_r
** Last update	Mon Mar 13 17:26:38 2017 gastal_r
*/

#ifndef         _CORE_HPP_
#define         _CORE_HPP_

#include        <dlfcn.h>
#include        <iostream>
#include        <vector>
#include        "File.hpp"
#include        "ICore.hh"
#include        "IGraph.hh"
#include        "IGame.hh"

class           Core : public arcade::ICore
{
public:
  Core(std::string lib);
  virtual       ~Core();

  void          openLib(std::string lib);
  void          openGame(std::string game);
  void          openLibsDir();
  void          openGamesDir();

  void          switchGame(arcade::MoveType);
  void          changeLib(arcade::MoveType);
  arcade::IGraph  *getLib();

  static void   *Dlopen(const char *filename, int flag);
  static void   *Dlsym(void *handle, const char *symbol);

private:
  arcade::IGraph        *_graph;
  arcade::IGame         *_game;
  std::vector<std::string> _games;
  std::vector<std::string> _libs;
};


#endif /* !_CORE_HPP_ */
