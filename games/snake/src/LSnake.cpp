/*
** lib_arcade_snake.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:43:53 2017 gastal_r
** Last update Tue Mar 21 23:55:39 2017 Leo Hubert Froideval
*/

#include          "LSnake.hpp"

LSnake::LSnake()
{}

LSnake::~LSnake()
{}

arcade::CommandType				LSnake::play(arcade::ICore &core)
{
  return (mainLoop(core, false));
}

void			LSnake::initGame()
{
  arcade::Position	head;

  // srand(time(NULL));
  if ((_map = (arcade::GetMap *)malloc(sizeof(arcade::GetMap)  * 50 * 50)) == NULL)
    throw arcade::Exception("Malloc failed\n");

  _map->type = arcade::CommandType::UNDEFINED;
  _map->width = 50;
  _map->height = 50;
  _score = 0;

  for (int i = 0 ; i < _map->width * _map->height ; ++i)
    if (((i % _map->width) == 0 || (i % _map->width) == _map->width - 1) ||
	((i / _map->width) == 0 || (i / _map->width) == _map->height - 1))
      _map->tile[i] = arcade::TileType::OBSTACLE;
    else
      _map->tile[i] = arcade::TileType::EMPTY;

  head.x = _map->width / 2;
  head.y = _map->height / 2;

  _position.push_back(head);

  newApple();
}

void			LSnake::printGame(arcade::ICore &core)
{
  core.getLib()->aClear();
  for (int i = 0 ; i < _map->width * _map->height ; ++i)
    core.getLib()->aTile((i % _map->width) + 1 , (i / _map->width) + 1, _map->tile[i]);

  core.getLib()->aTile(_position[0].x + 1, _position[0].y + 1, arcade::TileType::OTHER);
  if (_position.size() > 1)
    for (std::vector<arcade::Position>::iterator it = _position.begin() + 1; it != _position.end(); it++)
      core.getLib()->aTile((*it).x + 1, (*it).y + 1, arcade::TileType::MY_SHOOT);

  core.getLib()->aTile(_apple.x, _apple.y, arcade::TileType::POWERUP);
  core.refreshGui();
  core.getLib()->aRefresh();
}

void			LSnake::changeAction()
{
  switch (_map->type) {
  case (arcade::CommandType::GO_UP):
    if (_direction != arcade::CommandType::GO_DOWN && _direction != arcade::CommandType::GO_UP)
      _direction = arcade::CommandType::GO_UP;
    break;
  case (arcade::CommandType::GO_DOWN):
    if (_direction != arcade::CommandType::GO_UP && _direction != arcade::CommandType::GO_DOWN)
      _direction = arcade::CommandType::GO_DOWN;
    break;
  case (arcade::CommandType::GO_LEFT):
    if (_direction != arcade::CommandType::GO_RIGHT && _direction != arcade::CommandType::GO_LEFT)
      _direction = arcade::CommandType::GO_LEFT;
    break;
  case (arcade::CommandType::GO_RIGHT):
    if (_direction != arcade::CommandType::GO_LEFT && _direction != arcade::CommandType::GO_RIGHT)
      _direction = arcade::CommandType::GO_RIGHT;
    break;
  default:
    break;
  }
}

void			LSnake::addScore(int points)
{
  _score += points;
}

void			LSnake::move(arcade::ICore &core)
{
  int			nextTile;

  for (std::vector<arcade::Position>::iterator it = _position.end(); it != _position.begin(); it--)
    {
      (*it).x = (*(it - 1)).x;
      (*it).y = (*(it - 1)).y;
    }

  switch (_direction)
    {
    case (arcade::CommandType::GO_UP):
      _position[0].y--;
      break;
    case (arcade::CommandType::GO_DOWN):
      _position[0].y++;
      break;
    case (arcade::CommandType::GO_LEFT):
      _position[0].x--;
      break;
    case (arcade::CommandType::GO_RIGHT):
      _position[0].x++;
      break;
    default :
      break;
    }

  nextTile = (_position[0].y) * 50 + _position[0].x;

  if (_map->tile[nextTile] != arcade::TileType::EMPTY &&
      _map->tile[nextTile] != arcade::TileType::POWERUP &&
      _map->tile[nextTile] != arcade::TileType::MY_SHOOT)
    gameOver(core);

  for (std::vector<arcade::Position>::iterator it = _position.end(); it != _position.begin() + 1; it--)
    if (_position[0].x == (*it).x && _position[0].y == (*it).y)
      gameOver(core);

  if (_position[0].x == _apple.x - 1 && _position[0].y == _apple.y - 1)
    {
      newApple();
      addQueue();
      addScore(10);
      core.setScore(std::to_string(_score));
    }
}

