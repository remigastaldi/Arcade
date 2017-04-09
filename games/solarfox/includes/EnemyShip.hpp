//
// EnemyShip.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 16:14:47 2017 sellet_f
// Last update Fri Apr  7 02:43:37 2017 sellet_f
//

#ifndef		   _ENEMYSHIP_HH_
# define	   _ENEMYSHIP_HH_

# include    "ICore.hh"
# include	   "Object.hpp"
# include	   "EnemyMissile.hpp"
# include    "Level.hpp"

class		     EnemyShip : public Object
{
public:
  EnemyShip();
  EnemyShip(unsigned int, unsigned int, arcade::CommandType);
  ~EnemyShip();

  void	     print(arcade::ICore *);
  void	     move(arcade::ICore *, std::vector<EnemyMissile> &, const Level &, bool);
};

#endif
