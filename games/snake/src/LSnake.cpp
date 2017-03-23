/*
** lib_arcade_snake.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:43:53 2017 gastal_r
** Last update Fri Mar 24 00:51:05 2017 Leo Hubert Froideval
*/

#include          "LSnake.hpp"

LSnake::LSnake()
{}

LSnake::~LSnake()
{}

arcade::CommandType				LSnake::play(arcade::ICore &core)
{
  _core = &core;
  return (mainLoop(false));
}

void      LSnake::initTextures()
{
  _core->getLib()->aAssignTexture(arcade::TileType::EMPTY, RES_PATH "img/floor2.png", arcade::Color::A_WHITE);
  _core->getLib()->aAssignTexture(arcade::TileType::OBSTACLE, RES_PATH "img/wall.png", arcade::Color::A_RED);
  _core->getLib()->aAssignTexture(arcade::TileType::OTHER, RES_PATH "img/tron.png", arcade::Color::A_BLACK);
  _core->getLib()->aAssignTexture(arcade::TileType::MY_SHOOT, RES_PATH "img/wall3.png", arcade::Color::A_MAGENTA);
  _core->getLib()->aAssignTexture(arcade::TileType::POWERUP, RES_PATH "img/mooncat.jpg", arcade::Color::A_MAGENTA);
}

void			LSnake::initGame()
{
  arcade::Position	head;

  srand(time(NULL));
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

void			LSnake::printGame()
{
  _core->getLib()->aClear();
  _core->getLib()->aTile(_position[0].x + 1, _position[0].y + 1, arcade::TileType::OTHER);
  for (int i = 0 ; i < _map->width * _map->height ; ++i)
    _core->getLib()->aTile((i % _map->width) + 1 , (i / _map->width) + 1, _map->tile[i]);
  _core->getLib()->aTile(_position[0].x + 1, _position[0].y + 1, arcade::TileType::OTHER);
  if (_position.size() > 1)
    for (std::vector<arcade::Position>::iterator it = _position.begin() + 1; it != _position.end(); it++)
      _core->getLib()->aTile((*it).x + 1, (*it).y + 1, arcade::TileType::MY_SHOOT);

  _core->getLib()->aTile(_apple.x, _apple.y, arcade::TileType::POWERUP);
  _core->refreshGui();
  _core->getLib()->aRefresh();
}

void			LSnake::changeAction()
{
  switch (_map->type)
    {
    case (arcade::CommandType::GO_UP):
      if (_direction != arcade::CommandType::GO_DOWN)
	_direction = arcade::CommandType::GO_UP;
      break;
    case (arcade::CommandType::GO_DOWN):
      if (_direction != arcade::CommandType::GO_UP)
	_direction = arcade::CommandType::GO_DOWN;
      break;
    case (arcade::CommandType::GO_LEFT):
      if (_direction != arcade::CommandType::GO_RIGHT)
	_direction = arcade::CommandType::GO_LEFT;
      break;
    case (arcade::CommandType::GO_RIGHT):
      if (_direction != arcade::CommandType::GO_LEFT)
	_direction = arcade::CommandType::GO_RIGHT;
      break;
    default:
      break;
  }
  _map->type = arcade::CommandType::UNDEFINED;
}

void			LSnake::addScore(int points)
{
  _score += points;
}

bool			LSnake::checkNextTile(int y, int x)
{
  int			nextTile;

  nextTile = (y) * 50 + x;
  if (_map->tile[nextTile] == arcade::TileType::EMPTY ||
      _map->tile[nextTile] == arcade::TileType::POWERUP)
    for (std::vector<arcade::Position>::iterator it = _position.end(); it != _position.begin() + 1; it--)
      {
	if (x == (*it).x && y == (*it).y)
	  return (false);
      }
  else
    return (false);

  if (x == _apple.x - 1 && y == _apple.y - 1)
    {
      newApple();
      addQueue();
      addScore(10);
      if (_lPDM == false)
	_core->setScore(std::to_string(_score));
    }
  return (true);
}

void			LSnake::move()
{
  bool			canMove;

  canMove = true;
  switch (_direction)
    {
    case (arcade::CommandType::GO_UP):
      canMove = checkNextTile(_position[0].y - 1, _position[0].x);
      break;
    case (arcade::CommandType::GO_DOWN):
      canMove = checkNextTile(_position[0].y + 1, _position[0].x);
      break;
    case (arcade::CommandType::GO_LEFT):
      canMove = checkNextTile(_position[0].y, _position[0].x - 1);
      break;
    case (arcade::CommandType::GO_RIGHT):
      canMove = checkNextTile(_position[0].y, _position[0].x + 1);
      break;
    default:
      break;
    }

  if (canMove == true)
    {
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
	default:
	  break;
	}
    }
  else
    gameOver();
}

