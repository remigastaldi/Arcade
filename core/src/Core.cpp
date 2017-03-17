/*
** core.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 22:59:05 2017 gastal_r
** Last update	Fri Mar 17 03:33:28 2017 gastal_r
*/

#include        "Core.hpp"

Core::Core(const std::string &lib)
{
  setStatus(CONTINUE);
  openLibsDir();
  openGamesDir();
  openLib(lib);
  //openGame(std::string("games/lib_arcade_snake.so"));
/*  _currentGame = "games/lib_arcade_snake.so";
  _currentGraph = "lib/lib_arcade_ncurses.so";
  openGame(std::string("games/lib_arcade_snake.so"));
  switchGame(arcade::NEXT);
  switchLib(arcade::NEXT);
  switchGame(arcade::PREV);
  switchLib(arcade::PREV); */
}

Core::~Core()
{
  /* delete(_graph);
  delete(_game); */
}

void            Core::openLib(const std::string &name)
{
    arcade::IGraph *(*create_lib)();

    _graphHandle = Core::Dlopen(name.c_str(), RTLD_LOCAL | RTLD_LAZY);
    if (!_graphHandle) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
    }
    if (!_graphHandle)
      throw arcade::Exception(name, " doesn't exist or isn't in lib folder");
    create_lib = reinterpret_cast<arcade::IGraph* (*)()>(dlsym(_graphHandle, "createGraph"));
    if (!create_lib)
      throw arcade::Exception("Cannot load library symbol");
    _graph = create_lib();
    _currentGraph = name;
}

void            Core::openGame(const std::string &name)
{
    arcade::IGame *(*create_game)();

    _gameHandle = Core::Dlopen(name.c_str(), RTLD_LOCAL | RTLD_LAZY);
    if (!_gameHandle)
      throw arcade::Exception(name, " doesn't exist or isn't in lib folder");
    create_game = reinterpret_cast<arcade::IGame* (*)()>(dlsym(_gameHandle, "createGame"));
    if (!create_game)
      throw arcade::Exception("Cannot load game symbol");
    _game = create_game();
    _currentGame = name;
}

void            Core::openLibsDir()
{
  File files(GRAPH_DIR);
  _libs = files.getLibs();
}

void            Core::openGamesDir()
{
  File files(GAME_DIR);
  _games = files.getLibs();
}

void            Core::setGuiData()
{
  guiSetLibs(_libs);
  guiSetCurrentGraph(_currentGraph);
  guiSetGames(_games);
  guiSetCurrentGame(_currentGame);
  guiSetPlayer(_player);
}

void            Core::startCore()
{
  _graph->aInit(1080, 720);
/*setGraph(_graph);
  setGuiData();
  refreshGui(); */
/*  _player = getName(*this);
  guiSetPlayer(_player);
  _save.saveSetPlayer(_player);
  _save.loadPlayerSave();
  _graph->aClear();
  refreshGui(); */
//  chooseGame(*this);
  //openGame(chooseGame(*this));
  while (getStatus() == CONTINUE)
  {
  if (_graph->aCommand() == arcade::CommandType::ESCAPE)
    setStatus(Status::EXIT);
  }
}

void            Core::switchGame(const arcade::MoveType m)
void            Core::switchGame(const arcade::CommandType m)
{
  std::string   name;

  openGamesDir();
  if (_games.size() == 1)
    return;
  if (m == arcade::CommandType::NEXT_LIB)
  {
    size_t pos = find(_games.begin(), _games.end(), _currentGame) - _games.begin();
    if (pos + 1 == _games.size())
      name = *_games.begin();
    else
      name = _games[pos + 1];
  }
  else
  {
    size_t pos = find(_games.begin(), _games.end(), _currentGame) - _games.begin();
    if (pos  == 0)
      name = *(_games.end() - 1);
    else
      name = _games[pos - 1];
  }
  _game->close();
  delete(_game);
  Dlclose(_gameHandle);
  openGame(name);
}

void            Core::switchLib(const arcade::CommandType m)
{
  std::string   name;

  openLibsDir();
  if (_libs.size() == 1)
    return;
  if (m == arcade::CommandType::NEXT_LIB)
  {
    size_t pos = find(_libs.begin(), _libs.end(), _currentGraph) - _libs.begin();
    if (pos + 1 == _libs.size())
      name = *_libs.begin();
    else
      name = _libs[pos + 1];
  }
  else
  {
    size_t pos = find(_libs.begin(), _libs.end(), _currentGraph) - _libs.begin();
    if (pos  == 0)
      name = *_libs.end();
    else
      name = _libs[pos - 1];
  }
  _graph->aClose();
  delete(_graph);
  Dlclose(_graphHandle);
  openLib(name);
  _graph->aInit(1080, 720);
}

arcade::IGraph  *Core::getLib() const
{
  return (_graph);
}

Save            &Core::getSave()
{
  return (_save);
}

void            *Core::Dlsym(void *handle, const char *symbol)
{
  return (dlsym(handle, symbol));
}

void            *Core::Dlopen(const char *filename, int flag)
{
  return (dlopen(filename, flag));
}

int             Core::Dlclose(void *handle)
{
  return (dlclose(handle));
}
