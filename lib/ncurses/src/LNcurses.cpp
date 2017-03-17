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
  _win = Ncurses::Subwin(stdscr, 60, 60, 1, 1);
  ESCDELAY = 0;

  Ncurses::StartColor();
  Ncurses::InitPair(1, COLOR_WHITE, COLOR_WHITE);
  Ncurses::InitPair(2, COLOR_RED, COLOR_RED);
  Ncurses::InitPair(3, COLOR_GREEN, COLOR_GREEN);
  Ncurses::InitPair(4, COLOR_YELLOW, COLOR_YELLOW);
  Ncurses::InitPair(5, COLOR_BLUE, COLOR_BLUE);
  Ncurses::InitPair(6, COLOR_BLACK, COLOR_BLACK);
  Ncurses::InitPair(7, COLOR_CYAN, COLOR_CYAN);
  Ncurses::InitPair(8, COLOR_MAGENTA, COLOR_MAGENTA);
}

void        LNcurses::aClose()
{
  Ncurses::Endwin();
}

void        LNcurses::aTile(size_t x, size_t y, arcade::TileType tile)
{
  switch (tile)
    {
    case (arcade::TileType::EMPTY) :
      attron(COLOR_PAIR(1));
      mvprintw(y, x, "W");
      attroff(COLOR_PAIR(1));
      break;
    case (arcade::TileType::BLOCK) :
      attron(COLOR_PAIR(2));
      mvprintw(y, x, "R");
      attroff(COLOR_PAIR(2));
      break;
    case (arcade::TileType::OBSTACLE) :
      attron(COLOR_PAIR(3));
      mvprintw(y, x, "G");
      attroff(COLOR_PAIR(3));
      break;
    case (arcade::TileType::EVIL_DUDE) :
      attron(COLOR_PAIR(4));
      mvprintw(y, x, "Y");
      attroff(COLOR_PAIR(4));
      break;
    case (arcade::TileType::EVIL_SHOOT) :
      attron(COLOR_PAIR(5));
      mvprintw(y, x, "U");
      attroff(COLOR_PAIR(5));
      break;
    case (arcade::TileType::MY_SHOOT) :
      attron(COLOR_PAIR(6));
      mvprintw(y, x, "K");
      attroff(COLOR_PAIR(6));
      break;
    case (arcade::TileType::POWERUP) :
      attron(COLOR_PAIR(7));
      mvprintw(y, x, "C");
      attroff(COLOR_PAIR(7));
      break;
    case (arcade::TileType::OTHER) :
      attron(COLOR_PAIR(8));
      mvprintw(y, x, "M");
      attroff(COLOR_PAIR(8));
      break;
    }
}

void        LNcurses::aPutText(size_t, size_t, const std::string &,
                    size_t, arcade::Color, const std::string &)
{}

void        LNcurses::aRefresh()
{
  Ncurses::Wrefresh(_win);
}

arcade::CommandType	LNcurses::aCommand()
{
  switch(Ncurses::Getch())
    {
    case (27) :
      return (arcade::CommandType::ESCAPE);
      break;
    }
}

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
