//
// Ship.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 14:20:32 2017 sellet_f
// Last update Fri Apr  7 01:46:51 2017 sellet_f
//

#ifndef		_SHIP_HH_
# define	_SHIP_HH_

# include	"Object.hh"

class		Ship : public Object
{
public:
  Ship();
  ~Ship();

  void	print(arcade::ICore *);
  void	move(arcade::GetMap *);
};

#endif
