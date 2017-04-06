/*
** LSolarFox.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:08:10 2017 gastal_r
// Last update Thu Apr  6 13:42:28 2017 sellet_f
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

class           LSolarFox : public arcade::IGame
{
public:
  LSolarFox();
  virtual ~LSolarFox ();

  arcade::CommandType		play(arcade::ICore &);
  arcade::CommandType		mainLoop(void);
  void				initGame(bool);
  void				close(void);
  void				initTextures(void);
  void				changeAction();
  void        move();
  void				printGame(void);

  void				lPDM_getMap() const;
  void				lPDM_whereAmI();
  void				lPDM_start();

private:
  int				_score;
  arcade::ICore			*_core;
  bool				_lPDM;
  arcade::GetMap		*_map;
  Ship				_ship;
  std::vector<EnemyShip>	_enemyShip;
  std::vector<Missile>		_missile;
  std::vector<EnemyMissile>	_enemyMissile;
};

#endif          /* !_solarfox_HPP_ */
