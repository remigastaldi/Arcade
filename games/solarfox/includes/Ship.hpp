//
// Ship.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 14:20:32 2017 sellet_f
// Last update Sat Apr  8 03:24:58 2017 sellet_f
//

#ifndef		    _SHIP_HH_
# define	    _SHIP_HH_

# include   	"Object.hpp"
# include   	"Missile.hpp"

class		      Ship : public Object
{
public:
  Ship();
  Ship(unsigned int, unsigned int);
  ~Ship();

  void		    print(arcade::ICore *);
  int		      move(arcade::GetMap *);
  void		    shoot(Missile &);
};

#endif
