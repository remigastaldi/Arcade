//
// Object.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
// 
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
// 
// Started on  Tue Apr  4 16:19:14 2017 sellet_f
// Last update Tue Apr  4 17:49:09 2017 sellet_f
//


#ifndef		_OBJECT_HH_
# define	_OBJECT_HH_

# include	"ICore.hh"

class			Object
{
public:
  virtual		~Object() {}

  void			setX(unsigned int);
  void			setY(unsigned int);
  void			setIt(unsigned int);
  void			setSpeed(unsigned int);
  void			setDirection(arcade::CommandType);

  unsigned int		getX(void) const;
  unsigned int		getY(void) const;
  unsigned int		getIt(void) const;
  unsigned int		getSpeed(void) const;
  arcade::CommandType	getDirection(void) const;
protected:
  unsigned int		_x;
  unsigned int		_y;
  unsigned int		_it;
  unsigned int		_speed;
  arcade::CommandType	_direction;
};

#endif
