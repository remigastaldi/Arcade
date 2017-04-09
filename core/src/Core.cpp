/*
** core.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 22:59:05 2017 gastal_r
** Last update	Sun Apr 09 15:42:49 2017 gastal_r
*/

#include        "Core.hpp"

Core::Core(const std::string &lib)
{
  _graph = 0;
  _game = 0;
  setStatus(CONTINUE);
  openLibsDir();
  openGamesDir();
  openLib(lib);
}

Core::~Core()
{
  _graph->aClose();
  _graph ? delete(_graph) : (void)0;
  _game ? delete(_game) : (void)0;
}

void            Core::openLib(const std::string &name)
{
    arcade::IGraph *(*create_lib)();

    _graphHandle = Dlopen(name.c_str(), RTLD_LOCAL | RTLD_LAZY);
    if (!_graphHandle)
      throw arcade::Exception("Cannot open", name);
    create_lib = reinterpret_cast<arcade::IGraph* (*)()>(Dlsym(_graphHandle, "createGraph"));
    if (!create_lib)
      throw arcade::Exception("Cannot load library symbol");
    _graph = create_lib();
    _currentGraph = name;
}

void            Core::openGame(const std::string &name)
{
    arcade::IGame *(*create_game)();

    _gameHandle = Dlopen(name.c_str(), RTLD_LOCAL | RTLD_LAZY);
    if (!_gameHandle)
      throw arcade::Exception("Cannot load", name);
    create_game = reinterpret_cast<arcade::IGame* (*)()>(Dlsym(_gameHandle, "createGame"));
    if (!create_game)
      throw arcade::Exception("Cannot load game symbol");
    _game = create_game();
    _currentGame = name;
}

void            Core::openLibsDir()
{
  File files(GRAPH_DIR);
  _libs.clear();
  _libs = files.getLibs();
}

void            Core::openGamesDir()
{
  File files(GAME_DIR);
  _games.clear();
  _games = files.getLibs();
}

void            Core::setGuiData()
{
  guiSetGraph(_graph);
  guiSetLibs(_libs);
  guiSetCurrentGraph(_currentGraph);
  guiSetGames(_games);
  guiSetCurrentGame(_currentGame);
  guiSetPlayer(_player);
}

void          Core::chooseGameMenu()
{
  _currentGame = chooseGame(*this);
  if (getStatus() == EXIT)
    return;
  openGame(_currentGame);
}

void            Core::startCore()
{
  _graph->aInit(this, WIDTH, HEIGHT);
  _graph->aPlayMusic(CORE_RES "sounds/menu_music.wav");
  setGuiData();
  _save.loadPlayerSave();
  _player = getName(*this);
  if (getStatus() == EXIT)
    return;
  guiSetPlayer(_player);
  _save.saveSetPlayer(_player);
  chooseGameMenu();
  if (getStatus() == EXIT)
    return;
  _save.checkExistingUser();
  coreLoop();
}

void            Core::coreLoop()
{
  arcade::CommandType gameReturn = arcade::CommandType::UNDEFINED;

  while (getStatus() == CONTINUE)
  {
    _graph->aPlaySound(arcade::Sound::NEW_GAME);
    gameReturn = _game->play(*this);
    switch (gameReturn)
    {
      case arcade::CommandType::ESCAPE :
        return;
      case arcade::CommandType::NEXT_GAME :
        switchGame(arcade::CommandType::NEXT_GAME);
        break;
      case arcade::CommandType::PREV_GAME :
        switchGame(arcade::CommandType::PREV_GAME);
        break;
      case arcade::CommandType::RESTART :
        delete(_game);
        _game = 0;
	Dlclose(_gameHandle);
        openGamesDir();
        openLibsDir();
        openGame(_currentGame);
        break;
      case arcade::CommandType::MENU :
        _graph->aPlayMusic(CORE_RES "sounds/menu_music.wav");
        delete(_game);
        _game = 0;
        Dlclose(_gameHandle);
        openGamesDir();
        openLibsDir();
        _currentGame.clear();
        setGuiData();
        guiClearBestScores();
        chooseGameMenu();
        break;
      default :
        break;
    }
    if (gameReturn == arcade::CommandType::ESCAPE)
      return;
    if (_graph->aCommand() == arcade::CommandType::ESCAPE)
      setStatus(Status::EXIT);
  }
}

void            Core::switchGame(const arcade::CommandType m)
{
  std::string   name;

  openGamesDir();
  if (_games.size() == 1)
    return;
  if (m == arcade::CommandType::NEXT_GAME)
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
  delete(_game);
  _game = 0;
  Dlclose(_gameHandle);
  _graph->aClearAnimBuffer();
  openGame(name);
  guiSetPlayerBestScore(_save.getSavedScore(_currentGame));
  guiSetBestScores(_save.getBestPlayersScores(_currentGame));
  setGuiData();
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
      name = *(_libs.end() - 1);
    else
      name = _libs[pos - 1];
  }
  _graph->aClose();
  delete(_graph);
  _graph = 0;
  Dlclose(_graphHandle);
  openLib(name);
  _graph->aInit(this, 1920, 1080);
  setGuiData();
}

void             Core::saveScore(size_t score)
{
  if (std::stoul(_save.getSavedScore(_currentGame)) < score
      || std::stoul(_save.getSavedScore(_currentGame)) == 0)
    _save.saveScore(_currentGame, std::to_string(score));
}

std::vector<std::string> Core::getSounds()
{
  std::vector<std::string> sounds;

  sounds.push_back(CORE_RES "sounds/start_game.wav");
  sounds.push_back(CORE_RES "sounds/game_over.wav");
  sounds.push_back(CORE_RES "sounds/my_shoot.wav");
  sounds.push_back(CORE_RES "sounds/enemy_shoot.wav");
  sounds.push_back(CORE_RES "sounds/coin.wav");
  sounds.push_back(CORE_RES "sounds/explosion.wav");
  sounds.push_back(CORE_RES "sounds/select.wav");
  return (sounds);
}

arcade::IGraph  *Core::getLib() const
{
  return (_graph);
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
