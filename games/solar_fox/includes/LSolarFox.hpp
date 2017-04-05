/*
** LSolarFox.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:08:10 2017 gastal_r
** Last update	Sun Mar 26 04:11:40 2017 gastal_r
*/

#ifndef         _LSOLAR_FOX_HPP_
# define         _LSOLAR_FOX_HPP_

# include	"EnemyMissile.hh"
# include	"EnemyShip.hh"
# include	"Missile.hh"
# include	"ICore.hh"
# include	"Ship.hh"
# include	<chrono>

class           LSolarFox : public arcade::IGame
{
public:
  LSolarFox();
  virtual ~LSolarFox ();

  arcade::CommandType		play(arcade::ICore &);
  arcade::CommandType		mainLoop(bool);
  void				initGame(void);
  void				close(void);
  void				initTextures(void);
  arcade::CommandType		getDirection(Object const &, Object const &);
  void				printGame(void);

private:
  arcade::Position		_position;
  arcade::CommandType		_direction;
  int				_score;
  arcade::ICore			*_core;
  bool				_lPDM;
  arcade::GetMap		*_map;
  Ship				_ship;
  std::vector<EnemyShip>	_enemyShip;
  std::vector<Missile>		_missile;
  std::vector<EnemyMissile>	_enemyMissile;
};

#endif          /* !_SOLAR_FOX_HPP_ */
