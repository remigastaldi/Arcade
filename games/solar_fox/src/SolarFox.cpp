/*
** SolarFox.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:07:46 2017 gastal_r
** Last update	Sun Mar 26 04:12:03 2017 gastal_r
*/

#include        "SolarFox.hpp"

LSolarFox::LSolarFox()
{
}

LSolarFox::~LSolarFox()
{
}

void			LSolarFox::initTextures(void)
{

}

void			LSolarFox::initGame(void)
{
  std::ifstream		file("games/solar_fox/res/map/level_1.map");
  int			sizeLine;
  std::string		content;
  std::string		line;
  int			j;

  j = -1;
  srand(time(NULL));
  if ((_map = (arcade::GetMap *)malloc(sizeof(arcade::GetMap) + (50 * 53 * sizeof(arcade::TileType)))) == NULL)
    throw arcade::Exception("Malloc failed\n");

  _map->type = arcade::CommandType::GO_UP;
  _direction = arcade::CommandType::GO_UP;
  _map->width = 50;
  _map->height = 50;
  _score = 0;
  
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
      	{
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
    }
  else
    throw arcade::Exception("Invalid file.");
}

arcade::CommandType	LSolarFox::mainLoop(bool lPDM)
{
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
    }
  return (_map->type);
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

