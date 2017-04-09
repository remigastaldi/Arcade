//
// EnemyMissile.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 16:22:15 2017 sellet_f
// Last update Fri Apr  7 15:35:39 2017 sellet_f
//

#ifndef     _ENEMYMISSILE_HH_
# define    _ENEMYMISSILE_HH_

# include   "Object.hpp"
# include   "Missile.hpp"
# include   "Ship.hpp"

class	      EnemyMissile : public Object
{
public:
  EnemyMissile(unsigned int, unsigned int, arcade::CommandType);
  ~EnemyMissile();

  void	   print(arcade::ICore *);
  int	     move(const Ship &);
  bool	   checkColisions(const Object &);

private:
  unsigned int	_moves;
};

#endif
