//
// Ship.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 16:29:13 2017 sellet_f
// Last update Sat Apr  8 20:04:34 2017 sellet_f
//

#include "Ship.hpp"

Ship::Ship()
{
  _x = 25;
  _y = 26;
  _speed = 9;
  _direction = arcade::CommandType::GO_UP;
  _it = 10;
}

Ship::Ship(unsigned int x, unsigned int y)
{
  _x = x;
  _y = y;
  _speed = 9;
  _direction = arcade::CommandType::GO_UP;
  _it = 10;
}

Ship::~Ship()
{
}

void	Ship::print(arcade::ICore *core)
{
  if (checkAction(true) == true)
    core->getLib()->aTile(_x + 1, _y + 1, _speed, arcade::TileType::SHIP, _direction);
}

int	Ship::move(arcade::GetMap *map)
{
  if (checkAction(false))
    {
      switch(_direction)
	{
	case arcade::CommandType::GO_UP :
	  if (map->tile[(_y - 1) * 41 + _x] == arcade::TileType::OBSTACLE)
	    return (Destroyed::SHIP);
	  if (map->tile[(_y - 1) * 41 + _x] != arcade::TileType::BLOCK)
	    _y -= 1;
	  break;
	case arcade::CommandType::GO_DOWN :
	  if (map->tile[(_y + 1) * 41 + _x] == arcade::TileType::OBSTACLE)
	    return (Destroyed::SHIP);
	  if (map->tile[(_y + 1) * 41 + _x] != arcade::TileType::BLOCK)
	    _y += 1;
	  break;
	case arcade::CommandType::GO_LEFT :
	  if (map->tile[_y * 41 + _x - 1] == arcade::TileType::OBSTACLE)
	    return (Destroyed::SHIP);
	  if (map->tile[_y * 41 + _x - 1] != arcade::TileType::BLOCK)
	    _x -= 1;
	  break;
	case arcade::CommandType::GO_RIGHT :
	  if (map->tile[_y * 41 + _x + 1] == arcade::TileType::OBSTACLE)
	    return (Destroyed::SHIP);
	  if (map->tile[_y * 41 + _x + 1] != arcade::TileType::BLOCK)
	    _x += 1;
	  break;
	default :
	  break;
	}
    }
  return (0);
}

void	Ship::shoot(Missile &missile)
{
  switch (_direction)
    {
    case arcade::CommandType::GO_UP :
      missile = Missile(_x, _y - 1, _direction);
      break;
    case arcade::CommandType::GO_DOWN :
      missile = Missile(_x, _y + 1, _direction);
      break;
    case arcade::CommandType::GO_LEFT :
      missile = Missile(_x - 1, _y, _direction);
      break;
    case arcade::CommandType::GO_RIGHT :
      missile = Missile(_x + 1, _y, _direction);
      break;
    default:
      break;
    }
}
