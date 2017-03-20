/*
** LSnake.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 23:42:03 2017 gastal_r
** Last update Mon Mar 20 11:00:21 2017 Leo Hubert Froideval
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
  arcade::CommandType		mainLoop(arcade::ICore &, bool);
  void		initGame();
  arcade::CommandType		play(arcade::ICore &);
  void		close();
  void		addQueue();
  void		newApple();
  void		addScore(int);
  void		gameOver();

private:
  arcade::GetMap		*_map;
  std::vector<arcade::Position>	_position;
  arcade::Position		_apple;
  arcade::CommandType		_direction;
  int				_score;
};


#endif        /* !_LSnake_HPP_ */
