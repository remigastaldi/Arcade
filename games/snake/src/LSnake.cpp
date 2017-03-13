/*
** lib_arcade_snake.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:43:53 2017 gastal_r
** Last update	Mon Mar 13 00:41:46 2017 gastal_r
*/

#include          "LSnake.hpp"
#include          "ICore.hh"

LSnake::LSnake()
{}

LSnake::~LSnake()
{}

extern "C" void   play(ICore &core)
{
  std::cout << "PLAY" << '\n';

  core.initGraphicalLib();
  core.nextGame();
}
