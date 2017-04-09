//
// IGraph.hh for  in /home/descho_e/year_2016_2017/cpp_arcade/lib
//
// Made by eric deschodt
// Login   <descho_e@epitech.net>
//
// Started on  Wed Mar  8 16:57:20 2017 eric deschodt
// Last update Fri Mar 10 12:47:17 2017 eric deschodt
//


#ifndef		       IGRAPH_HH__
# define	       IGRAPH_HH__

#include         "ICore.hh"

#define BLOCK_X      8
#define BLOCK_Y      16
#define WIDTH        1920
#define HEIGHT       1080
#define pos_x(x)     (WIDTH / BLOCK_X) / x
#define pos_y(y)     (HEIGHT / BLOCK_Y) / y
#define X_PAD        pos_x(3.5)
#define Y_PAD        pos_y(6)

namespace	       arcade
{
  class ICore;
  enum Font
  {
    FREAKY,
    PRESS_START
  };

  enum    Sound
  {
    NEW_GAME,
    GAME_OVER,
    MY_SHOOT,
    EVIL_SHOOT,
    POWERUP,
    EXPLOSION,
    OTHER
  };

  enum Color
  {
    A_BLACK,
    A_RED,
    A_GREEN,
    A_YELLOW,
    A_BLUE,
    A_MAGENTA,
    A_CYAN,
    A_WHITE
  };

  class		       IGraph
  {
  public:
    virtual      ~IGraph(){};

    virtual void aInit(arcade::ICore *, size_t, size_t) = 0;
    virtual void aClose() = 0;

    virtual void aTile(size_t, size_t, int, arcade::TileType, arcade::CommandType) = 0;

    virtual void aAssignTexture(arcade::TileType tile, const std::string &path, arcade::Color color) = 0;

    virtual void aPlaySound(arcade::Sound) = 0;
    virtual void aPlayMusic(const std::string &) = 0;

    virtual void aPutText(size_t, size_t, arcade::Font, size_t, arcade::Color, const std::string &) = 0;

    virtual void aClear() = 0;
    virtual void aClearAnimBuffer() = 0;
    virtual void aRefresh() = 0;

    virtual arcade::CommandType aCommand() = 0;
    virtual std::string         aChar() = 0;
  };
}

#endif
