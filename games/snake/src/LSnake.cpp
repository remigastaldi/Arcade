/*
** lib_arcade_snake.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:43:53 2017 gastal_r
** Last update	Tue Mar 14 14:50:17 2017 gastal_r
*/

#include          "LSnake.hpp"
#include          "ICore.hh"
#include          "IGame.hh"

LSnake::LSnake()
{}

LSnake::~LSnake()
{}

void              LSnake::play()
{
  std::cout << "PLAY" << '\n';
}

void              LSnake::close()
{
  std::cout << "CLOSE GAME" << '\n';
}

extern "C"
{
  LSnake         *createGame()
  {
    std::cout << "GAME" << '\n';
    return (new LSnake());
  }

  void            deleteGame(arcade::IGame *game)
  {
    delete(game);
  }
}
