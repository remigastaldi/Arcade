/*
** LNcurses.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:45:49 2017 gastal_r
** Last update	Mon Mar 13 23:01:13 2017 gastal_r
*/

#include          "LNcurses.hpp"

LNcurses::LNcurses()
{}

LNcurses::~LNcurses()
{}

void        LNcurses::aInit(size_t, size_t)
{}

void        LNcurses::aClose()
{
  std::cout << "CLOSE LIB" << '\n';
}

void        LNcurses::aTile(size_t, size_t, arcade::TileType)
{}

void        LNcurses::aRefresh()
{}

extern "C"
{
  LNcurses        *createGraph()
  {
    std::cout << "GRAPH" << '\n';
    return (new LNcurses());
  }

  void            deleteGame(arcade::IGraph *graph)
  {
    delete(graph);
  }
}
