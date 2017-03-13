/*
** core.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 22:59:05 2017 gastal_r
** Last update	Mon Mar 13 18:28:09 2017 gastal_r
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
    {
      std::cerr << "Cannot load library: " << dlerror() << '\n';
    }
    dlerror();
    create_lib = reinterpret_cast<arcade::IGraph* (*)()>(dlsym(handle, "createGraph"));
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
      std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
    }
    _graph = create_lib();
}

void            Core::openGame(std::string name)
{
    void    *handle;
    arcade::IGame *(*create_game)();

    handle = Core::Dlopen(name.c_str(), RTLD_LOCAL | RTLD_LAZY);
    if (!handle)
    {
      std::cerr << "Cannot load library: " << dlerror() << '\n';
    }
    dlerror();
    create_game = reinterpret_cast<arcade::IGame* (*)()>(dlsym(handle, "createGame"));
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
      std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
    }
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
