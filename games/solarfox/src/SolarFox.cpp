/*
** SolarFox.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:07:46 2017 gastal_r
** Last update	Sat Apr 08 02:18:20 2017 gastal_r
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

  if (_enemyMissile.size() > 1)
    for (std::vector<EnemyMissile>::iterator it = _enemyMissile.begin() ; it != _enemyMissile.end() - 1 ; ++it)
      it->print(_core);
  _ship.print(_core);
  for (std::vector<Missile>::iterator it = _missile.begin(); it != _missile.end(); ++it)
    it->print(_core);
  for (std::vector<EnemyShip>::iterator it = _enemyShip.begin() ; it != _enemyShip.end() ; ++it)
    it->print(_core);

  for (unsigned int i = 0 ; i < MAP_HEIGHT * MAP_WIDTH; i++)
    _core->getLib()->aTile((i % _map->width) + 1, (i / _map->height) + 1, 0, _map->tile[i], arcade::CommandType::UNDEFINED);

  _core->refreshGui();
  _core->getLib()->aRefresh();
}

void			LSolarFox::initTextures(void)
{
  _core->getLib()->aAssignTexture(arcade::TileType::EMPTY, SOLAR_RES "img/floor2.png", arcade::Color::A_WHITE);
  _core->getLib()->aAssignTexture(arcade::TileType::BLOCK, SOLAR_RES "img/wall2.png", arcade::Color::A_RED);
  _core->getLib()->aAssignTexture(arcade::TileType::SHIP, SOLAR_RES "img/ship.png", arcade::Color::A_BLACK);
  _core->getLib()->aAssignTexture(arcade::TileType::MY_SHOOT, SOLAR_RES "img/wall3.png", arcade::Color::A_MAGENTA);
  _core->getLib()->aAssignTexture(arcade::TileType::POWERUP, SOLAR_RES "img/mooncat.jpg", arcade::Color::A_MAGENTA);
  _core->getLib()->aAssignTexture(arcade::TileType::EVIL_DUDE, SOLAR_RES "img/wall.png", arcade::Color::A_BLUE);
  _core->getLib()->aAssignTexture(arcade::TileType::EVIL_SHOOT, SOLAR_RES "img/wall.png", arcade::Color::A_RED);
}

void			LSolarFox::initGame(bool lPDM)
{
  std::ifstream		file(SOLAR_RES "map/level_moul.map");
  std::string		content;
  std::string		line;
  int			sizeLine;
  int			j;

  j = -1;
  _score = 0;
  _nbpower = 0;
  _lPDM = lPDM;
  std::srand(std::time(NULL));

  _exitStatus = arcade::CommandType::UNDEFINED;
  _map = new arcade::GetMap[(MAP_HEIGHT * MAP_WIDTH * sizeof(arcade::TileType))];
  _map->type = arcade::CommandType::GO_UP;
  _map->width = MAP_WIDTH;
  _map->height = MAP_HEIGHT;
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
      _nbpower++;
	    _map->tile[++j] = arcade::TileType::POWERUP;
	    break;
	  case 'V' :
	    _map->tile[++j] = arcade::TileType::EMPTY;
	    _ship = Ship(i % _map->width, i / _map->height);
	    break;
	  case 'E':
	    _map->tile[++j] = arcade::TileType::EMPTY;
	    if ((i % _map->width == 1 && i / _map->height == 1) || (i % _map->width == 39 && i / _map->height == 39))
	      _enemyShip.push_back(EnemyShip(i % _map->width, i / _map->height, arcade::CommandType::GO_LEFT));
	    else
	      _enemyShip.push_back(EnemyShip(i % _map->width, i / _map->height, arcade::CommandType::GO_UP));
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
	  _map->tile[(_ship.getY() - 1) * MAP_WIDTH + _ship.getX()] != arcade::TileType::BLOCK)
	direction = arcade::CommandType::GO_UP;
      break;
    case (arcade::CommandType::GO_DOWN):
      if (direction != arcade::CommandType::GO_UP &&
	  _map->tile[(_ship.getY() + 1) * MAP_WIDTH + _ship.getX()] != arcade::TileType::BLOCK)
	direction = arcade::CommandType::GO_DOWN;
      break;
    case (arcade::CommandType::GO_LEFT):
      if (direction != arcade::CommandType::GO_RIGHT &&
	  _map->tile[_ship.getY() * MAP_WIDTH + _ship.getX() - 1] != arcade::TileType::BLOCK)
	direction = arcade::CommandType::GO_LEFT;
      break;
    case (arcade::CommandType::GO_RIGHT):
      if (direction != arcade::CommandType::GO_LEFT &&
	  _map->tile[_ship.getY() * MAP_WIDTH + _ship.getX() + 1] != arcade::TileType::BLOCK)
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
  for (std::vector<Missile>::iterator it = _missile.begin(); it != _missile.end(); ++it)
    it->move();
  _ship.move(_map);

  if (_missile.size() != 0)
  {
    for (std::vector<Missile>::iterator it = _missile.begin(); it != _missile.end(); ++it)
    {
      if (_map->tile[it->getY() * MAP_WIDTH + it->getX()] == arcade::TileType::POWERUP)
      {
        _map->tile[it->getY() * MAP_WIDTH + it->getX()] = arcade::TileType::EMPTY;
        _score += 10;
        _core->setScore(std::to_string(_score));
        _core->getLib()->aPlaySound(arcade::Sound::POWERUP);
        it = _missile.erase(it);
        it = it - 1;
      }
    }
  }


  int	colisionType;
  bool colision = false;
  for (std::vector<EnemyMissile>::iterator itE = _enemyMissile.begin() ; itE != _enemyMissile.end() ; ++itE)
    {
      for (std::vector<Missile>::iterator it = _missile.begin(); it != _missile.end(); ++it)
      {
        colision = itE->checkColisions(*it);
        if (colision == true)
        {
          it = _missile.erase(it);
          it = it--;
          itE = _enemyMissile.erase(itE);
          itE == itE--;
        }
      }

      colisionType = itE->move(_ship);

      if (colisionType == SHIP_DESTROYED)
      {
        _core->getLib()->aPlaySound(arcade::Sound::EXPLOSION);
        itE = _enemyMissile.erase(itE);
        itE = itE--;
        gameOver();
        return;
       }
       else if (colisionType == MISSILE_DESTROYED)
       {
         itE = _enemyMissile.erase(itE);
         itE == itE--;
       }
       for (std::vector<Missile>::iterator it = _missile.begin(); it != _missile.end(); ++it)
      {
        colision = itE->checkColisions(*it);
        if (colision == true)
        {
          it = _missile.erase(it);
          it = it--;
          itE = _enemyMissile.erase(itE);
          itE == itE--;
        }
      }
    }
  for (std::vector<EnemyShip>::iterator it = _enemyShip.begin() ; it != _enemyShip.end() ; ++it)
    it->move(_core, _enemyMissile);
}

arcade::CommandType					LSolarFox::mainLoop(void)
{
  std::chrono::high_resolution_clock::time_point	t1 = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point  m1 = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point	t2;
  arcade::CommandType					lastCommand;


  initTextures();
  _core->setScore(std::to_string(_score));
  while (_map->type != arcade::CommandType::ESCAPE && _map->type != arcade::CommandType::MENU)
    {
      t2 = std::chrono::high_resolution_clock::now();
      lastCommand = _core->getLib()->aCommand();

      if (lastCommand != arcade::CommandType::UNDEFINED)
	     _map->type = lastCommand;


  Missile missile;
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
	  break;
	case arcade::CommandType::NEXT_GAME :
	  return (arcade::CommandType::NEXT_GAME);
	case arcade::CommandType::PREV_GAME :
	  return (arcade::CommandType::PREV_GAME);
	case arcade::CommandType::SHOOT :
    if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - m1).count() >= 200)
    {
  	  _ship.shoot(missile);
      _missile.push_back(missile);
      _core->getLib()->aPlaySound(arcade::Sound::MY_SHOOT);
      m1 = std::chrono::high_resolution_clock::now();
    }
    break;
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
          move();
          if (_exitStatus == arcade::CommandType::MENU || _exitStatus == arcade::CommandType::ESCAPE)
      	    return (_exitStatus);
          printGame();
          t1 = std::chrono::high_resolution_clock::now();
        }
    }
  return (_map->type);
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

void			LSolarFox::gameOver(void)
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

void			LSolarFox::lPDM_getMap() const
{
  arcade::GetMap *map;

  map = _map;
  if (_missile.size() != 0)
  {
    map->tile[_missile.end()->getY() * MAP_WIDTH + _missile.end()->getX()] = arcade::TileType::MY_SHOOT;
  }
  std::cout.write(reinterpret_cast<char *>(map), sizeof(arcade::GetMap) + (_map->width * _map->height * sizeof(arcade::TileType)));
}

void			LSolarFox::lPDM_whereAmI()
{
  arcade::WhereAmI	*solarfox;
  int			length;

  length = 1;
  solarfox = new arcade::WhereAmI[(length * sizeof(arcade::Position))];
  solarfox->type = _map->type;
  solarfox->lenght = length;
  solarfox->position[0].x = _ship.getX();
  solarfox->position[0].y = _ship.getY();
  std::cout.write(reinterpret_cast<char *>(solarfox), sizeof(arcade::WhereAmI) + (length * sizeof(arcade::Position)));
  delete(solarfox);
}

void			LSolarFox::lPDM_start()
{
  arcade::CommandType	command;
  arcade::CommandType	direction;
  Missile missile;

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
      case (arcade::CommandType::SHOOT):
         _ship.shoot(missile);
         _missile.push_back(missile);
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
