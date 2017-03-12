//
// IGame.hh for  in /home/descho_e/year_2016_2017/cpp_arcade/lib/ncurses
// 
// Made by eric deschodt
// Login   <descho_e@epitech.net>
// 
// Started on  Wed Mar  8 13:01:42 2017 eric deschodt
// Last update Fri Mar 10 12:48:38 2017 eric deschodt
//

#ifndef		IGAME_HH__
# define	IGAME_HH__

# include	<unistd.h>
# include	"IGraph.hh"

namespace	arcade
{
    enum class  CommandCore
    {
      UNDEFINED,
      ESCAPE,
      PRV_GRAPH,
      NXT_GRAPH,
      PRV_GAME,
      NXT_GAME,
      RESTART,
      MENU
    };

  class		IGame
  {
  public:
    virtual void talk() const = 0;
    virtual arcade::CommandCore start_game(IGraph *, void *) = 0;
    virtual ~IGame(){};
  };
}

#endif
