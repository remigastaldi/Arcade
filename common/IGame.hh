//
// IGame.hh for  in /home/descho_e/year_2016_2017/cpp_arcade/lib/ncurses
//
// Made by eric deschodt
// Login   <descho_e@epitech.net>
//
// Started on  Wed Mar  8 13:01:42 2017 eric deschodt
// Last update Fri Mar 10 12:48:38 2017 eric deschodt
//

#ifndef           IGAME_HH__
# define	        IGAME_HH__

# include	        <unistd.h>
# include	        "Protocol.hpp"

namespace	        arcade
{
  class           ICore;
  class           IGame
  {
  public:
    virtual       ~IGame(){};

    virtual arcade::CommandType  play(arcade::ICore &) = 0;
  };
}

#endif
