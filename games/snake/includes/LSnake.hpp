/*
** LSnake.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 23:42:03 2017 gastal_r
** Last update	Sun Apr 02 01:29:42 2017 gastal_r
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

class				LSnake : public arcade::IGame
{
public:
  LSnake();
  virtual		        ~LSnake();

  void		initGame();
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
  arcade::CommandType		mainLoop(bool);
  arcade::CommandType		play(arcade::ICore &);
  arcade::CommandType	  getDirection(arcade::Position const &, arcade::Position const &);

  void				lPDM_getMap() const;
  void				lPDM_whereAmI();
  void				lPDM_move(arcade::CommandType);
  void				lPDM_play();
  void				lPDM_escape();
  void				lPDM_menu();
  arcade::CommandType		lPDM_aCommand(std::string const &);

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
