/*
** LNcurses.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:45:49 2017 gastal_r
** Last update Fri Mar 17 03:21:37 2017 Leo Hubert Froideval
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
  Ncurses::InitPair(9, COLOR_BLACK, COLOR_WHITE);
  Ncurses::InitPair(10, COLOR_WHITE, COLOR_BLACK);
  Ncurses::InitPair(11, COLOR_BLUE, COLOR_BLACK);
  Ncurses::InitPair(12, COLOR_RED, COLOR_BLACK);
  Ncurses::InitPair(13, COLOR_GREEN, COLOR_BLACK);
  Ncurses::InitPair(14, COLOR_MAGENTA, COLOR_BLACK);
  Ncurses::InitPair(15, COLOR_CYAN, COLOR_BLACK);
  Ncurses::InitPair(16, COLOR_YELLOW, COLOR_BLACK);
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
      Ncurses::Attron(COLOR_PAIR(1));
      mvprintw(y, x, "W");
      Ncurses::Attroff(COLOR_PAIR(1));
      break;
    case (arcade::TileType::BLOCK) :
      Ncurses::Attron(COLOR_PAIR(2));
      mvprintw(y, x, "R");
      Ncurses::Attroff(COLOR_PAIR(2));
      break;
    case (arcade::TileType::OBSTACLE) :
      Ncurses::Attron(COLOR_PAIR(3));
      mvprintw(y, x, "G");
      Ncurses::Attroff(COLOR_PAIR(3));
      break;
    case (arcade::TileType::EVIL_DUDE) :
      Ncurses::Attron(COLOR_PAIR(4));
      mvprintw(y, x, "Y");
      Ncurses::Attroff(COLOR_PAIR(4));
      break;
    case (arcade::TileType::EVIL_SHOOT) :
      Ncurses::Attron(COLOR_PAIR(5));
      mvprintw(y, x, "U");
      Ncurses::Attroff(COLOR_PAIR(5));
      break;
    case (arcade::TileType::MY_SHOOT) :
      Ncurses::Attron(COLOR_PAIR(6));
      mvprintw(y, x, "K");
      Ncurses::Attroff(COLOR_PAIR(6));
      break;
    case (arcade::TileType::POWERUP) :
      Ncurses::Attron(COLOR_PAIR(7));
      mvprintw(y, x, "C");
      Ncurses::Attroff(COLOR_PAIR(7));
      break;
    case (arcade::TileType::OTHER) :
      Ncurses::Attron(COLOR_PAIR(8));
      mvprintw(y, x, "M");
      Ncurses::Attroff(COLOR_PAIR(8));
      break;
    }
}

void        LNcurses::aPutText(size_t x, size_t y, const std::string &path,
                    size_t size, arcade::Color color, const std::string &str)
{
  (void)path;
  (void)size;
  switch (color)
    {
    case (arcade::Color::BLACK) :
      Ncurses::Attron(COLOR_PAIR(9));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(9));
      break;
    case (arcade::Color::WHITE) :
      Ncurses::Attron(COLOR_PAIR(10));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(10));
      break;
    case (arcade::Color::BLUE) :
      Ncurses::Attron(COLOR_PAIR(11));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(11));
      break;
    case (arcade::Color::RED) :
      Ncurses::Attron(COLOR_PAIR(12));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(12));
      break;
    case (arcade::Color::GREEN) :
      Ncurses::Attron(COLOR_PAIR(13));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(13));
      break;
    case (arcade::Color::MAGENTA) :
      Ncurses::Attron(COLOR_PAIR(14));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(14));
      break;
    case (arcade::Color::CYAN) :
      Ncurses::Attron(COLOR_PAIR(15));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(15));
      break;
    case (arcade::Color::YELLOW) :
      Ncurses::Attron(COLOR_PAIR(16));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(16));
      break;
    }
}

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
    case (KEY_UP) :
      return (arcade::CommandType::GO_UP);
      break;
    case (KEY_DOWN) :
      return (arcade::CommandType::GO_DOWN);
      break;
    case (KEY_LEFT) :
      return (arcade::CommandType::GO_LEFT);
      break;
    case (KEY_RIGHT) :
      return (arcade::CommandType::GO_RIGHT);
      break;
    case (51) :
      return (arcade::CommandType::PREV_LIB);
      break;
    case(52) :
      return (arcade::CommandType::NEXT_LIB);
      break;
    case(53) :
      return (arcade::CommandType::PREV_GAME);
      break;
    case (54) :
      return (arcade::CommandType::NEXT_GAME);
      break;
    case (57) :
      return (arcade::CommandType::RESTART);
      break;
    case (58) :
      return (arcade::CommandType::MENU);
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
