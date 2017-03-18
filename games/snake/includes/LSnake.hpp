/*
** LSnake.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 23:42:03 2017 gastal_r
** Last update Fri Mar 17 15:01:26 2017 Leo Hubert Froideval
*/

#ifndef         _LSnake_HPP_
#define         _LSnake_HPP_

#include	<algorithm>
#include	<iomanip>
#include	<chrono>
#include	<ctime>
#include	<thread>
#include	<vector>
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

  void		changeAction();
  void		move();
  void		printGame(arcade::ICore &core);
  void		mainLoop(arcade::ICore &, bool);
  void		initGame();
  void		play(arcade::ICore &);
  void		close();
  void		addQueue();
  void		newApple();

private:
  arcade::GetMap		*_map;
  std::vector<arcade::Position>	_position;
  arcade::Position		_apple;
  arcade::CommandType		_direction;
};

typedef struct			snake_part
{
  int				_x;
  int				_y;
}				snake_part;

#endif        /* !_LSnake_HPP_ */
