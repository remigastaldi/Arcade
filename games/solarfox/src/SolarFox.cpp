/*
** SolarFox.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 26 04:07:46 2017 gastal_r
** Last update	Sun Apr 09 23:11:06 2017 gastal_r
*/

#include	        "LSolarFox.hpp"

LSolarFox::LSolarFox()
{
  _status = CONTINUE;
  _keepCommand = arcade::CommandType::UNDEFINED;
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
  for (std::vector<arcade::Position>::const_iterator it = _powerUp.begin() ; it != _powerUp.end() ; ++it)
    _core->getLib()->aTile(it->x + 1, it->y + 1, 0, arcade::TileType::POWERUP, arcade::CommandType::UNDEFINED);
  for (unsigned int i = 0 ; i < MAP_HEIGHT * MAP_WIDTH; i++)
    _core->getLib()->aTile((i % _map->width) + 1, (i / _map->height) + 1, 0, _map->tile[i], arcade::CommandType::UNDEFINED);

  _core->refreshGui();
  _core->getLib()->aRefresh();
}

void			LSolarFox::initTextures(void)
{
  _core->getLib()->aAssignTexture(arcade::TileType::EMPTY, SOLAR_RES "img/green_darker2.png", arcade::Color::A_WHITE);
  _core->getLib()->aAssignTexture(arcade::TileType::BLOCK, SOLAR_RES "img/black.png", arcade::Color::A_BLACK);
  _core->getLib()->aAssignTexture(arcade::TileType::SHIP, SOLAR_RES "img/blue_neon2.png", arcade::Color::A_BLUE);
  _core->getLib()->aAssignTexture(arcade::TileType::MY_SHOOT, SOLAR_RES "img/blue_neon2.png", arcade::Color::A_BLUE);
  _core->getLib()->aAssignTexture(arcade::TileType::POWERUP, SOLAR_RES "img/yellow_neon.png", arcade::Color::A_YELLOW);
  _core->getLib()->aAssignTexture(arcade::TileType::EVIL_DUDE, SOLAR_RES "img/red_neon.png", arcade::Color::A_RED);
  _core->getLib()->aAssignTexture(arcade::TileType::EVIL_SHOOT, SOLAR_RES "img/red_neon2.png", arcade::Color::A_RED);
  _core->getLib()->aAssignTexture(arcade::TileType::OBSTACLE, SOLAR_RES "img/red.png", arcade::Color::A_RED);
  _core->getLib()->aAssignTexture(arcade::TileType::OTHER, SOLAR_RES "img/black.png", arcade::Color::A_BLACK);
}

void			LSolarFox::parseMap(std::string const &content)
{
  arcade::Position	powerUp;
  int			j;

  j = -1;

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
	powerUp.x = i % _map->width;
	powerUp.y = i / _map->width;
	_powerUp.push_back(powerUp);
	_map->tile[++j] = arcade::TileType::EMPTY;
	break;
      case 'V' :
	_map->tile[++j] = arcade::TileType::EMPTY;
	_ship = Ship(i % _map->width, i / _map->height);
	break;
      case 'E':
	_map->tile[++j] = arcade::TileType::OTHER;
	if ((i % _map->width == 1 && i / _map->height == 1) || (i % _map->width == 39 && i / _map->height == 39))
	  _enemyShip.push_back(EnemyShip(i % _map->width, i / _map->height, arcade::CommandType::GO_LEFT));
	else
	  _enemyShip.push_back(EnemyShip(i % _map->width, i / _map->height, arcade::CommandType::GO_UP));
	break;
      case 'X' :
	_map->tile[++j] = arcade::TileType::OBSTACLE;
	break;
      case 'O' :
	_map->tile[++j] = arcade::TileType::OTHER;
	break;
      default :
	throw arcade::Exception("Invalid map.");
	break;
      }
}

arcade::CommandType  	LSolarFox::initGame(bool lPDM)
{
  int			sizeLine;
  std::string		content;
  std::string		line;

  _score = 0;
  _lPDM = lPDM;
  _exitStatus = arcade::CommandType::UNDEFINED;
  std::srand(std::time(NULL));

  _map = new arcade::GetMap[(MAP_HEIGHT * MAP_WIDTH * sizeof(arcade::TileType))];
  _map->width = MAP_WIDTH;
  _map->height = MAP_HEIGHT;

  if (_lPDM == false)
    initTextures();

  if (_level.getNbLvl() == 0)
    throw arcade::Exception("No map found");
  while (_status != EXIT)
  {
    _nbpower = 0;
    _map->type = arcade::CommandType::GO_UP;
    std::ifstream		file(lPDM ? SOLAR_RES "map/level_moul.map" : _level.getNextLvl());
    if (file)
      {
        content.clear();
        std::getline(file, line);
        sizeLine = line.length();
        content += line;

        while (getline(file, line))
        	{
        	  if ((unsigned int)sizeLine != line.length())
        	    throw arcade::Exception("Invalid map.");
        	  content += line;
        	}
        parseMap(content);
      }
    else
      throw arcade::Exception("Invalid file.");
    file.close();
    arcade::CommandType val;
    if (_lPDM == false)
       val = mainLoop();
    if (val != arcade::CommandType::UNDEFINED)
      return (val);

    if (_level.getCurrentLvl() == _level.getNbLvl() - 1)
      {
        if (_lPDM == false)
          gameWin();
        return(_exitStatus);
      }
      _missile.clear();
      _enemyMissile.clear();
      _powerUp.clear();
      _enemyShip.clear();
  }
  return (arcade::CommandType::MENU);
}

