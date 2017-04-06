//
// EnemyMissile.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 16:22:15 2017 sellet_f
// Last update Wed Apr  5 03:14:24 2017 sellet_f
//

#ifndef _ENEMYMISSILE_HH_
# define _ENEMYMISSILE_HH_

# include "Object.hh"

class	EnemyMissile : public Object
{
public:
  EnemyMissile(unsigned int, unsigned int, arcade::CommandType);
  ~EnemyMissile();
};

#endif
