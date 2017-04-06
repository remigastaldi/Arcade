/*
** SolarFox.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:07:46 2017 gastal_r
** Last update	Thu Apr 06 13:54:46 2017 gastal_r
*/

#include        "LSolarFox.hpp"

LSolarFox::LSolarFox()
{
}

LSolarFox::~LSolarFox()
{
}

#include <chrono>
#include <thread>
void		        LSolarFox::printGame(void)
{
  _core->getLib()->aClear();

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  if (_missile.size() > 1)
    for (std::vector<Missile>::iterator it = _missile.begin() ; it != _missile.end() - 1 ; ++it)
      if ((*it).checkAction(true) == true)
  	_core->getLib()->aTile((*it).getX() + 1, (*it).getY() + 1, (*it).getSpeed(), arcade::TileType::MY_SHOOT, getDirection((*it), (*(it + 1))));

  if (_enemyMissile.size() > 1)
    for (std::vector<EnemyMissile>::iterator it = _enemyMissile.begin() ; it != _enemyMissile.end() - 1 ; ++it)
      if ((*it).checkAction(true) == true)
  	_core->getLib()->aTile((*it).getX() + 1, (*it).getY() + 1, (*it).getSpeed(), arcade::TileType::EVIL_SHOOT, getDirection((*it), (*(it + 1))));

  if (_ship.checkAction(true) == true)
    _core->getLib()->aTile(_ship.getX() + 1, _ship.getY() + 1, _ship.getSpeed(), arcade::TileType::OTHER, _ship.getDirection());

  for (std::vector<EnemyShip>::iterator it = _enemyShip.begin() ; it != _enemyShip.end() ; ++it)
    if ((*it).checkAction(true) == true)
      _core->getLib()->aTile((*it).getX() + 1, (*it).getY() + 1, (*it).getSpeed(), arcade::TileType::EVIL_DUDE, it->getDirection());

  for (unsigned int i = 0 ; i < 41 * 41 ; i++)
    _core->getLib()->aTile((i % _map->width) + 1, (i / _map->height) + 1, 0, _map->tile[i], arcade::CommandType::UNDEFINED);

  _core->refreshGui();
  _core->getLib()->aRefresh();
}

void			LSolarFox::initTextures(void)
{
  _core->getLib()->aAssignTexture(arcade::TileType::EMPTY, "games/solarfox/res/img/floor2.png", arcade::Color::A_WHITE);
  _core->getLib()->aAssignTexture(arcade::TileType::BLOCK, "games/solarfox/res/img/wall2.png", arcade::Color::A_RED);
  _core->getLib()->aAssignTexture(arcade::TileType::OTHER, "games/solarfox/res/img/tron.png", arcade::Color::A_BLACK);
  _core->getLib()->aAssignTexture(arcade::TileType::MY_SHOOT, "games/solarfox/res/img/wall3.png", arcade::Color::A_MAGENTA);
  _core->getLib()->aAssignTexture(arcade::TileType::POWERUP, "games/solarfox/res/img/mooncat.jpg", arcade::Color::A_MAGENTA);
  _core->getLib()->aAssignTexture(arcade::TileType::EVIL_DUDE, "games/solarfox/res/img/wall.png", arcade::Color::A_BLUE);
}

void			LSolarFox::initGame(bool lPDM)
{
  std::ifstream		file("games/solarfox/res/map/level_1.map");
  EnemyShip		enemyShip;
  int			sizeLine;
  std::string		content;
  std::string		line;
  int			j;

  j = -1;
  _score = 0;
  _lPDM = lPDM;
  srand(time(NULL));

  if ((_map = (arcade::GetMap *)malloc(sizeof(arcade::GetMap) + (41 * 41 * sizeof(arcade::TileType)))) == NULL)
    throw arcade::Exception("Malloc failed\n");
  _map->type = arcade::CommandType::GO_UP;
  _map->width = 41;
  _map->height = 41;

  if (file)
    {
      std::getline(file, line);
      sizeLine = line.length();
      content += line;

      while (getline(file, line))
      	{
      	  if ((unsigned int)sizeLine != line.length())
      	    throw arcade::Exception("Invalid map.");
      	  content += line;
      	}

      for (unsigned int i = 0 ; i < content.length() ; i++)
	switch (content[i])
	  {
	  case '#' :
	    _map->tile[++j] = arcade::TileType::BLOCK;
	    break;
	  case ' ' :
	    _map->tile[++j] = arcade::TileType::EMPTY;
	    break;
	  case '1' :
	    _map->tile[++j] = arcade::TileType::POWERUP;
	    break;
	  case 'V' :
	    _map->tile[++j] = arcade::TileType::EMPTY;
	    _ship.setX(i % _map->width);
	    _ship.setY(i / _map->height);
	    _ship.setSpeed(7);
	    _ship.setIt(10);
	    _ship.setDirection(arcade::CommandType::GO_UP);
	    break;
	  case 'E':
	    _map->tile[++j] = arcade::TileType::EMPTY;
	    enemyShip.setX(i % _map->width);
	    enemyShip.setY(i / _map->height);
	    enemyShip.setSpeed(7);
	    enemyShip.setIt(10);
	    if ((i % _map->width == 1 && i / _map->height == 1) || (i % _map->width == 39 && i / _map->height == 39))
	      enemyShip.setDirection(arcade::CommandType::GO_LEFT);
	    else
	      enemyShip.setDirection(arcade::CommandType::GO_UP);
	    _enemyShip.push_back(enemyShip);
	    break;
	  default :
	    throw arcade::Exception("Invalid map.");
	    break;
	  }
    }
  else
    throw arcade::Exception("Invalid file.");
}

