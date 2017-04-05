/*
** lib_arcade_snake.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:43:53 2017 gastal_r
** Last update	Thu Apr 06 01:10:39 2017 gastal_r
*/

#include          "LSnake.hpp"

LSnake::LSnake()
{
  _map = 0;
  _core = 0;
}

LSnake::~LSnake()
{
  _map ? free(_map) : (void)0;
}

arcade::CommandType				LSnake::play(arcade::ICore &core)
{
  initGame(false);
  _core = &core;
  return (mainLoop());
}

void      LSnake::initTextures()
{
  _core->getLib()->aAssignTexture(arcade::TileType::EMPTY, SNAKE_RES "img/floor2.png", arcade::Color::A_WHITE);
  _core->getLib()->aAssignTexture(arcade::TileType::OBSTACLE, SNAKE_RES "img/wall.png", arcade::Color::A_RED);
  _core->getLib()->aAssignTexture(arcade::TileType::SHIP,"games/solar_fox/res/img/ship.png", arcade::Color::A_GREEN);
  _core->getLib()->aAssignTexture(arcade::TileType::MY_SHOOT, SNAKE_RES "img/wall3.png", arcade::Color::A_MAGENTA);
  _core->getLib()->aAssignTexture(arcade::TileType::POWERUP, SNAKE_RES "img/mooncat.jpg", arcade::Color::A_MAGENTA);
}

void			LSnake::initGame(bool lPDM)
{
  arcade::Position	head;

  _lPDM = lPDM;
  srand(time(NULL));
  if ((_map = (arcade::GetMap *)malloc(sizeof(arcade::GetMap) + (MAP_WIDTH * MAP_HEIGHT * sizeof(arcade::TileType)))) == NULL)
    throw arcade::Exception("Malloc failed\n");

  _exitStatus = arcade::CommandType::UNDEFINED;
  _map->type = arcade::CommandType::GO_UP;
  _direction = arcade::CommandType::GO_UP;
  _map->width = MAP_WIDTH;
  _map->height = MAP_HEIGHT;
  _speed = SNAKE_SPEED;
  _score = 0;

  for (int i = 0 ; i < MAP_WIDTH * MAP_HEIGHT ; ++i)
    if (((i % MAP_WIDTH) == 0 || (i % MAP_WIDTH) == MAP_WIDTH - 1) ||
	((i / MAP_HEIGHT) == 0 || (i / MAP_HEIGHT) == MAP_HEIGHT - 1))
      _map->tile[i] = arcade::TileType::OBSTACLE;
    else
    _map->tile[i] = arcade::TileType::EMPTY;

  for (size_t i = 0; i < 5; i++)
  {

      head.x = _map->width / 2;
      head.y = _map->height / 2 + i;

      _position.push_back(head);
  }

  newApple();
}

arcade::CommandType	LSnake::getDirection(arcade::Position const &cur, arcade::Position const &prev)
{
  if (cur.x - 1 == prev.x)
    return (arcade::CommandType::GO_RIGHT);
  else if (cur.x + 1 == prev.x)
    return (arcade::CommandType::GO_LEFT);
  else if (cur.y - 1 == prev.y)
    return (arcade::CommandType::GO_DOWN);
  else if (cur.y + 1 == prev.y)
    return (arcade::CommandType::GO_UP);
  return (arcade::CommandType::UNDEFINED);
}

