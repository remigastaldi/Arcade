/*
** Gui.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 11:01:41 2017 gastal_r
** Last update	Tue Mar 14 15:38:41 2017 gastal_r
*/

#include        "Gui.hpp"

Gui::Gui()
{
  _status = CONTINUE;
}

Gui::~Gui()
{}

void            Gui::setGraph(arcade::IGraph *graph)
{
    _graph = graph;
}

void            Gui::startGui()
{

}

Status          &Gui::getStatus()
{
  return (_status);
}
