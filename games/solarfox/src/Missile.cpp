//
// Missile.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 17:20:27 2017 sellet_f
// Last update Thu Apr  6 23:04:53 2017 sellet_f
//

#include "Missile.hh"

Missile::Missile()
{
  _x = 0;
  _y = 0;
  _speed = 0;
  _it = 0;
  _direction = arcade::CommandType::UNDEFINED;
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

void	Missile::print(arcade::ICore *core)
{
  if (checkAction(true) == true)
    core->getLib()->aTile(_x + 1, _y + 1, _speed, arcade::TileType::MY_SHOOT, _direction);
}
