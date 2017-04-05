/*
** SolarFox.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:07:46 2017 gastal_r
** Last update	Sun Mar 26 04:12:03 2017 gastal_r
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

  for (unsigned int i = 0 ; i < 50 * 53 ; i++)
    _core->getLib()->aTile((i % _map->width) + 1, (i / _map->height) + 1, _map->tile[i], arcade::CommandType::UNDEFINED);

  if (_missile.size() > 1)
    for (std::vector<Missile>::iterator it = _missile.begin() ; it != _missile.end() - 1 ; ++it)
      _core->getLib()->aTile((*it).getX() + 1, (*it).getY() + 1, arcade::TileType::MY_SHOOT, getDirection((*it), (*(it + 1))));

  if (_enemyMissile.size() > 1)
    for (std::vector<EnemyMissile>::iterator it = _enemyMissile.begin() ; it != _enemyMissile.end() - 1 ; ++it)
      _core->getLib()->aTile((*it).getX() + 1, (*it).getY() + 1, arcade::TileType::EVIL_SHOOT, getDirection((*it), (*(it + 1))));

  for (std::vector<EnemyShip>::iterator it = _enemyShip.begin() ; it != _enemyShip.end() - 1 ; ++it)
    _core->getLib()->aTile((*it).getX() + 1, (*it).getY() + 1, arcade::TileType::EVIL_DUDE, getDirection((*it), (*(it + 1))));

  _core->getLib()->aTile(_ship.getX(), _ship.getY(), arcade::TileType::OTHER, arcade::CommandType::UNDEFINED);

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

void			LSolarFox::initGame(void)
{
  std::ifstream		file("games/solar_fox/res/map/level_1.map");
  int			sizeLine;
  std::string		content;
  std::string		line;
  int			j;

  j = -1;
  _score = 0;
  srand(time(NULL));
  _direction = arcade::CommandType::GO_UP;

  if ((_map = (arcade::GetMap *)malloc(sizeof(arcade::GetMap) + (50 * 53 * sizeof(arcade::TileType)))) == NULL)
    throw arcade::Exception("Malloc failed\n");
  _map->type = arcade::CommandType::GO_UP;
  _map->width = 50;
  _map->height = 50;

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

arcade::CommandType	LSolarFox::mainLoop(bool lPDM)
{
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point t2;
  arcade::CommandType	lastCommand;

  _lPDM = lPDM;
  initGame();
  if (_lPDM == false)
    {
      initTextures();
      _core->setScore(std::to_string(_score));
    }
  while (_map->type != arcade::CommandType::ESCAPE && _map->type != arcade::CommandType::MENU)
    {
      if (_lPDM == false)
	{
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
	}
      else
	{
	  //lPDM 
	}

      if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() >= 16 && _lPDM == false)
      	{
	  // changeAction();
	  // move();
	  if (_lPDM == false)
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
  return (mainLoop(false));
}

void			LSolarFox::close(void)
{

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

    solarfox.mainLoop(true);
  }
}

