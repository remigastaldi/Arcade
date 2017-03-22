/*
** LNcurses.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:45:49 2017 gastal_r
** Last update	Wed Mar 22 10:13:56 2017 gastal_r
*/

#include          "LNcurses.hpp"

LNcurses::LNcurses()
{}

LNcurses::~LNcurses()
{}

void        LNcurses::aInit(size_t, size_t)
{
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
  x = x * 2 - 1;
  switch (tile)
    {
    case (arcade::TileType::EMPTY) :
      Ncurses::Attron(COLOR_PAIR(1));
      mvprintw(Y_PAD + y, X_PAD + x, "W");
      mvprintw(Y_PAD + y, X_PAD + x + 1, "W");
      Ncurses::Attroff(COLOR_PAIR(1));
      break;
    case (arcade::TileType::OBSTACLE) :
      Ncurses::Attron(COLOR_PAIR(2));
      mvprintw(Y_PAD + y, X_PAD + x, "R");
      mvprintw(Y_PAD + y, X_PAD + x + 1, "R");
      Ncurses::Attroff(COLOR_PAIR(2));
      break;
    case (arcade::TileType::BLOCK) :
      Ncurses::Attron(COLOR_PAIR(3));
      mvprintw(Y_PAD + y, X_PAD + x, "G");
      mvprintw(Y_PAD + y, X_PAD + x + 1, "G");
      Ncurses::Attroff(COLOR_PAIR(3));
      break;
    case (arcade::TileType::EVIL_DUDE) :
      Ncurses::Attron(COLOR_PAIR(4));
      mvprintw(Y_PAD + y, X_PAD + x, "Y");
      mvprintw(Y_PAD + y, X_PAD + x + 1, "Y");
      Ncurses::Attroff(COLOR_PAIR(4));
      break;
    case (arcade::TileType::EVIL_SHOOT) :
      Ncurses::Attron(COLOR_PAIR(5));
      mvprintw(Y_PAD + y, X_PAD + x, "U");
      mvprintw(Y_PAD + y, X_PAD + x + 1, "U");
      Ncurses::Attroff(COLOR_PAIR(5));
      break;
    case (arcade::TileType::MY_SHOOT) :
      Ncurses::Attron(COLOR_PAIR(6));
      mvprintw(Y_PAD + y, X_PAD + x, "K");
      mvprintw(Y_PAD + y, X_PAD + x + 1, "K");
      Ncurses::Attroff(COLOR_PAIR(6));
      break;
    case (arcade::TileType::POWERUP) :
      Ncurses::Attron(COLOR_PAIR(7));
      mvprintw(Y_PAD + y, X_PAD + x, "C");
      mvprintw(Y_PAD + y, X_PAD + x + 1, "C");
      Ncurses::Attroff(COLOR_PAIR(7));
      break;
    case (arcade::TileType::OTHER) :
      Ncurses::Attron(COLOR_PAIR(8));
      mvprintw(Y_PAD + y, X_PAD + x, "M");
      mvprintw(Y_PAD + y, X_PAD + x + 1, "M");
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
    case (arcade::Color::A_BLACK) :
      Ncurses::Attron(COLOR_PAIR(9));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(9));
      break;
    case (arcade::Color::A_WHITE) :
      Ncurses::Attron(COLOR_PAIR(10));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(10));
      break;
    case (arcade::Color::A_BLUE) :
      Ncurses::Attron(COLOR_PAIR(11));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(11));
      break;
    case (arcade::Color::A_RED) :
      Ncurses::Attron(COLOR_PAIR(12));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(12));
      break;
    case (arcade::Color::A_GREEN) :
      Ncurses::Attron(COLOR_PAIR(13));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(13));
      break;
    case (arcade::Color::A_MAGENTA) :
      Ncurses::Attron(COLOR_PAIR(14));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(14));
      break;
    case (arcade::Color::A_CYAN) :
      Ncurses::Attron(COLOR_PAIR(15));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(15));
      break;
    case (arcade::Color::A_YELLOW) :
      Ncurses::Attron(COLOR_PAIR(16));
      mvprintw(y, x, str.c_str());
      Ncurses::Attroff(COLOR_PAIR(16));
      break;
    }
}

void            LNcurses::aClear()
{
  Ncurses::Clear();
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
    case (KEY_UP) :
      return (arcade::CommandType::GO_UP);
    case (KEY_DOWN) :
      return (arcade::CommandType::GO_DOWN);
    case (KEY_LEFT) :
      return (arcade::CommandType::GO_LEFT);
    case (KEY_RIGHT) :
      return (arcade::CommandType::GO_RIGHT);
    case (50) :
      return (arcade::CommandType::PREV_LIB);
    case(51) :
      return (arcade::CommandType::NEXT_LIB);
    case(52) :
      return (arcade::CommandType::PREV_GAME);
    case (53) :
      return (arcade::CommandType::NEXT_GAME);
    case (56) :
      return (arcade::CommandType::RESTART);
    case (57) :
      return (arcade::CommandType::MENU);
    case (10) :
      return (arcade::CommandType::PLAY);
    }
  return (arcade::CommandType::UNDEFINED);
}

std::string   LNcurses::aChar()
{
  std::string input;

  Ncurses::Nodelay(stdscr, FALSE);
  int value = Ncurses::Getch();
  switch (value)
  {
    case 127 :
      input = "BACKSPACE";
      break;
    case 10 :
      input = "ENTER";
      break;
    case 27 :
      input = "ESCAPE";
      break;
    default :
      input = std::string(1, value);
  }
  Ncurses::Nodelay(stdscr, TRUE);
  return (input);
}

extern "C"
{
  LNcurses        *createGraph()
  {
    return (new LNcurses());
  }

  void            deleteGame(arcade::IGraph *graph)
  {
    delete(graph);
  }
}