arcade::CommandType			LSnake::mainLoop(bool lPDM)
{
  std::clock_t		cur_time = clock();
  std::clock_t		old_time = clock();
  arcade::CommandType lastCommand;

  _lPDM = lPDM;
  initGame();
  if (lPDM == false)
    {
      initTextures();
      _core->setScore(std::to_string(_score));
    }
  while (_map->type != arcade::CommandType::ESCAPE && _map->type != arcade::CommandType::MENU)
    {
      cur_time = clock();
      if (_lPDM == true)
      {
        std::string tmp;
        std::cin >> tmp;
        _map->type = lPDM_aCommand(tmp);
      switch(_map->type)
      {
      case (arcade::CommandType::GET_MAP):
      lPDM_getMap();
      break;
      case (arcade::CommandType::WHERE_AM_I):
      lPDM_whereAmI();
      break;
      case (arcade::CommandType::GO_UP):
      lPDM_move(arcade::CommandType::GO_UP);
      break;
      case (arcade::CommandType::GO_DOWN):
      lPDM_move(arcade::CommandType::GO_DOWN);
      break;
      case (arcade::CommandType::GO_LEFT):
      lPDM_move(arcade::CommandType::GO_LEFT);
      break;
      case (arcade::CommandType::GO_RIGHT):
      lPDM_move(arcade::CommandType::GO_RIGHT);
      break;
      case (arcade::CommandType::PLAY):
      lPDM_play();
      break;
      default:
      break;
      }
      }
      else
      {
        lastCommand = _core->getLib()->aCommand();
        if (lastCommand != arcade::CommandType::UNDEFINED)
          _map->type = lastCommand;
        switch (_map->type)
        {
          case arcade::CommandType::NEXT_LIB :
            _core->switchLib(arcade::CommandType::NEXT_LIB);
            initTextures();
            _map->type = arcade::CommandType::UNDEFINED;
            break;
          case arcade::CommandType::PREV_LIB :
            _core->switchLib(arcade::CommandType::PREV_LIB);
            initTextures();
            _map->type = arcade::CommandType::UNDEFINED;
            break;
          case arcade::CommandType::NEXT_GAME :
            return(arcade::CommandType::NEXT_GAME);
          case arcade::CommandType::PREV_GAME :
            return(arcade::CommandType::PREV_GAME);
          default :
            break;
        }
      }

      if (cur_time > old_time + (100000 - (int)_position.size()))
      {
        changeAction();
        move();
        if (lPDM == false)
        {
        printGame();
        }
	      old_time = clock();
      }
    }
  return (_map->type);
}

void							LSnake::gameOver()
{
  _core->setScore(std::to_string(_score));
  _core->getLib()->aClear();
  _core->getLib()->aPutText(pos_x(2.7), pos_y(2.25), "core/res/fonts/press_start.ttf", WIDTH / 40, arcade::Color::A_RED, "GAME OVER");
  _core->getLib()->aPutText(pos_x(3.1), pos_y(1.8), "core/res/fonts/press_start.ttf", WIDTH / 100, arcade::Color::A_WHITE, "PRESS ENTER TO RESTART THE GAME.");
  _core->getLib()->aPutText(pos_x(2.7), pos_y(2.25), "core/res/fonts/press_start.ttf", WIDTH / 40, arcade::Color::A_RED, "GAME OVER");
  _core->getLib()->aRefresh();
  while (1)
    {
      _map->type = _core->getLib()->aCommand();
      if (_map->type == arcade::CommandType::ESCAPE)
	{
	  _core->saveScore(_score);
	  exit(0);
	}
      if (_map->type == arcade::CommandType::MENU)
	{
	  _core->saveScore(_score);
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
    switch (command[0])
      {
      case 0:
	std::cout << "LA PUTE\n";
	return (arcade::CommandType::WHERE_AM_I);
      case 1:
	return (arcade::CommandType::GET_MAP);
      case 2:
        return (arcade::CommandType::GO_UP);
      case 3:
	return (arcade::CommandType::GO_DOWN);
      case 4:
	return (arcade::CommandType::GO_LEFT);
      case 5:
	return (arcade::CommandType::GO_RIGHT);
      case 9:
	return (arcade::CommandType::PLAY);
      default:
	break;
      }

  return (arcade::CommandType::UNDEFINED);
}

void                  LSnake::lPDM_getMap() const
{
  write(1, _map, sizeof(arcade::GetMap) * (_map->width * _map->height));
}

void			LSnake::lPDM_whereAmI()
{
  arcade::WhereAmI	*snake;
  int			length;
  int			i;

  i = -1;
  length = 0;
  for (std::vector<arcade::Position>::iterator it = _position.end(); it != _position.begin(); it--)
    length++;
  if ((snake = (arcade::WhereAmI *)malloc(sizeof(arcade::WhereAmI)  * length)) == NULL)
    return ;
  snake->type = _map->type;
  snake->lenght = length;
  for (std::vector<arcade::Position>::iterator it = _position.end(); it != _position.begin(); it--)
    snake->position[i] = *it;
  std::cout << "COUILLE MOLLE\n";
  write(1, snake, sizeof(arcade::WhereAmI));
}

void			LSnake::lPDM_move(arcade::CommandType direction)
{
  (void)direction;
}

void			LSnake::lPDM_play()
{

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

    snake.mainLoop(true);
  }
}
