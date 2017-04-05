/*
** SolarFox.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:07:46 2017 gastal_r
// Last update Wed Apr  5 20:18:28 2017 sellet_f
*/

#include        "LSolarFox.hpp"

LSolarFox::LSolarFox()
{
}

LSolarFox::~LSolarFox()
{
}

void		        LSolarFox::printGame(void)
{
  _core->getLib()->aClear();

  for (unsigned int i = 0 ; i < 41 * 41 ; i++)
    _core->getLib()->aTile((i % _map->width) + 1, (i / _map->height) + 1, SOLAR_SPEED, _map->tile[i], arcade::CommandType::UNDEFINED);

  if (_missile.size() > 1)
    for (std::vector<Missile>::iterator it = _missile.begin() ; it != _missile.end() - 1 ; ++it)
      if ((*it).checkPrint((*it)) == true)
  	_core->getLib()->aTile((*it).getX() + 1, (*it).getY() + 1, SOLAR_SPEED, arcade::TileType::MY_SHOOT, getDirection((*it), (*(it + 1))));

  if (_enemyMissile.size() > 1)
    for (std::vector<EnemyMissile>::iterator it = _enemyMissile.begin() ; it != _enemyMissile.end() - 1 ; ++it)
      if ((*it).checkPrint((*it)) == true)
  	_core->getLib()->aTile((*it).getX() + 1, (*it).getY() + 1, SOLAR_SPEED, arcade::TileType::EVIL_SHOOT, getDirection((*it), (*(it + 1))));

  for (std::vector<EnemyShip>::iterator it = _enemyShip.begin() ; it != _enemyShip.end() - 1 ; ++it)
    if ((*it).checkPrint((*it)) == true)
      _core->getLib()->aTile((*it).getX() + 1, (*it).getY() + 1, SOLAR_SPEED, arcade::TileType::EVIL_DUDE, getDirection((*it), (*(it + 1))));

  _core->getLib()->aTile(_ship.getX(), _ship.getY(), SOLAR_SPEED, arcade::TileType::OTHER, arcade::CommandType::UNDEFINED);

  _core->refreshGui();
  _core->getLib()->aRefresh();
}

void			LSolarFox::initTextures(void)
{
  _core->getLib()->aAssignTexture(arcade::TileType::EMPTY, "games/solar_fox/res/img/floor2.png", arcade::Color::A_WHITE);
  _core->getLib()->aAssignTexture(arcade::TileType::OBSTACLE, "games/solar_fox/res/img/floor2.png", arcade::Color::A_RED);
  _core->getLib()->aAssignTexture(arcade::TileType::OTHER, "games/solar_fox/res/img/tron.png", arcade::Color::A_BLACK);
  _core->getLib()->aAssignTexture(arcade::TileType::MY_SHOOT, "games/solar_fox/res/img/wall3.png", arcade::Color::A_MAGENTA);
  _core->getLib()->aAssignTexture(arcade::TileType::POWERUP, "games/solar_fox/res/img/mooncat.jpg", arcade::Color::A_MAGENTA);
}

void			LSolarFox::initGame(bool lPDM)
{
  std::ifstream		file("games/solar_fox/res/map/level_1.map");
  EnemyShip		enemyShip;
  int			sizeLine;
  std::string		content;
  std::string		line;
  int			j;

  _lPDM = lPDM;

  j = -1;
  _score = 0;
  srand(time(NULL));
  _direction = arcade::CommandType::GO_UP;
  _position.x = MAP_WIDTH / 2;
  _position.y = MAP_HEIGHT / 2;

  enemyShip.setX(0);
  enemyShip.setY(0);
  enemyShip.setSpeed(5);
  enemyShip.setIt(5);
  enemyShip.setDirection(arcade::CommandType::GO_UP);

  _enemyShip.push_back(enemyShip);

  enemyShip.setX(40);
  enemyShip.setDirection(arcade::CommandType::GO_RIGHT);

  _enemyShip.push_back(enemyShip);

  enemyShip.setY(40);
  enemyShip.setDirection(arcade::CommandType::GO_DOWN);

  _enemyShip.push_back(enemyShip);

  enemyShip.setX(0);
  enemyShip.setDirection(arcade::CommandType::GO_LEFT);

  _enemyShip.push_back(enemyShip);

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
	  default :
	    throw arcade::Exception("Invalid map.");
	    break;
	  }
    }
  else
    throw arcade::Exception("Invalid file.");
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
	  // changeAction();
	  // move();
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
  snake->position[0] = _position;
  write(1, snake, sizeof(arcade::WhereAmI) + (length * sizeof(arcade::Position)));
  free(snake);
}

void			LSolarFox::lPDM_start()
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
      //  move();
        break;
      default:
        break;
      }
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
