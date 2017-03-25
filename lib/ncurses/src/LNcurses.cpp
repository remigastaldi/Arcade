/*
** LNcurses.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:45:49 2017 gastal_r
** Last update	Sat Mar 25 20:32:31 2017 gastal_r
*/

#include          "LNcurses.hpp"

LNcurses::LNcurses()
{}

LNcurses::~LNcurses()
{}

void        LNcurses::aInit(arcade::ICore *, size_t, size_t)
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
  Ncurses::InitPair(N_WHITE, COLOR_WHITE, COLOR_WHITE);
  Ncurses::InitPair(N_RED, COLOR_RED, COLOR_RED);
  Ncurses::InitPair(N_GREEN, COLOR_GREEN, COLOR_GREEN);
  Ncurses::InitPair(N_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
  Ncurses::InitPair(N_BLUE, COLOR_BLUE, COLOR_BLUE);
  Ncurses::InitPair(N_BLACK, COLOR_BLACK, COLOR_BLACK);
  Ncurses::InitPair(N_CYAN, COLOR_CYAN, COLOR_CYAN);
  Ncurses::InitPair(N_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
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

void        LNcurses::printTile(size_t x, size_t y, const LNcurses::NColor &color)
{
  Ncurses::Attron(COLOR_PAIR(color));
  mvprintw(Y_PAD + y, X_PAD + x, "W");
  mvprintw(Y_PAD + y, X_PAD + x + 1, "W");
  Ncurses::Attroff(COLOR_PAIR(color));
}

void        LNcurses::aTile(size_t x, size_t y, arcade::TileType tile, const arcade::CommandType &)
{
  x = x * 2;
  switch (tile)
    {
    case (arcade::TileType::EMPTY) :
      printTile(x, y, _emptyColor);
      break;
    case (arcade::TileType::OBSTACLE) :
      printTile(x, y, _obstacleColor);
      break;
    case (arcade::TileType::BLOCK) :
      printTile(x, y, _blockColor);
      break;
    case (arcade::TileType::EVIL_DUDE) :
      printTile(x, y, _evilDudeColor);
      break;
    case (arcade::TileType::EVIL_SHOOT) :
      printTile(x, y, _evilShootColor);
      break;
    case (arcade::TileType::MY_SHOOT) :
      printTile(x, y, _myShootColor);
      break;
    case (arcade::TileType::POWERUP) :
      printTile(x, y, _powerupColor);
      break;
    case (arcade::TileType::OTHER) :
      printTile(x, y, _otherColor);
      break;
    }
}

LNcurses::NColor  LNcurses::fillColor(const arcade::Color &color)
{
  NColor   n;

  (color == arcade::A_WHITE ? n = NColor::N_WHITE :
   (color == arcade::A_BLUE ? n = NColor::N_BLUE :
    (color == arcade::A_RED ? n = NColor::N_RED :
     (color == arcade::A_GREEN ? n = NColor::N_GREEN :
      (color == arcade::A_MAGENTA ? n = NColor::N_MAGENTA :
       (color == arcade::A_CYAN ? n = NColor::N_CYAN :
         (color == arcade::A_YELLOW ? n = NColor::N_YELLOW : NColor::N_BLACK)))))));
  return (n);
}

void        LNcurses::aAssignTexture(const arcade::TileType tile, const std::string &path, const arcade::Color color)
{
  (void) path;

  switch (tile)
  {
    case arcade::TileType::EMPTY :
      _emptyColor = fillColor(color);
      break;
    case arcade::TileType::BLOCK :
      _blockColor = fillColor(color);
      break;
    case arcade::TileType::OBSTACLE :
      _obstacleColor = fillColor(color);
      break;
    case arcade::TileType::EVIL_DUDE :
      _evilDudeColor = fillColor(color);
      break;
    case arcade::TileType::EVIL_SHOOT :
      _evilShootColor = fillColor(color);
      break;
    case arcade::TileType::MY_SHOOT :
      _myShootColor = fillColor(color);
      break;
    case arcade::TileType::POWERUP :
      _powerupColor = fillColor(color);
      break;
    case arcade::TileType::OTHER :
      _otherColor = fillColor(color);
      break;
    }
}

void        LNcurses::printText(size_t x, size_t y, int color, const std::string &str)
{
  Ncurses::Attron(COLOR_PAIR(color));
  mvprintw(y, x, str.c_str());
  Ncurses::Attroff(COLOR_PAIR(color));
}

void        LNcurses::aPutText(size_t x, size_t y, const arcade::Font &path,
                    size_t size, arcade::Color color, const std::string &str)
{
  (void)path;
  (void)size;
  switch (color)
    {
    case (arcade::Color::A_BLACK) :
      printText(x, y, 9, str);
      break;
    case (arcade::Color::A_WHITE) :
      printText(x, y, 10, str);
      break;
    case (arcade::Color::A_BLUE) :
      printText(x, y, 11, str);
      break;
    case (arcade::Color::A_RED) :
      printText(x, y, 12, str);
      break;
    case (arcade::Color::A_GREEN) :
      printText(x, y, 13, str);
      break;
    case (arcade::Color::A_MAGENTA) :
      printText(x, y, 14, str);
      break;
    case (arcade::Color::A_CYAN) :
      printText(x, y, 15, str);
      break;
    case (arcade::Color::A_YELLOW) :
      printText(x, y, 16, str);
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
  std::this_thread::sleep_for(std::chrono::milliseconds(70));
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
