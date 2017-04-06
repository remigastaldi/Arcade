//
// EnemyMissile.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 17:31:02 2017 sellet_f
// Last update Tue Apr  4 19:04:38 2017 sellet_f
//

#include "EnemyMissile.hh"

EnemyMissile::EnemyMissile(unsigned int x, unsigned int y, arcade::CommandType direction)
{
  _x = x;
  _y = y;
  _speed = 4;
  _direction = direction;
  _it = 4;
}

EnemyMissile::~EnemyMissile()
{

}
