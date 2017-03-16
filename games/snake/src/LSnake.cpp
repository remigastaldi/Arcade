
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

LSnake::LSnake()
{}

LSnake::~LSnake()
{}

void				LSnake::play(arcade::ICore &core)
{
  snake_part			initPos;
  std::list<snake_part>		snake;

  initPos._x = 30;
  initPos._y = 30;
  snake.push_back(initPos);

  mainLoop(core, false);
}

void	LSnake::initMap()
{
  if ((_map = (arcade::GetMap *)malloc(sizeof(arcade::GetMap)  * 50 * 50)) == NULL)
    throw arcade::Exception("Malloc failed\n");
  _map->type = arcade::CommandType::UNDEFINED;
  _map->width = 50;
  _map->height = 50;
  for (int i = 0 ; i < _map->width * _map->height ; ++i)
  {
    if ((i % _map->width) == 0 || (i % _map->width) == _map->width - 1)
      _map->tile[i] = arcade::TileType::BLOCK;
    else if ((i / _map->width) == 0 || (i / _map->width) == _map->height - 1)
      _map->tile[i] = arcade::TileType::BLOCK;
    else
      _map->tile[i] = arcade::TileType::EMPTY;

  }

  // for (int i = 0 ; i < _map->width * _map->height ; ++i)
  //   std::cout << (int)_map->tile[i] << std::endl;
}

void			LSnake::printMap(arcade::ICore &core)
{
  for (int i = 0 ; i < _map->width * _map->height ; ++i)
  {
    core.getLib()->aTile((i % _map->width) * 10 , (i / _map->width) * 10 , _map->tile[i]);
  }
  core.getLib()->aRefresh();
}

void			LSnake::mainLoop(arcade::ICore &core, bool lPDM)
{
  initMap();
  while (_map->type != arcade::CommandType::ESCAPE && _map->type != arcade::CommandType::MENU)
    {
      if (lPDM == true)
	{

	}
      else
	{
    _map->type = core.getLib()->aCommand();
    printMap(core);
	}
    }
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

  void			Play()
  {
    LSnake		snake;
    arcade::ICore	*core;

    snake.mainLoop(*core, true);
  }
}