void			LSolarFox::changeAction()
{
  arcade::CommandType direction;

  direction = _ship.getDirection();
  switch (_map->type)
    {
    case (arcade::CommandType::GO_UP):
      if (direction != arcade::CommandType::GO_DOWN &&
	  _map->tile[(_ship.getY() - 1) * 41 + _ship.getX()] != arcade::TileType::BLOCK)
	direction = arcade::CommandType::GO_UP;
      break;
    case (arcade::CommandType::GO_DOWN):
      if (direction != arcade::CommandType::GO_UP &&
	  _map->tile[(_ship.getY() + 1) * 41 + _ship.getX()] != arcade::TileType::BLOCK)
	direction = arcade::CommandType::GO_DOWN;
      break;
    case (arcade::CommandType::GO_LEFT):
      if (direction != arcade::CommandType::GO_RIGHT &&
	  _map->tile[_ship.getY() * 41 + _ship.getX() - 1] != arcade::TileType::BLOCK)
	direction = arcade::CommandType::GO_LEFT;
      break;
    case (arcade::CommandType::GO_RIGHT):
      if (direction != arcade::CommandType::GO_LEFT &&
	  _map->tile[_ship.getY() * 41 + _ship.getX() + 1] != arcade::TileType::BLOCK)
	direction = arcade::CommandType::GO_RIGHT;
      break;
    default:
      break;
    }
  _ship.setDirection(direction);
  _map->type = arcade::CommandType::UNDEFINED;
}

void    LSolarFox::move()
{
  if (_ship.checkAction(false))
    switch (_ship.getDirection())
      {
      case (arcade::CommandType::GO_UP):
	if (_map->tile[(_ship.getY() - 1) * 41 + _ship.getX()] != arcade::TileType::BLOCK)
	  _ship.setY(_ship.getY() - 1);
	break;
      case (arcade::CommandType::GO_DOWN):
	if (_map->tile[(_ship.getY() + 1) * 41 + _ship.getX()] != arcade::TileType::BLOCK)
	  _ship.setY(_ship.getY() + 1);
	break;
      case (arcade::CommandType::GO_LEFT):
	if (_map->tile[_ship.getY() * 41 + _ship.getX() - 1] != arcade::TileType::BLOCK)
	  _ship.setX(_ship.getX() - 1);
	break;
      case (arcade::CommandType::GO_RIGHT):
	if (_map->tile[_ship.getY() * 41 + _ship.getX() + 1] != arcade::TileType::BLOCK)
	  _ship.setX(_ship.getX() + 1);
	break;
      default:
	break;
  }

  for (std::vector<EnemyShip>::iterator it = _enemyShip.begin() ; it != _enemyShip.end() ; ++it)
    {
      if ((*it).checkAction(false))
	switch ((*it).getDirection())
	  {
	  case arcade::CommandType::GO_UP :
	    if ((*it).getY() == 1)
	      (*it).setDirection(arcade::CommandType::GO_DOWN);
	    else
	      (*it).setY((*it).getY() - 1);
	    break;
	  case arcade::CommandType::GO_DOWN :
	    if ((*it).getY() == 39)
	      (*it).setDirection(arcade::CommandType::GO_UP);
	    else
	      (*it).setY((*it).getY() + 1);
	    break;
	  case arcade::CommandType::GO_LEFT :
	    if ((*it).getX() == 1)
	      (*it).setDirection(arcade::CommandType::GO_RIGHT);
	    else
	      (*it).setX((*it).getX() - 1);
	    break;
	  case arcade::CommandType::GO_RIGHT :
	    if ((*it).getX() == 39)
	      (*it).setDirection(arcade::CommandType::GO_LEFT);
	    else
	      (*it).setX((*it).getX() + 1);
	    break;
	  default:
	    break;
	}
    }
}

