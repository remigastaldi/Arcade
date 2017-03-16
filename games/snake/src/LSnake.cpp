
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

void	LSnake::initMap(arcade::GetMap &map)
{
  map.type = arcade::CommandType::UNDEFINED;
  map.width = 50;
  map.height = 50;
  for (int i = -1 ; i < map.width * map.height ; ++i)
    map.tile[i] = arcade::TileType::EMPTY;
}

void			LSnake::mainLoop(arcade::ICore &core, bool lPDM)
{
  arcade::GetMap	*map;

  if ((map = (arcade::GetMap *)malloc(sizeof(arcade::GetMap)  * 50 * 50)) == NULL)
    throw arcade::Exception("Malloc failed\n");
  initMap(*map);
  while (map->type != arcade::CommandType::ESCAPE && map->type != arcade::CommandType::MENU)
    {
      if (lPDM == true)
	{
	  
	}
      else
	{
	  
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