void			LSnake::printGame()
{
  _core->getLib()->aClear();

  if (_speed == 10)
  {
    _core->getLib()->aTile(_position[0].x + 1, _position[0].y + 1, SNAKE_SPEED, arcade::TileType::SHIP, _direction);
    if (_position.size() > 1)
      for (std::vector<arcade::Position>::iterator it = _position.begin() + 1; it != _position.end() - 1; ++it)
        _core->getLib()->aTile((*it).x + 1, (*it).y + 1, SNAKE_SPEED, arcade::TileType::MY_SHOOT, getDirection((*it), (*(it + 1))));
  _speed = SNAKE_SPEED;
  }
  else
    _speed++;
  _core->getLib()->aTile(_apple.x, _apple.y, 0,arcade::TileType::POWERUP, arcade::CommandType::UNDEFINED);

static int i = 10;
static int j = 10;
static int x = 5;
static int k = 5;

if (i == 10)
{
  _core->getLib()->aTile(x, 20, 4, arcade::TileType::MY_SHOOT, arcade::CommandType::GO_RIGHT);
  x++;
  if (x == 40)
    x = 5;
  i = 4;
}
else
  i++;

if (j == 10)
{
  _core->getLib()->aTile(k, 21, 8, arcade::TileType::MY_SHOOT, arcade::CommandType::GO_RIGHT);
  k++;
  if (k == 40)
    k = 5;
  j = 8;
}
else
  j++;

for (int i = 0 ; i < MAP_WIDTH * MAP_HEIGHT ; ++i)
  _core->getLib()->aTile((i % _map->width) + 1 , (i / _map->width) + 1, 0, _map->tile[i], arcade::CommandType::UNDEFINED);

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

  nextTile = (y) * MAP_HEIGHT + x;
  if (_map->tile[nextTile] == arcade::TileType::EMPTY ||
      _map->tile[nextTile] == arcade::TileType::POWERUP)
    {
      if (_position.size() > 1)
	{
	  for (std::vector<arcade::Position>::iterator it = _position.end() - 2; it != _position.begin() + 1; --it)
	    {
	      if (x == (*it).x && y == (*it).y)
		return (false);
	    }
	}
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

  for (std::vector<arcade::Position>::iterator it = _position.end() - 1; it != _position.begin(); --it)
    {
      (*it).x = (*(it - 1)).x;
      (*it).y = (*(it - 1)).y;
    }

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
  else if (_lPDM != true)
    gameOver();
}

arcade::CommandType			LSnake::mainLoop()
{
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point t2;
  arcade::CommandType lastCommand;

  initTextures();
  _core->setScore(std::to_string(_score));
  while (_map->type != arcade::CommandType::ESCAPE && _map->type != arcade::CommandType::MENU)
    {
      t2 = std::chrono::high_resolution_clock::now();
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

      if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() >= 16)
    	{
        //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << '\n';
        changeAction();
        if (_speed == 10)
        {
          move();
        }
    	  if (_exitStatus == arcade::CommandType::MENU || _exitStatus == arcade::CommandType::ESCAPE)
        {
    	    return (_exitStatus);
        }
  	    printGame();
        t1 = std::chrono::high_resolution_clock::now();
    	}
    }
  return (_map->type);
}

void							LSnake::gameOver()
{
  _core->getLib()->aClearAnimBuffer();
  _core->setScore(std::to_string(_score));
  _core->gameOver();
  while (1)
    {
      _map->type = _core->getLib()->aCommand();
      if (_map->type == arcade::CommandType::ESCAPE)
      {
        _core->saveScore(_score);
        _exitStatus = arcade::CommandType::ESCAPE;
        return;
      }
      if (_map->type == arcade::CommandType::PLAY)
      {
        _core->saveScore(_score);
        _exitStatus = arcade::CommandType::MENU;
        return;
      }
    }
}

void			LSnake::close()
{
}

void			LSnake::addQueue()
{
  _position.push_back(_position[_position.size() - 1]);
}

void			LSnake::newApple()
{
  int			tile;

  _apple.x = (rand() % (MAP_WIDTH - 2)) + 2;
  _apple.y = (rand() % (MAP_HEIGHT - 2)) + 2;
  tile = (_apple.y) * MAP_HEIGHT + _apple.x;
  while (_map->tile[tile] != arcade::TileType::EMPTY)
    {
      _apple.x = (rand() % (MAP_WIDTH - 2)) + 2;
      _apple.y = (rand() % (MAP_HEIGHT - 2)) + 2;
      for (std::vector<arcade::Position>::iterator it = _position.end() - 1; it != _position.begin(); --it)
	if (_apple.x == (*it).x && _apple.y == (*it).y)
	  {
	    _apple.x = 0;
	    _apple.y = 0;
	  }
      tile = (_apple.y) * MAP_HEIGHT + _apple.x;
    }
  // for (std::vector<arcade::Position>::iterator it = _position.end(); it != _position.begin(); it--)
  //   if (_apple.x == (*it).x && _apple.y == (*it).y)
  //     newApple();
}

void                  LSnake::lPDM_getMap() const
{
  write(1, _map, sizeof(arcade::GetMap) + (MAP_WIDTH * MAP_HEIGHT * sizeof(arcade::TileType)));
}

void			LSnake::lPDM_whereAmI()
{
  arcade::WhereAmI	*snake;
  int			length;
  int			i;

  i = 0;
  length = _position.size() - 1;
  if ((snake = (arcade::WhereAmI *)malloc(sizeof(arcade::WhereAmI) + (length * sizeof(arcade::Position)))) == NULL)
    return ;
  snake->type = _map->type;
  snake->lenght = length;
  for (std::vector<arcade::Position>::iterator it = _position.begin(); it != _position.end() - 1; ++it)
  {
    snake->position[i] = *it;
    i++;
  }
  write(1, snake, sizeof(arcade::WhereAmI) + (length * sizeof(arcade::Position)));
  free(snake);
}

void			LSnake::lPDM_start()
{
  arcade::CommandType command;

  while (!std::cin.eof())
  {
    std::cin.read((char *) &command, sizeof(arcade::CommandType));
    _map->type = command;
    switch(_map->type)
      {
      case (arcade::CommandType::GET_MAP):
        lPDM_getMap();
        break;
      case (arcade::CommandType::WHERE_AM_I):
        lPDM_whereAmI();
        break;
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
      case (arcade::CommandType::PLAY):
        move();
        break;
      default:
        break;
      }
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

    snake.initGame(true);
    snake.lPDM_start();
  }
}
