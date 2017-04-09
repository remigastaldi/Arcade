//
// EnemyMissile.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 17:31:02 2017 sellet_f
// Last update Fri Apr  7 16:40:37 2017 sellet_f
//

#include      "EnemyMissile.hpp"

EnemyMissile::~EnemyMissile()
{
  _x = 0;
  _y = 0;
  _speed = 0;
  _moves = 0;
  _it = 0;
  _direction = arcade::CommandType::UNDEFINED;
}

EnemyMissile::EnemyMissile(unsigned int x, unsigned int y, arcade::CommandType direction)
{
  _x = x;
  _y = y;
  _moves = 38;
  _speed = 7;
  _direction = direction;
  _it = 7;
}

void	         EnemyMissile::print(arcade::ICore *core)
{
  if (checkAction(true) == true)
    core->getLib()->aTile(_x + 1, _y + 1, _speed, arcade::TileType::EVIL_SHOOT, _direction);
}

bool	         EnemyMissile::checkColisions(const Object &obj)
{
  if (obj.getX() == _x && obj.getY() == _y)
    return (true);
  return (false);
}

int           EnemyMissile::move(const Ship &ship)
{
  if (checkAction(false))
    {
      switch (_direction)
    	{
    	case arcade::CommandType::GO_UP :
    	  if (_y == 1)
    	    return (Destroyed::MISSILE);
    	  _y -= 1;
    	  break;
    	case arcade::CommandType::GO_DOWN :
    	  if (_y == 39)
    	    return (Destroyed::MISSILE);
    	  _y += 1;
    	  break;
    	case arcade::CommandType::GO_LEFT :
    	  if (_x == 1)
    	    return (Destroyed::MISSILE);
    	  _x -= 1;
    	  break;
    	case arcade::CommandType::GO_RIGHT :
    	  if (_x == 39)
    	    return (Destroyed::MISSILE);
    	  _x += 1;
    	default:
    	  break;
    	}
    }
    if (checkColisions(ship) == true)
     return (SHIP);
  return (0);
}
