/*
** LSnake.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 23:42:03 2017 gastal_r
** Last update	Wed Apr 05 20:24:06 2017 gastal_r
*/

#ifndef			        _LSnake_HPP_
#define			        _LSnake_HPP_

#include			<algorithm>
#include			<iomanip>
#include			<chrono>
#include			<ctime>
#include			<thread>
#include			<vector>
#include		  <iostream>
#include			<list>
#include		  "ICore.hh"

#define				SNAKE_RES "games/snake/res/"
#define				MAP_WIDTH 40
#define				MAP_HEIGHT 40
#define       SNAKE_SPEED 9

class				LSnake : public arcade::IGame
{
public:
  LSnake();
  virtual		        ~LSnake();

  void		initGame(bool);
  void    initTextures();
  void		changeAction();
  void		printGame();
  void		move();
  bool		checkSnakeColision(int);
  void		newApple();
  void		newBlock();
  void		addQueue();
  void		addScore(int);
  void		gameOver();
  void		close();
  bool		checkNextTile(int, int);
  arcade::CommandType		mainLoop();
  arcade::CommandType		play(arcade::ICore &);
  arcade::CommandType	  getDirection(arcade::Position const &, arcade::Position const &);

  void				lPDM_getMap() const;
  void				lPDM_whereAmI();
  void				lPDM_start();

private:
  arcade::GetMap		              *_map;
  std::vector<arcade::Position>   _position;
  arcade::Position		            _apple;
  arcade::CommandType	            _direction;
  int				                      _score;
  arcade::ICore     				      *_core;
  bool				                    _lPDM;
  arcade::CommandType             _exitStatus;
  int                             _speed;
};


#endif        /* !_LSnake_HPP_ */
