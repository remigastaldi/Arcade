/*
** LSnake.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 23:42:03 2017 gastal_r
** Last update Wed Apr 05 13:53:17 2017 Leo Hubert Froideval
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

#define				RES_PATH "games/snake/res/"
#define				MAPWIDTH 40
#define				MAPHEIGHT 40

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
  void		newApple();
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
};


#endif        /* !_LSnake_HPP_ */
