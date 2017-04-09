//
// Object.hh for Project-Master in /home/sellet_f/Projets/Tek2/Arcade
//
// Made by sellet_f
// Login   <flavien.sellet@epitech.eu>
//
// Started on  Tue Apr  4 16:19:14 2017 sellet_f
// Last update Fri Apr  7 15:22:57 2017 sellet_f
//


#ifndef		   _OBJECT_HH_
# define	   _OBJECT_HH_

# include	    "ICore.hh"

class			Object
{
  public:
    enum Destroyed
  {
    NOTHING,
    SHIP,
    MISSILE
  };

public:
  virtual		~Object() {}

  void			setX(unsigned int);
  void			setY(unsigned int);
  void			setIt(unsigned int);
  void			setSpeed(unsigned int);
  void			setDirection(arcade::CommandType);

  unsigned int		    getX(void) const;
  unsigned int		    getY(void) const;
  unsigned int		    getIt(void) const;
  unsigned int		    getSpeed(void) const;
  arcade::CommandType	getDirection(void) const;

  bool			checkAction(bool);

protected:
  unsigned int		_x;
  unsigned int		_y;
  unsigned int		_it;
  unsigned int		_speed;
  arcade::CommandType	_direction;
};

#endif
