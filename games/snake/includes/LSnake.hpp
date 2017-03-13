/*
** LSnake.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 23:42:03 2017 gastal_r
** Last update	Mon Mar 13 16:03:24 2017 gastal_r
*/

#ifndef         _LSnake_HPP_
#define         _LSnake_HPP_

#include        <iostream>
#include        "ICore.hh"
#include        "IGame.hh"
#include        "IGraph.hh"

class           LSnake : public arcade::IGame
{
public:
  LSnake(arcade::ICore *);
  virtual       ~LSnake();

  void          play();

private:
  arcade::ICore *_core;
};

#endif        /* !_LSnake_HPP_ */
