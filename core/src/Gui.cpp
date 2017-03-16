/*
** Gui.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 11:01:41 2017 gastal_r
** Last update	Thu Mar 16 21:57:16 2017 gastal_r
*/

#include        "Gui.hpp"

Gui::Gui()
{
}

Gui::~Gui()
{}

void            Gui::setGraph(arcade::IGraph *graph)
{
    _graph = graph;
}

void            Gui::affName()
{
  _graph->aPutText(500 - (_player.size() * 5), 650, "core/res/fonts/press_start.ttf",
                  20, arcade::MAGENTA, _player);
}

void            Gui::affGui()
{
  _graph->aPutText(430, 10, "core/res/fonts/press_start.ttf",
                  40, arcade::RED, "ARCADE");
  affDispLibs();
  affDispGames();
  affName();
  _graph->aRefresh();
}

void            Gui::affDispLibs()
{
  size_t i = 0;
  std::vector<std::string> libs(_libs);

  for (std::vector<std::string>::iterator it = libs.begin(); it != libs.end(); ++it)
  {
    if (*it == _currentGraph)
      _graph->aPutText(20, 100 + 40 * i, "core/res/fonts/freaky_font.ttf",
                    30, arcade::YELLOW, "->");
    *it = (*it).substr(0, (*it).find_last_of("."));
    *it = (*it).erase(0, (*it).find_last_of("_") + 1);
    _graph->aPutText(50, 100 + 40 * i, "core/res/fonts/freaky_font.ttf",
                    30, arcade::GREEN, (*it));
    i++;
  }
}

void            Gui::affDispGames()
{
  size_t i = 0;
  std::vector<std::string> games(_games);

  for (std::vector<std::string>::iterator it = games.begin(); it != games.end(); ++it)
  {
    if (*it == _currentGame)
      _graph->aPutText(940, 100 + 40 * i, "core/res/fonts/freaky_font.ttf",
                    30, arcade::YELLOW, "->");
    *it = (*it).substr(0, (*it).find_last_of("."));
    *it = (*it).erase(0, (*it).find_last_of("_") + 1);
    _graph->aPutText(970, 100 + 40 * i, "core/res/fonts/freaky_font.ttf",
                    30, arcade::CYAN, (*it));
    i++;
  }
}

const std::string     Gui::getName(arcade::ICore &core)
{
  std::string input;
  std::string name;

  _graph->aPutText(1080 / 2 - 150, 720 / 2 - 40, "core/res/fonts/press_start.ttf",
                30, arcade::MAGENTA, "ENTER NAME");
  core.refreshGui();
  while ((input = _graph->aChar()) != "ENTER")
  {
    if (!input.empty())
    {
      if (input == "ESCAPE")
      {
        _status = EXIT;
        return (name);
      }
      else if (input == "BACKSPACE" && !name.empty())
      {
        name.pop_back();
        _graph->aClear();
        core.refreshGui();
      }
      else if (input != "BACKSPACE" && name.size() + 1 < 10)
        name += input;
      _graph->aClear();
      _graph->aPutText(1080 / 2 - 150, 720 / 2 - 40, "core/res/fonts/press_start.ttf",
                      30, arcade::MAGENTA, "ENTER NAME");
      _graph->aPutText(500 - (name.size() * 5), 400, "core/res/fonts/freaky_font.ttf",
                    40, arcade::BLUE, name);
      core.refreshGui();
    }
  }
  return (name);
}

void                  Gui::listGame()
{
  std::vector<std::string>::iterator it;
  std::vector<std::string> game(_games);
  size_t i = 0;

  for (it = game.begin(); it != game.end(); ++it)
  {
    *it = (*it).substr(0, (*it).find_last_of("."));
    *it = (*it).erase(0, (*it).find_last_of("_") + 1);
    _graph->aPutText(400, 200 + 40 * i, "core/res/fonts/press_start.ttf",
                    30, arcade::CYAN, (*it));
    i++;
  }
}

const std::string     Gui::chooseGame(arcade::ICore &core)
{
  arcade::CommandType cmd;
  std::vector<std::string>::iterator game;

  size_t i = 0;
  _graph->aClear();
  _graph->aPutText(345, 205, "core/res/fonts/press_start.ttf",
    25, arcade::YELLOW, "->");
  listGame();
  core.refreshGui();
  while ((cmd = _graph->aCommand()) != arcade::CommandType::PLAY)
  {
    if (cmd != arcade::CommandType::UNDEFINED)
    {
      if (cmd == arcade::CommandType::ESCAPE)
      {
        _status = EXIT;
        return ("");
      }
      if (cmd == arcade::CommandType::GO_UP)
      {
        (i == 0 ? i = _games.size() - 1: i--);
        _graph->aClear();
        _graph->aPutText(345, 205 + 40 * i, "core/res/fonts/press_start.ttf",
          25, arcade::YELLOW, "->");
        listGame();
        core.refreshGui();
        while ((cmd = _graph->aCommand()) == arcade::CommandType::GO_UP);
      }
      else if (cmd == arcade::CommandType::GO_DOWN)
      {
        (i == _games.size() - 1 ? i = 0: i++);
        _graph->aClear();
        _graph->aPutText(345, 205 + 40 * i, "core/res/fonts/press_start.ttf",
          25, arcade::YELLOW, "->");
        listGame();
        core.refreshGui();
        while ((cmd = _graph->aCommand()) == arcade::CommandType::GO_DOWN);
      }
    }
  }
  _currentGame = _games[i];
  _graph->aClear();
  affGui();
  return (_games[i]);
}

const Status          &Gui::getStatus()
{
  return (_status);
}
