/*
** core.hpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 19:09:59 2017 gastal_r
** Last update	Tue Mar 14 13:14:40 2017 gastal_r
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
#include        "Gui.hpp"

#define GAME_DIR  "games/"
#define GRAPH_DIR "lib/"

class           Core : public arcade::ICore, public Gui
{
public:
  Core(const std::string &lib);
  virtual       ~Core();

  void          openLib(const std::string &lib);
  void          openGame(const std::string &game);
  void          openLibsDir();
  void          openGamesDir();

  void          startCore();

  void          switchGame(const arcade::MoveType);
  void          switchLib(const arcade::MoveType);
  arcade::IGraph  *getLib() const;

  static void   *Dlsym(void *handle, const char *symbol);
  static void   *Dlopen(const char *filename, int flag);
  static int    Dlclose(void *handle);

private:
  void                  *_graphHandle;
  void                  *_gameHandle;
  arcade::IGraph        *_graph;
  arcade::IGame         *_game;
  std::string           _currentGame;
  std::string           _currentGraph;
  std::vector<std::string> _games;
  std::vector<std::string> _libs;
};


#endif /* !_CORE_HPP_ */
