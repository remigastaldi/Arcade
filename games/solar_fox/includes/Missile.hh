//
// Missile.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 16:21:08 2017 sellet_f
// Last update Tue Apr  4 19:00:38 2017 sellet_f
//

#ifndef _MISSILE_HH_
# define _MISSILE_HH_

# include "Object.hh"

class	Missile : Object
{
public:
  Missile(unsigned int, unsigned int, arcade::CommandType);
  ~Missile();

};

#endif
