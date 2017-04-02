/*
** LNcurses.hpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 19:10:52 2017 gastal_r
** Last update	Sun Apr 02 01:33:52 2017 gastal_r
*/

#ifndef       _LNcurses_HPP_
#define       _LNcurses_HPP_

#include        <thread>
#include        <chrono>
#include      "IGraph.hh"
#include      "Ncurses.hpp"

class LNcurses : public arcade::IGraph
{
  enum NColor
  {
    UNDIFINED,
    N_WHITE,
    N_RED,
    N_GREEN,
    N_YELLOW,
    N_BLUE,
    N_BLACK,
    N_CYAN,
    N_MAGENTA
  };

public:
  LNcurses ();
  virtual ~LNcurses ();

  void        aInit(arcade::ICore *, size_t, size_t);
  void        aClose();

  void        printTile(size_t x, size_t y, LNcurses::NColor color);
  void        aTile(size_t, size_t, arcade::TileType, arcade::CommandType);
  void        aTile(size_t, size_t, void *){};

  NColor      fillColor(arcade::Color color);
  void        aAssignTexture(arcade::TileType tile, const std::string &path, arcade::Color color);
  void        *aGetTexture(const std::string &) {return (NULL);}

  void        printText(size_t x, size_t y, int color, const std::string &str);
  void        aPutText(size_t, size_t, arcade::Font, size_t, arcade::Color, const std::string &);

  void        aClear();
  void        aRefresh();
  std::string   aChar();
  arcade::CommandType aCommand();

private:
  WINDOW	*_win;
  NColor   _emptyColor;
  NColor   _blockColor;
  NColor   _obstacleColor;
  NColor   _evilDudeColor;
  NColor   _evilShootColor;
  NColor   _myShootColor;
  NColor   _powerupColor;
  NColor   _otherColor;
};

#endif        /* !_LNcurses_HPP_ */
