//
// EnemyMissile.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 16:22:15 2017 sellet_f
// Last update Tue Apr  4 19:06:21 2017 sellet_f
//

#ifndef _ENEMYMISSILE_HH_
# define _ENEMYMISSILE_HH_

# include "Object.hh"

class	EnemyMissile : Object
{
public:
  EnemyMissile(unsigned int, unsigned int, arcade::CommandType);
  ~EnemyMissile();
};

#endif
