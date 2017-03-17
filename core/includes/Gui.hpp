/*
** Gui.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 10:55:17 2017 gastal_r
** Last update	Fri Mar 17 02:56:38 2017 gastal_r
*/

#ifndef         _GUI_HPP_
#define         _GUI_HPP_

#include        <vector>
#include        "IGraph.hh"
#include        "ICore.hh"

enum Status
{
  CONTINUE,
  EXIT
};

class           Gui
{
public:
  Gui ();
  virtual       ~Gui ();

  void          setGraph(arcade::IGraph *graph);
  void          affGui();
  void          affName();
  void          affDispLibs();
  void          affDispGames();

  const std::string   getName(arcade::ICore &);
  void                listGame(arcade::ICore &, size_t);
  const std::string   chooseGame(arcade::ICore &);

  const Status  &getStatus();
  void          setStatus(const Status status) {_status = status; }

  void          guiSetLibs(const std::vector<std::string> libs) {_libs = libs;}
  void          guiSetCurrentGraph(const std::string &graph) {_currentGraph = graph;}
  void          guiSetGames(const std::vector<std::string> games) {_games = games;}
  void          guiSetCurrentGame(const std::string &game) {_currentGame = game;}
  void          guiSetPlayer(const std::string &player) {_player = player;}
  void          guiSetBestScore(std::string score) {_bestScore = score;}

private:
  arcade::IGraph  *_graph;
  Status          _status;
  std::string               _currentGame;
  std::string               _currentGraph;
  std::vector<std::string>  _games;
  std::vector<std::string>  _libs;
  std::string               _player;
  std::string               _bestScore;
};


#endif /* !_GUI_HPP_ */
