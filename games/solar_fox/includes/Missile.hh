//
// Missile.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 16:21:08 2017 sellet_f
// Last update Wed Apr  5 03:14:54 2017 sellet_f
//

#ifndef _MISSILE_HH_
# define _MISSILE_HH_

# include "Object.hh"

class	Missile : public Object
{
public:
  Missile(unsigned int, unsigned int, arcade::CommandType);
  ~Missile();

};

#endif
