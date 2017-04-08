/*
** LSolarFox.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:08:10 2017 gastal_r
** Last update	Sun Apr 09 00:18:34 2017 gastal_r
*/

#ifndef         _Lsolarfox_HPP_
# define         _Lsolarfox_HPP_

# include	<chrono>
# include	"EnemyMissile.hpp"
# include	"EnemyShip.hpp"
# include	"Missile.hpp"
# include	"ICore.hh"
# include	"Ship.hpp"
# include "Level.hpp"

# define MAP_WIDTH 41
# define MAP_HEIGHT 41
# define SOLAR_RES "games/solarfox/res/"

class           LSolarFox : public arcade::IGame
{
  enum Status
  {
    CONTINUE,
    EXIT
  };

public:
  LSolarFox();
  virtual ~LSolarFox ();

  void				initTextures(void);
  arcade::CommandType		initGame(bool);

  void				parseMap(std::string const &);
  arcade::CommandType		play(arcade::ICore &);
  void				printGame(void);
  void				changeAction();
  arcade::CommandType		mainLoop(void);

  void        win(void);
  void				gameWin(void);
  void				gameOver(void);

  void				close(void);
  void        move(void);

  void				lPDM_getMap() const;
  void				lPDM_whereAmI();
  void				lPDM_start();

private:
  bool				      _lPDM;
  arcade::GetMap		*_map;
  Ship				      _ship;
  int				        _score;
  arcade::ICore			*_core;
  size_t             _nbpower;
  std::vector<Missile>	       	_missile;
  std::vector<arcade::Position>	_powerUp;
  std::vector<EnemyShip>	      _enemyShip;
  arcade::CommandType           _exitStatus;
  std::vector<EnemyMissile>	    _enemyMissile;
  arcade::CommandType           _keepCommand;
  LSolarFox::Status             _status;
};

#endif          /* !_solarfox_HPP_ */
