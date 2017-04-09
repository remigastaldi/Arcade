/*
** lib_arcade_snake.cpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 18:43:53 2017 gastal_r
** Last update	Sun Apr 09 22:56:25 2017 gastal_r
*/

#include          "LSnake.hpp"

LSnake::LSnake()
{
  _map = 0;
  _core = 0;
}

LSnake::~LSnake()
{
  _map ? delete(_map) : (void)0;
}

arcade::CommandType				LSnake::play(arcade::ICore &core)
{
  initGame(false);
  _core = &core;
  return (mainLoop());
}

void      LSnake::initTextures()
{
  _core->getLib()->aAssignTexture(arcade::TileType::EMPTY, SNAKE_RES "img/green_darker2.png", arcade::Color::A_WHITE);
  _core->getLib()->aAssignTexture(arcade::TileType::OBSTACLE, SNAKE_RES "img/red_neon.png", arcade::Color::A_RED);
  _core->getLib()->aAssignTexture(arcade::TileType::SHIP, SNAKE_RES "img/blue_neon.png", arcade::Color::A_BLUE);
  _core->getLib()->aAssignTexture(arcade::TileType::OTHER, SNAKE_RES "img/purple_neon.png", arcade::Color::A_MAGENTA);
  _core->getLib()->aAssignTexture(arcade::TileType::POWERUP, SNAKE_RES "img/yellow_neon.png", arcade::Color::A_YELLOW);
}

void			LSnake::initGame(bool lPDM)
{
  arcade::Position	head;

  _lPDM = lPDM;
  std::srand(std::time(NULL));
  _map = new arcade::GetMap[(MAP_WIDTH * MAP_HEIGHT * sizeof(arcade::TileType))];
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
      for (std::vector<arcade::Position>::const_iterator it = _position.begin() + 1; it != _position.end() - 1; ++it)
        _core->getLib()->aTile((*it).x + 1, (*it).y + 1, SNAKE_SPEED, arcade::TileType::OTHER, getDirection((*it), (*(it + 1))));
  _speed = SNAKE_SPEED;
  }
  else
    _speed++;
  _core->getLib()->aTile(_apple.x, _apple.y, 0,arcade::TileType::POWERUP, arcade::CommandType::UNDEFINED);

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
      _core->getLib()->aPlaySound(arcade::Sound::POWERUP);
      newApple();
      for (int i = std::rand() % 3 + 1 ; i > 0 ; --i)
	addQueue();
      addScore(10);
      if (_lPDM == false)
	{
	  _core->setScore(std::to_string(_score));
	  newBlock();
	}
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
  _map->type = arcade::CommandType::UNDEFINED;
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
	  if (_map->type == arcade::CommandType::UNDEFINED)
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
	    case arcade::CommandType::MENU :
	      _core->getLib()->aClearAnimBuffer();
	      _core->setScore(std::to_string(_score));
	      return (arcade::CommandType::MENU);
	    case arcade::CommandType::RESTART :
	      _core->getLib()->aClearAnimBuffer();
	      _core->setScore(std::to_string(_score));
	      return (arcade::CommandType::RESTART);
	    default :
	      break;
	    }

	  if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() >= 16)
	    {
	      changeAction();
	      if (_speed == 10)
		move();
	      if (_exitStatus == arcade::CommandType::MENU || _exitStatus == arcade::CommandType::ESCAPE)
		return (_exitStatus);

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

void			LSnake::addQueue()
{
  _position.push_back(_position[_position.size() - 1]);
}

bool			LSnake::checkSnakeColision(int tile) const
{
  for (std::vector<arcade::Position>::const_iterator it = _position.begin() ; it != _position.end() ; ++it)
    if (tile % MAP_WIDTH == it->x && tile / MAP_HEIGHT == it->y)
      return (false);
  return (true);
}

void			LSnake::newBlock()
{
  int			tile;

  while (checkSnakeColision(tile = std::rand() % (MAP_WIDTH * MAP_HEIGHT - 2)) == false
                            || _map->tile[tile] != arcade::TileType::EMPTY);
  _map->tile[tile] = arcade::TileType::OBSTACLE;
}

void			LSnake::newApple()
{
  int			tile;

  _apple.x = (std::rand() % (MAP_WIDTH - 2)) + 2;
  _apple.y = (std::rand() % (MAP_HEIGHT - 2)) + 2;
  tile = (_apple.y - 1) * MAP_HEIGHT + _apple.x - 1;
  while (checkSnakeColision(tile) == false || _map->tile[tile] != arcade::TileType::EMPTY)
    {
      _apple.x = (std::rand() % (MAP_WIDTH - 2)) + 2;
      _apple.y = (std::rand() % (MAP_HEIGHT - 2)) + 2;
      tile = (_apple.y - 1) * MAP_HEIGHT + _apple.x - 1;
    }
}

void                  LSnake::lPDM_getMap() const
{
  std::cout.write(reinterpret_cast<char *>(_map), sizeof(arcade::GetMap) + (MAP_WIDTH * MAP_HEIGHT * sizeof(arcade::TileType)));
}

void			LSnake::lPDM_whereAmI()
{
  arcade::WhereAmI	*snake;
  int			length;
  int			i;

  i = 0;
  length = _position.size() - 1;
  snake = new arcade::WhereAmI[(length * sizeof(arcade::Position))];
  snake->type = _map->type;
  snake->lenght = length;
  for (std::vector<arcade::Position>::const_iterator it = _position.begin(); it != _position.end() - 1; ++it)
  {
    snake->position[i] = *it;
    i++;
  }
  std::cout.write(reinterpret_cast<char *>(snake), sizeof(arcade::WhereAmI) + (length * sizeof(arcade::Position)));
  delete(snake);
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