arcade::CommandType	LSolarFox::mainLoop(void)
{
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point t2;
  arcade::CommandType	lastCommand;

  initTextures();
  _core->setScore(std::to_string(_score));
  while (_map->type != arcade::CommandType::ESCAPE && _map->type != arcade::CommandType::MENU)
    {
      t2 = std::chrono::high_resolution_clock::now();
      lastCommand = _core->getLib()->aCommand();

      if (lastCommand != arcade::CommandType::UNDEFINED)
	       _map->type = lastCommand;

      switch(_map->type)
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
	case arcade::CommandType::NEXT_GAME :
	  return (arcade::CommandType::NEXT_GAME);
	case arcade::CommandType::PREV_GAME :
	  return (arcade::CommandType::PREV_GAME);
	default :
	  break;
	}

      if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() >= 16)
      	{
          changeAction();
          move();
	  printGame();
          t1 = std::chrono::high_resolution_clock::now();
        }
    }
  return (_map->type);
}

arcade::CommandType	LSolarFox::getDirection(Object const &cur, Object const&prev)
{
  if (cur.getX() - 1 == prev.getX())
    return (arcade::CommandType::GO_RIGHT);
  else if (cur.getX() + 1 == prev.getX())
    return (arcade::CommandType::GO_LEFT);
  else if (cur.getY() - 1 == prev.getY())
    return (arcade::CommandType::GO_DOWN);
  else if (cur.getY() + 1 == prev.getY())
    return (arcade::CommandType::GO_UP);
  return (arcade::CommandType::UNDEFINED);
}

arcade::CommandType	LSolarFox::play(arcade::ICore& core)
{
  _core = &core;
  initGame(false);
  return (mainLoop());
}

void			LSolarFox::close(void)
{

}

void			LSolarFox::lPDM_getMap() const
{
  write(1, _map, sizeof(arcade::GetMap) + (_map->width * _map->height * sizeof(arcade::TileType)));
}

void			LSolarFox::lPDM_whereAmI()
{
  arcade::WhereAmI	*snake;
  int			length;

  length = 1;
  if ((snake = (arcade::WhereAmI *)malloc(sizeof(arcade::WhereAmI) + (length * sizeof(arcade::Position)))) == NULL)
    return ;
  snake->type = _map->type;
  snake->lenght = length;
  snake->position[0].x = _ship.getX();
  snake->position[0].y = _ship.getY();
  write(1, snake, sizeof(arcade::WhereAmI) + (length * sizeof(arcade::Position)));
  free(snake);
}

void			LSolarFox::lPDM_start()
{
  arcade::CommandType command;
  arcade::CommandType direction;

  while (!std::cin.eof())
  {
    std::cin.read((char *) &command, sizeof(arcade::CommandType));
    _map->type = command;
    direction = _ship.getDirection();
    switch(_map->type)
      {
      case (arcade::CommandType::GET_MAP):
        lPDM_getMap();
        break;
      case (arcade::CommandType::WHERE_AM_I):
        lPDM_whereAmI();
        break;
      case (arcade::CommandType::GO_UP):
          direction = arcade::CommandType::GO_UP;
        break;
      case (arcade::CommandType::GO_DOWN):
          direction = arcade::CommandType::GO_DOWN;
        break;
      case (arcade::CommandType::GO_LEFT):
          direction = arcade::CommandType::GO_LEFT;
        break;
      case (arcade::CommandType::GO_RIGHT):
          direction = arcade::CommandType::GO_RIGHT;
        break;
      case (arcade::CommandType::PLAY):
        move();
        break;
      default:
        break;
      }
      _ship.setDirection(direction);
  }
}

extern "C"
{
  LSolarFox		*createGame(void)
  {
    return (new LSolarFox());
  }

  void			deleteGame(arcade::IGame *game)
  {
    if (game != NULL)
      delete (game);
  }

  void			Play()
  {
    LSolarFox		solarfox;

    solarfox.initGame(true);
    solarfox.lPDM_start();
  }
}
