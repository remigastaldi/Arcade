/*
** core.hpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 19:09:59 2017 gastal_r
** Last update	Sat Apr 01 23:43:11 2017 gastal_r
*/

#ifndef         _CORE_HPP_
#define         _CORE_HPP_

#include        "ICore.hh"

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

  void          setGuiData();
  void          refreshGui() { affGui();}
  void          setScore(const std::string &score) { guiSetScore(score);}
  void          startCore();
  void          coreLoop();

  void          chooseGameMenu();
  void          switchGame(arcade::CommandType);
  void          switchLib(arcade::CommandType);
  void          saveScore(size_t score);
  Save            &getSave() { return (_save);}
  arcade::IGraph  *getLib() const;

  static void   *Dlsym(void *handle, const char *symbol);
  static void   *Dlopen(const char *filename, int flag);
  static int    Dlclose(void *handle);

private:
  std::string           _player;
  void                  *_graphHandle;
  void                  *_gameHandle;
  arcade::IGraph        *_graph;
  arcade::IGame         *_game;
  std::string           _currentGame;
  std::string           _currentGraph;
  std::vector<std::string> _games;
  std::vector<std::string> _libs;
  Save                  _save;
};


#endif /* !_CORE_HPP_ */
