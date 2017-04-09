//
// Missile.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 16:21:08 2017 sellet_f
// Last update Sun Apr  9 12:41:00 2017 sellet_f
//

#ifndef _MISSILE_HH_
# define _MISSILE_HH_

# include "Object.hpp"

class	Missile : public Object
{
public:
  Missile();
  Missile(unsigned int, unsigned int, arcade::CommandType);
  ~Missile();

  void	print(arcade::ICore *);
  void	empty(void);
  void	move(arcade::GetMap *);

private:
  int   _moves;
};

#endif
