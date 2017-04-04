//
// EnemyShip.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 16:46:49 2017 sellet_f
// Last update Tue Apr  4 18:55:34 2017 sellet_f
//

#include "EnemyShip.hh"

EnemyShip::EnemyShip(unsigned int x, unsigned int y, arcade::CommandType direction)
{
  _x = x;
  _y = y;
  _speed = 4;
  _direction = direction;
  _it = 6;
}

EnemyShip::~EnemyShip()
{
}