void			LSolarFox::changeAction()
{
  arcade::CommandType direction;

  direction = _ship.getDirection();
  switch (_map->type)
    {
    case (arcade::CommandType::GO_UP):
      _keepCommand = arcade::CommandType::GO_UP;
      break;
    case (arcade::CommandType::GO_DOWN):
      _keepCommand = arcade::CommandType::GO_DOWN;
      break;
    case (arcade::CommandType::GO_LEFT):
      _keepCommand = arcade::CommandType::GO_LEFT;
      break;
    case (arcade::CommandType::GO_RIGHT):
      _keepCommand = arcade::CommandType::GO_RIGHT;
      break;
    default:
      break;
    }
    switch (_keepCommand)
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
}

void    LSolarFox::move()
{
  for (std::vector<Missile>::iterator it = _missile.begin(); it != _missile.end(); ++it)
    it->move(_map);
  if (_ship.move(_map) == Object::Destroyed::SHIP && _lPDM == false)
    gameOver();

  if (_missile.size() != 0)
    {
      for (std::vector<Missile>::iterator it = _missile.begin(); it != _missile.end(); ++it)
	{
	  for (std::vector<arcade::Position>::iterator itpow = _powerUp.begin() ; itpow != _powerUp.end() ; ++itpow)
	    {
	      if (itpow->x == it->getX() && itpow->y == it->getY())
		{
		  _score += 10;
      _nbpower--;
      if (_lPDM == false)
      {
        _core->setScore(std::to_string(_score));
        _core->getLib()->aPlaySound(arcade::Sound::POWERUP);
      }
		  it = _missile.erase(it);
		  it = it - 1;
		  itpow = _powerUp.erase(itpow);
		  itpow = itpow - 1;
		}
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
	      it = it - 1;
	      itE = _enemyMissile.erase(itE);
	      itE == itE - 1;
	    }
	}

      colisionType = itE->move(_ship);
      if (colisionType == Object::Destroyed::SHIP)
	{
    if (_lPDM == false)
	   _core->getLib()->aPlaySound(arcade::Sound::EXPLOSION);
	  itE = _enemyMissile.erase(itE);
	  itE = itE - 1;
    if (_lPDM == false)
	   gameOver();
	  return;
	}
      else if (colisionType == Object::Destroyed::MISSILE)
	{
	  itE = _enemyMissile.erase(itE);
	  itE == itE - 1;
	}

      for (std::vector<Missile>::iterator it = _missile.begin(); it != _missile.end(); ++it)
	{
	  colision = itE->checkColisions(*it);
	  if (colision == true)
	    {
	      it = _missile.erase(it);
	      it = it - 1;
	      itE = _enemyMissile.erase(itE);
	      itE == itE - 1;
	    }
	}
    }
  for (std::vector<EnemyShip>::iterator it = _enemyShip.begin() ; it != _enemyShip.end() ; ++it)
    it->move(_core, _enemyMissile, _level, _lPDM);
  _map->type = arcade::CommandType::UNDEFINED;
}

arcade::CommandType					LSolarFox::mainLoop(void)
{
  std::chrono::high_resolution_clock::time_point	t1 = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point	m1 = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point	gf = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point	t2;
  arcade::CommandType					lastCommand;
  Missile						missile;

  _core->setScore(std::to_string(_score));
  while (_map->type != arcade::CommandType::ESCAPE && _map->type != arcade::CommandType::MENU && _nbpower > 0)
    {
      t2 = std::chrono::high_resolution_clock::now();
      lastCommand = _core->getLib()->aCommand();

      if (_map->type == arcade::CommandType::UNDEFINED)
	_map->type = lastCommand;

  if (lastCommand == arcade::CommandType::UNDEFINED)
  {
      if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - gf).count() >= 800)
      {
        _ship.setSpeed(9);
        gf = std::chrono::high_resolution_clock::now();
      }
    }

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
	case arcade::CommandType::GO_FORWARD :
	  _ship.setSpeed(10);
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
          {
            _core->getLib()->aClearAnimBuffer();
      	    return (_exitStatus);
          }
          printGame();
          t1 = std::chrono::high_resolution_clock::now();
        }
    }
  _core->getLib()->aClearAnimBuffer();
  return (_nbpower == 0 ? arcade::CommandType::UNDEFINED : _map->type);
}

arcade::CommandType	LSolarFox::play(arcade::ICore& core)
{
  _core = &core;
  return (initGame(false));
}

void			LSolarFox::gameWin(void)
{
  _core->getLib()->aClearAnimBuffer();
  _core->setScore(std::to_string(_score));
  _core->gameWin();
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
    map->tile[_missile.at(_missile.size() - 1).getY() * MAP_WIDTH + _missile.at(_missile.size() - 1).getX()] = arcade::TileType::MY_SHOOT;
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
