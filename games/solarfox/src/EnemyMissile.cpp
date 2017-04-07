//
// EnemyMissile.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 17:31:02 2017 sellet_f
// Last update Fri Apr  7 04:05:19 2017 sellet_f
//

#include "EnemyMissile.hh"

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
  _speed = 4;
  _direction = direction;
  _it = 4;
}

void	EnemyMissile::print(arcade::ICore *core)
{
  if (checkAction(true) == true)
    core->getLib()->aTile(_x + 1, _y + 1, _speed, arcade::TileType::EVIL_SHOOT, _direction);
}

int		EnemyMissile::getMoves(void) const
{
  return (_moves);
}

bool	EnemyMissile::move(Missile missile, Ship ship)
{
  if (checkAction(false))
  {
    if (_moves > 0)
      _moves--;
    switch (_direction)
        {
        case arcade::CommandType::GO_UP :
    if (((missile.getX() == _x && missile.getY() == _y) || (ship.getX() == _x && ship.getY() == _y)) &&
        ((missile.getX() == _x && missile.getY() == _y - 1) || (ship.getX() == _x && ship.getY() == _y - 1)))
      return (false);
    _y -= 1;
    break;
        case arcade::CommandType::GO_DOWN :
    if (((missile.getX() == _x && missile.getY() == _y) || (ship.getX() == _x && ship.getY() == _y)) &&
        ((missile.getX() == _x && missile.getY() == _y + 1) || (ship.getX() == _x && ship.getY() == _y + 1)))
      return (false);
    _y += 1;
    break;
        case arcade::CommandType::GO_LEFT :
    if (((missile.getX() == _x && missile.getY() == _y) || (ship.getX() == _x && ship.getY() == _y)) &&
        ((missile.getX() == _x && missile.getY() + 1 == _y) || (ship.getX() == _x && ship.getY() + 1== _y)))
      return (false);
    _x -= 1;
    break;
        case arcade::CommandType::GO_RIGHT :
    if (((missile.getX() == _x && missile.getY() == _y) || (ship.getX() == _x && ship.getY() == _y)) &&
        ((missile.getX() == _x && missile.getY() - 1 == _y) || (ship.getX() == _x && ship.getY() - 1== _y)))
      return (false);
    _x += 1;
    break;
        default:
    return (false);
    break;
        }
  }
  return (true);
}
