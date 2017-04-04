/*
** LSolarFox.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:08:10 2017 gastal_r
** Last update	Sun Mar 26 04:11:40 2017 gastal_r
*/

#ifndef         _LSOLAR_FOX_HPP_
#define         _LSOLAR_FOX_HPP_

#include      "ICore.hh"

class           LSolarFox : public arcade::IGame
{
public:
  LSolarFox();
  virtual ~LSolarFox ();

  arcade::CommandType	play(arcade::ICore &);
  arcade::CommandType	mainLoop(bool);
  void			initGame(void);
  void			close(void);
  void			initTextures(void);
private:
  arcade::Position	_position;
  arcade::CommandType	_direction;
  int			_score;
  bool			_lPDM;
  arcade::ICore		*_core;
  arcade::GetMap	*_map;
};

#endif          /* !_SOLAR_FOX_HPP_ */
