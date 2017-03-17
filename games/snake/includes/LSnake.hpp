/*
** LSnake.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 23:42:03 2017 gastal_r
** Last update Fri Mar 17 03:07:45 2017 Leo Hubert Froideval
*/

#ifndef         _LSnake_HPP_
#define         _LSnake_HPP_

#include	<algorithm>
#include <vector>
#include        <iostream>
#include	<list>
#include        "ICore.hh"
#include        "IGame.hh"
#include        "IGraph.hh"
#include	"Protocol.hpp"
#include	"Exception.hpp"

class           LSnake : public arcade::IGame
{
public:
  typedef struct s_snake
  {
    int	x;
    int	y;
  }	t_snake;

  LSnake();
  virtual       ~LSnake();

  void		moveAction(arcade::ICore &core);
  void		printGame(arcade::ICore &core);
  void		mainLoop(arcade::ICore &, bool);
  void		initGame();
  void          play(arcade::ICore &);
  void          close();

private:
  arcade::GetMap  *_map;
  std::vector<arcade::Position>	_position;
};

typedef struct	snake_part
{
  int		_x;
  int		_y;
}		snake_part;

#endif        /* !_LSnake_HPP_ */
