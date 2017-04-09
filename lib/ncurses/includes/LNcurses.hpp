/*
** LNcurses.hpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 19:10:52 2017 gastal_r
** Last update	Sun Apr 09 15:39:07 2017 gastal_r
*/

#ifndef       _LNcurses_HPP_
#define       _LNcurses_HPP_

#include        <thread>
#include        <chrono>
#include        "IGraph.hh"
#include        "Ncurses.hpp"
#include        "Sound.hpp"

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

  class         Data
  {
  public:
    int         x;
    int         y;
    int         speed;
    int         nbf;
    int         cf;
    arcade::TileType    type;
    arcade::CommandType dir;
  };

public:
  LNcurses ();
  virtual ~LNcurses () {};

  void        aInit(arcade::ICore *, size_t, size_t);
  void        aClose();

  void        printTile(size_t x, size_t y, LNcurses::NColor color);

  void        aTile(size_t, size_t, int, arcade::TileType, arcade::CommandType);

  NColor      fillColor(arcade::Color color);
  void        aAssignTexture(arcade::TileType tile, const std::string &path, arcade::Color color);

  void        aPlaySound(arcade::Sound sound) {_sound.playSound(sound);}
  void        aPlayMusic(const std::string &path) {_sound.playMusic(path);}

  void        printText(size_t x, size_t y, int color, const std::string &str);
  void        aPutText(size_t, size_t, arcade::Font, size_t, arcade::Color, const std::string &);

  void        transition();
  void        drawElem(size_t x, size_t y, arcade::TileType type, arcade::CommandType);

  void                aClearAnimBuffer();
  void                aClear();
  void                aRefresh();
  std::string         aChar();
  arcade::CommandType aCommand();

private:
  std::vector<LNcurses::Data>      _data;
  WINDOW	 *_win;
  bool      _init;

  Sound    _sound;

  NColor   _emptyColor;
  NColor   _blockColor;
  NColor   _obstacleColor;
  NColor   _evilDudeColor;
  NColor   _evilShootColor;
  NColor   _myShootColor;
  NColor   _powerupColor;
  NColor   _shipColor;
  NColor   _otherColor;
};

#endif        /* !_LNcurses_HPP_ */