arcade::CommandType			LSnake::mainLoop(arcade::ICore &core, bool lPDM)
{
  std::clock_t		cur_time = clock();
  std::clock_t		old_time = clock();

  initGame();
  if (lPDM == false)
    core.setScore(std::to_string(_score)); //TODO
  while (_map->type != arcade::CommandType::ESCAPE && _map->type != arcade::CommandType::MENU)
    {
      cur_time = clock();

      if (cur_time > old_time + (100000 - (int)_position.size()))
      {
        if (lPDM == true)
      	{
          std::string tmp;
          std::cin >> tmp;
          if (tmp[0] == 0)
            return (arcade::CommandType::ESCAPE);
          _map->type = lPDM_aCommand(tmp);
          if (_map->type == arcade::CommandType::GET_MAP)
            lPDM_getMap();
      	}
        else
      	{
          _map->type = core.getLib()->aCommand();
          if (_map->type == arcade::CommandType::NEXT_LIB)
    	        core.switchLib(arcade::CommandType::NEXT_LIB);
      	}

        changeAction();
        move(core);
        if (lPDM == false)
        {
          printGame(core);
        }
    	  old_time = clock();
    	}
    }
    return (_map->type);
}

void							LSnake::gameOver(arcade::ICore &core)
{
  core.setScore(std::to_string(_score));
  core.getLib()->aClear();
  core.getLib()->aPutText(pos_x(2.7), pos_y(2.25), "core/res/fonts/press_start.ttf", WIDTH / 40, arcade::Color::A_RED, "GAME OVER");
  core.getLib()->aPutText(pos_x(3.1), pos_y(1.8), "core/res/fonts/press_start.ttf", WIDTH / 100, arcade::Color::A_WHITE, "PRESS ENTER TO RESTART THE GAME.");
  core.getLib()->aPutText(pos_x(2.7), pos_y(2.25), "core/res/fonts/press_start.ttf", WIDTH / 40, arcade::Color::A_RED, "GAME OVER");
  core.getLib()->aRefresh();
  while (1)
    {
      _map->type = core.getLib()->aCommand();
      if (_map->type == arcade::CommandType::ESCAPE)
	{
	  exit(0);
	}
      if (_map->type == arcade::CommandType::MENU)
	{
	  exit(0);
	}
    }
}

void			LSnake::close()
{
}

void			LSnake::addQueue()
{
  _position.push_back(_position[_position.size()]);
}

void			LSnake::newApple()
{
  int			tile;

  _apple.x = (rand() % (_map->width - 2)) + 2;
  _apple.y = (rand() % (_map->height - 2)) + 2;
  tile = (_apple.y) * 50 + _apple.x;
  if (_map->tile[tile] != arcade::TileType::EMPTY)
    newApple();
  for (std::vector<arcade::Position>::iterator it = _position.end(); it != _position.begin(); it--)
    if (_apple.x == (*it).x && _apple.y == (*it).y)
      newApple();
}

arcade::CommandType		LSnake::lPDM_aCommand(std::string const &command)
{
    if (!command[0])
      return (arcade::CommandType::UNDEFINED);
    switch (command[0]) {
      case 0:
        return (arcade::CommandType::WHERE_AM_I);
        break;
      case 1:
        return (arcade::CommandType::GET_MAP);
        break;
      case 2:
        return (arcade::CommandType::GO_UP);
        break;
    }

  return (arcade::CommandType::UNDEFINED);
}

void                  LSnake::lPDM_getMap() const
{
  for (int i = 0 ; i < _map->width * _map->height ; ++i)
    {
      std::cout << (int)_map->tile[i] << std::endl;
    }
}


extern "C"
{
  LSnake		*createGame()
  {
    return (new LSnake());
  }

  void			  deleteGame(arcade::IGame *game)
  {
    if (game != NULL)
      delete(game);
  }

  void			Play()
  {
    LSnake		snake;
    arcade::ICore	*core;

    snake.mainLoop(*core, true);
    delete(core);
  }
}
