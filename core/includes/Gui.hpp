/*
** Gui.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 10:55:17 2017 gastal_r
** Last update	Wed Mar 15 13:34:55 2017 gastal_r
*/

#ifndef         _GUI_HPP_
#define         _GUI_HPP_

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

  Status        &getStatus();
  void          setStatus(const Status status) {_status = status; }
private:
  arcade::IGraph *_graph;
  Status          _status;
};


#endif /* !_GUI_HPP_ */
