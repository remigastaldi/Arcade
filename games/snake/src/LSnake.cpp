/*
** lib_arcade_snake.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:43:53 2017 gastal_r
** Last update	Mon Mar 13 17:44:21 2017 gastal_r
*/

#include          "LSnake.hpp"
#include          "ICore.hh"
#include          "IGame.hh"

LSnake::LSnake(arcade::ICore *core)
{
  _core = core;
}

LSnake::~LSnake()
{}

void              LSnake::play()
{
  std::cout << "BITE" << '\n';
}

extern "C"
{
  LSnake         *createGame(arcade::ICore *core)
  {
    std::cout << "GAME" << '\n';
    return (new LSnake(core));
  }

  void            deleteGame(arcade::IGame *game)
  {
    delete(game);
  }
}
