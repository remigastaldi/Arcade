//
// EnemyShip.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 16:46:49 2017 sellet_f
// Last update Sun Apr  9 20:05:45 2017 sellet_f
//

#include      "EnemyShip.hpp"

EnemyShip::EnemyShip()
{
  _x = 0;
  _y = 0;
  _speed = 4;
  _it = 10;
  _direction = arcade::CommandType::UNDEFINED;
}

EnemyShip::EnemyShip(unsigned int x, unsigned int y, arcade::CommandType direction)
{
  _x = x;
  _y = y;
  _speed = 4;
  _direction = direction;
  _it = 10;
}

EnemyShip::~EnemyShip()
{
}

void		        EnemyShip::print(arcade::ICore *core)
{
  if (checkAction(true) == true)
    core->getLib()->aTile(_x + 1, _y + 1, _speed, arcade::TileType::EVIL_DUDE, _direction);
}

void		        EnemyShip::move(arcade::ICore *core, std::vector<EnemyMissile> &enemyMissile, const Level &level, bool lPDM)
{
  if (checkAction(false))
    {
      switch (_direction)
	{
	case arcade::CommandType::GO_UP :
	  if (_y == 1)
	    _direction = arcade::CommandType::GO_DOWN;
	  else
	    _y -= 1;
	  break;
	case arcade::CommandType::GO_DOWN :
	  if (_y == 39)
	    _direction = arcade::CommandType::GO_UP;
	  else
	    _y += 1;
	  break;
	case arcade::CommandType::GO_LEFT :
	  if (_x == 1)
	    _direction = arcade::CommandType::GO_RIGHT;
	  else
	    _x -= 1;
	  break;
	case arcade::CommandType::GO_RIGHT :
	  if (_x == 39)
	    _direction = arcade::CommandType::GO_LEFT;
	  else
	    _x += 1;
	  break;
	default:
	  break;
	}

      if (std::rand() % (level.getNbLvl() * 50) <= (level.getCurrentLvl() + 1) * 10 && lPDM == false)
	{
	  if (_x == 1 && (_direction == arcade::CommandType::GO_UP || _direction == arcade::CommandType::GO_DOWN))
	    enemyMissile.push_back(EnemyMissile(_x + 1, _y, arcade::CommandType::GO_RIGHT));
	  else if (_x == 39 && (_direction == arcade::CommandType::GO_UP || _direction == arcade::CommandType::GO_DOWN))
	    enemyMissile.push_back(EnemyMissile(_x - 1, _y, arcade::CommandType::GO_LEFT));
	  else if (_y == 1 && (_direction == arcade::CommandType::GO_LEFT || _direction == arcade::CommandType::GO_RIGHT))
	    enemyMissile.push_back(EnemyMissile(_x, _y + 1, arcade::CommandType::GO_DOWN));
	  else if (_y == 39 && (_direction == arcade::CommandType::GO_LEFT || _direction == arcade::CommandType::GO_RIGHT))
	    enemyMissile.push_back(EnemyMissile(_x, _y - 1, arcade::CommandType::GO_UP));
	  core->getLib()->aPlaySound(arcade::EVIL_SHOOT);
	}

    }
}
