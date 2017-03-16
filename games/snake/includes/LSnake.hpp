/*
** LSnake.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 23:42:03 2017 gastal_r
** Last update	Tue Mar 14 14:50:16 2017 gastal_r
*/

#ifndef         _LSnake_HPP_
#define         _LSnake_HPP_

#include	<algorithm>
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
  LSnake();
  virtual       ~LSnake();

  void		mainLoop(arcade::ICore &, bool);
  void		initMap(arcade::GetMap &);
  void          play(arcade::ICore &);
  void          close();

private:
};

typedef struct	snake_part
{
  int		_x;
  int		_y;
}		snake_part;

#endif        /* !_LSnake_HPP_ */
