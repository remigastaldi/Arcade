//
// Ship.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 16:29:13 2017 sellet_f
// Last update Tue Apr  4 18:59:47 2017 sellet_f
//

#include "Ship.hh"

Ship::Ship()
{
  _x = 25;
  _y = 26;
  _speed = 3;
  _direction = arcade::CommandType::GO_UP;
  _it = 7;
}

Ship::~Ship()
{

}
