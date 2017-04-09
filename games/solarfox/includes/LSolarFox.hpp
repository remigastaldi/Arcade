/*
** LSolarFox.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:08:10 2017 gastal_r
** Last update	Sun Apr 09 23:00:57 2017 gastal_r
*/

#ifndef         _Lsolarfox_HPP_
# define        _Lsolarfox_HPP_

# include     	<chrono>
# include     	"EnemyMissile.hpp"
# include     	"EnemyShip.hpp"
# include     	"Missile.hpp"
# include     	"ICore.hh"
# include     	"Ship.hpp"
# include       "Level.hpp"

# define        MAP_WIDTH 41
# define        MAP_HEIGHT 41
# define        SOLAR_RES "games/solarfox/res/"

class           LSolarFox : public arcade::IGame
{
  enum Status
  {
    CONTINUE,
    EXIT
  };

public:
  LSolarFox();
  virtual ~LSolarFox () {};

  void				          initTextures(void);
  arcade::CommandType		initGame(bool);

  void				parseMap(std::string const &);
  void				printGame(void);
  void				changeAction();

  void        win(void);
  void				gameWin(void);
  void				gameOver(void);

  void        move(void);

  void				lPDM_getMap() const;
  void				lPDM_whereAmI();
  void				lPDM_start();

  arcade::CommandType		mainLoop(void);
  arcade::CommandType		play(arcade::ICore &);

private:
  arcade::ICore			*_core;
  arcade::GetMap		*_map;
  Level             _level;
  Ship				      _ship;

  int				        _score;
  bool				      _lPDM;
  size_t            _nbpower;

  std::vector<Missile>	       	_missile;
  std::vector<EnemyMissile>	    _enemyMissile;
  std::vector<EnemyShip>	      _enemyShip;

  std::vector<arcade::Position>	_powerUp;

  arcade::CommandType           _exitStatus;
  arcade::CommandType           _keepCommand;
  LSolarFox::Status             _status;
};

#endif          /* !_solarfox_HPP_ */
