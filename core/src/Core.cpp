/*
** core.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 22:59:05 2017 gastal_r
** Last update	Mon Mar 13 21:44:05 2017 gastal_r
*/

#include        "Core.hpp"

Core::Core(std::string lib)
{
  openLibsDir();
  openGamesDir();
  openLib(lib);
  //openGame(std::string("games/lib_arcade_snake.so"));
}

Core::~Core()
{}

void            Core::openLib(std::string name)
{
    void    *handle;
    arcade::IGraph *(*create_lib)();

    handle = Core::Dlopen(name.c_str(), RTLD_LOCAL | RTLD_LAZY);
    if (!handle)
      throw arcade::Exception("Cannot load library: ", name);
    create_lib = reinterpret_cast<arcade::IGraph* (*)()>(dlsym(handle, "createGraph"));
    if (!create_lib)
      throw arcade::Exception("Cannot load library symbol");
    _graph = create_lib();
}

void            Core::openGame(std::string name)
{
    void    *handle;
    arcade::IGame *(*create_game)();

    handle = Core::Dlopen(name.c_str(), RTLD_LOCAL | RTLD_LAZY);
    if (!handle)
    throw arcade::Exception("Cannot load game: ", name);
    create_game = reinterpret_cast<arcade::IGame* (*)()>(dlsym(handle, "createGame"));
    if (!create_game)
      throw arcade::Exception("Cannot load game symbol");
    _game = create_game();
}

void            Core::openLibsDir()
{
  File files("./lib/");
  _libs = files.getLibs();
}

void            Core::openGamesDir()
{
  File files("./games/");
  _libs = files.getLibs();
}

void            Core::switchGame(arcade::MoveType)
{}

void            Core::changeLib(arcade::MoveType)
{}

arcade::IGraph  *Core::getLib()
{
  return (_graph);
}

void            *Core::Dlopen(const char *filename, int flag)
{
  return (dlopen(filename, flag));
}

void            *Core::Dlsym(void *handle, const char *symbol)
{
  return (dlsym(handle, symbol));
}
