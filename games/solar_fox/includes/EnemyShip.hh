//
// EnemyShip.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 16:14:47 2017 sellet_f
// Last update Wed Apr  5 03:14:43 2017 sellet_f
//

#ifndef		_ENEMYSHIP_HH_
# define	_ENEMYSHIP_HH_

# include	"Object.hh"

class		EnemyShip : public Object
{
public:
  EnemyShip(unsigned int, unsigned int, arcade::CommandType);
  ~EnemyShip();

  // bool	checkMove();
};

#endif
