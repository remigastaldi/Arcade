//
// Missile.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 17:20:27 2017 sellet_f
// Last update Tue Apr  4 19:01:54 2017 sellet_f
//

#include "Missile.hh"

Missile::Missile(unsigned int x, unsigned int y, arcade::CommandType direction)
{
  _x = x;
  _y = y;
  _speed = 10;
  _direction = direction;
  _it = 10;
}

Missile::~Missile()
{

}
