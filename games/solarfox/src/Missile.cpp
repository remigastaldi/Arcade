//
// Missile.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 17:20:27 2017 sellet_f
// Last update Sun Apr  9 13:32:34 2017 sellet_f
//

#include      "Missile.hpp"

Missile::Missile()
{
  _x = 0;
  _y = 0;
  _speed = 0;
  _it = 0;
  _direction = arcade::CommandType::UNDEFINED;
  _moves = 6;
}

Missile::Missile(unsigned int x, unsigned int y, arcade::CommandType direction)
{
  _x = x;
  _y = y;
  _moves = 6;
  _speed = 10;
  _direction = direction;
  _it = 10;
}

Missile::~Missile()
{
}

void	         Missile::print(arcade::ICore *core)
{
  if (checkAction(true) == true)
    core->getLib()->aTile(_x + 1, _y + 1, _speed, arcade::TileType::MY_SHOOT, _direction);
}

void	         Missile::move(arcade::GetMap *map)
{
  if (checkAction(false))
    {
      switch (_direction)
	{
	case arcade::CommandType::GO_UP :
	  _y -= 1;
	  break;
	case arcade::CommandType::GO_DOWN :
	  _y += 1;
	  break;
	case arcade::CommandType::GO_LEFT :
	  _x -= 1;
	  break;
	case arcade::CommandType::GO_RIGHT :
	  _x += 1;
	default:
	  break;
	}
      if (_moves > 0 && map->tile[_y * 41 + _x] != arcade::TileType::OBSTACLE)
	_moves -= 1;
      else
	empty();
    }
}

void	         Missile::empty(void)
{
  _x = 0;
  _y = 0;
  _direction = arcade::CommandType::UNDEFINED;
  _moves = 6;
}
