//
// Object.cpp for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 17:48:07 2017 sellet_f
// Last update Wed Apr  5 17:45:21 2017 sellet_f
//

#include "Object.hh"

void			Object::setX(unsigned int x)
{
  _x = x;
}

void			Object::setY(unsigned int y)
{
  _y = y;
}

void			Object::setIt(unsigned int it)
{
  _it = it;
}

void			Object::setSpeed(unsigned int speed)
{
  _speed = speed;
}

void			Object::setDirection(arcade::CommandType direction)
{
  _direction = direction;
}

unsigned int		Object::getX(void) const
{
  return (_x);
}

unsigned int		Object::getY(void) const
{
  return (_y);
}

unsigned int		Object::getIt(void) const
{
  return (_it);
}

unsigned int		Object::getSpeed(void) const
{
  return (_speed);
}

arcade::CommandType	Object::getDirection(void) const
{
  return (_direction);
}

bool			Object::checkPrint(Object obj)
{
  if (obj._it == 10)
    {
      obj._it = obj._speed;
      return (true);
    }
  else
    obj._it += 1;
  return (false);
}
