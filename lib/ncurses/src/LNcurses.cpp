/*
** LNcurses.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:45:49 2017 gastal_r
** Last update	Wed Mar 15 10:29:21 2017 gastal_r
*/

#include          "LNcurses.hpp"

LNcurses::LNcurses()
{}

LNcurses::~LNcurses()
{}

void        LNcurses::aInit(size_t, size_t)
{
  std::cout << "INIT LIB" << '\n';
  Ncurses::Newterm(NULL, stderr, stdin);
  Ncurses::Noecho();
  Ncurses::Cbreak();
  Ncurses::CursSet(0);
  Ncurses::Keypad(stdscr, TRUE);
  Ncurses::Nodelay(stdscr, TRUE);
  
  Ncurses::InitPair(1, COLOR_WHITE, COLOR_WHITE);
  Ncurses::InitPair(2, COLOR_GREEN, COLOR_GREEN);
  Ncurses::InitPair(3, COLOR_RED, COLOR_RED);
  Ncurses::InitPair(4, COLOR_BLACK, COLOR_WHITE);
  Ncurses::InitPair(5, COLOR_RED, COLOR_BLACK);
  Ncurses::InitPair(6, COLOR_WHITE, COLOR_BLACK);
  Ncurses::InitPair(7, COLOR_MAGENTA, COLOR_MAGENTA);
}

void        LNcurses::aClose()
{
  Ncurses::Endwin();
}

void        LNcurses::aTile(size_t, size_t, arcade::TileType)
{}

void        LNcurses::aPutText(size_t, size_t, const std::string &,
                    size_t, arcade::Color, const std::string &)
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
