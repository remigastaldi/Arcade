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

#include        <iostream>
#include        "Protocol.hpp"

namespace	       arcade
{
  enum Color
  {
    BLACK,
    WHITE,
    BLUE,
    RED,
    GREEN,
    MAGENTA,
    CYAN,
    YELLOW
  };

  class		       IGraph
  {
  public:
    virtual      ~IGraph(){};

    virtual void aInit(size_t, size_t) = 0;
    virtual void aClose() = 0;
    virtual void aTile(size_t, size_t, arcade::TileType) = 0;
    virtual void aTile(size_t x, size_t y, void *texture) = 0;
    virtual void *aGetTexture(const std::string &) = 0;
    virtual void aPutText(size_t, size_t, const std::string &,
                          size_t, arcade::Color, const std::string &) = 0;
    virtual void aClear() = 0;
    virtual void aRefresh() = 0;
    virtual arcade::CommandType aCommand() = 0;
    virtual std::string  aChar() = 0;
  };
}

#endif
