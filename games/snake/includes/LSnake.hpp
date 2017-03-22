/*
** LSnake.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 23:42:03 2017 gastal_r
** Last update	Wed Mar 22 21:10:21 2017 gastal_r
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
  void		move(arcade::ICore &);
  void		printGame(arcade::ICore &core);
  arcade::CommandType		mainLoop(arcade::ICore &, bool);
  void    initTextures(arcade::ICore &core);
  void		initGame();
  arcade::CommandType		play(arcade::ICore &);
  void		close();
  void		addQueue();
  void		newApple();
  void		addScore(int);
  void		gameOver(arcade::ICore &);

  /*
  **  Fonctions pour la putain de moulinette
  */
  arcade::CommandType		lPDM_aCommand(std::string const &);
  void                  lPDM_getMap() const;

private:
  arcade::GetMap		*_map;
  std::vector<arcade::Position>	_position;
  arcade::Position		_apple;
  arcade::CommandType	_direction;
  int				          _score;
};


#endif        /* !_LSnake_HPP_ */
