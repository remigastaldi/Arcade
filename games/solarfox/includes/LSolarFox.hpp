/*
** LSolarFox.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:08:10 2017 gastal_r
** Last update	Thu Apr 06 14:15:23 2017 gastal_r
*/

#ifndef         _Lsolarfox_HPP_
# define         _Lsolarfox_HPP_

# include	"EnemyMissile.hh"
# include	"EnemyShip.hh"
# include	"Missile.hh"
# include	"ICore.hh"
# include	"Ship.hh"
# include	<chrono>

# define MAP_WIDTH 41
# define MAP_HEIGHT 41
# define SOLAR_SPEED 8
# define SOLAR_RES "games/solarfox/res/"

class           LSolarFox : public arcade::IGame
{
public:
  LSolarFox();
  virtual ~LSolarFox ();

  arcade::CommandType		play(arcade::ICore &);
  void				initTextures(void);
  void				printGame(void);
  void				changeAction();
  arcade::CommandType		mainLoop(void);
  void				initGame(bool);
  void				close(void);
  void			        move();

  void				lPDM_getMap() const;
  void				lPDM_whereAmI();
  void				lPDM_start();

private:
  bool				_lPDM;
  arcade::GetMap		*_map;
  Ship				_ship;
  int				_score;
  arcade::ICore			*_core;
  Missile			_missile;
  std::vector<EnemyShip>	_enemyShip;
  std::vector<EnemyMissile>	_enemyMissile;
};

#endif          /* !_solarfox_HPP_ */
