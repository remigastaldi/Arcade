/*
** LSnake.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 23:42:03 2017 gastal_r
** Last update	Sun Apr 09 17:31:50 2017 gastal_r
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

class				  LSnake : public arcade::IGame
{
public:
  LSnake();
  virtual     ~LSnake();

  void		    initGame(bool);
  void        initTextures();

  void		    changeAction();
  void		    printGame();
  void		    move();
  bool		    checkSnakeColision(int) const;

  void		    newApple();
  void		    newBlock();

  void		    addQueue();
  void		    addScore(int);

  void		    gameOver();
  bool		    checkNextTile(int, int);


  void				lPDM_getMap() const;
  void				lPDM_whereAmI();
  void				lPDM_start();

  arcade::CommandType		mainLoop();
  arcade::CommandType		play(arcade::ICore &);
  arcade::CommandType	  getDirection(arcade::Position const &, arcade::Position const &);

private:
  arcade::ICore     				      *_core;
  arcade::GetMap		              *_map;
  arcade::Position		            _apple;

  int				                      _score;
  int                             _speed;
  bool				                    _lPDM;

  arcade::CommandType	            _direction;
  arcade::CommandType             _exitStatus;

  std::vector<arcade::Position>   _position;
};


#endif        /* !_LSnake_HPP_ */
