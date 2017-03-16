/*
** Gui.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 10:55:17 2017 gastal_r
** Last update	Thu Mar 16 14:55:07 2017 gastal_r
*/

#ifndef         _GUI_HPP_
#define         _GUI_HPP_

#include        <vector>
#include        "IGraph.hh"

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
  void          startGui();
  void          affDispLibs(std::vector<std::string> , std::string);
  void          affDispGames(std::vector<std::string> , std::string);

  Status        &getStatus();
  void          setStatus(const Status status) {_status = status; }

private:
  arcade::IGraph *_graph;
  Status          _status;
};


#endif /* !_GUI_HPP_ */
