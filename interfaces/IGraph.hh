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

#include        "Protocol.hpp"
#include        <iostream>

namespace	       arcade
{
  class		       IGraph
  {
  public:
    virtual      ~IGraph(){};

    virtual void aInit(size_t, size_t) = 0;
    virtual void aClose() = 0;
    virtual void aTile(size_t, size_t, arcade::TileType) = 0;
    virtual void aRefresh() = 0;
  };
}

#endif
