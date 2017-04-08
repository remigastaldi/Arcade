//
// Missile.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 16:21:08 2017 sellet_f
// Last update Sat Apr  8 00:11:58 2017 sellet_f
//

#ifndef _MISSILE_HH_
# define _MISSILE_HH_

# include "Object.hh"

class	Missile : public Object
{
public:
  Missile();
  Missile(unsigned int, unsigned int, arcade::CommandType);
  ~Missile();

  void	print(arcade::ICore *);
  void	empty(void);
  void	move(void);
};

#endif
