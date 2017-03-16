/*
** Gui.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 11:01:41 2017 gastal_r
** Last update	Thu Mar 16 14:52:32 2017 gastal_r
*/

#include        "Gui.hpp"

Gui::Gui()
{
  _status = CONTINUE;
}

Gui::~Gui()
{}

void            Gui::setGraph(arcade::IGraph *graph)
{
    _graph = graph;
}

void            Gui::startGui()
{
  _graph->aPutText(1080 / 2 - 150, 720 / 2 - 40, "core/res/fonts/press_start.ttf",
                  30, arcade::RED, "ENTER NAME");
}

void            Gui::affDispLibs(std::vector<std::string> libs, std::string current)
{
  size_t i = 0;

  for (std::vector<std::string>::iterator it = libs.begin(); it != libs.end(); ++it)
  {
    if (*it == current)
      _graph->aPutText(20, 100 + 40 * i, "core/res/fonts/freaky_font.ttf",
                    30, arcade::YELLOW, "->");
    *it = (*it).substr(0, (*it).find_last_of("."));
    *it = (*it).erase(0, (*it).find_last_of("_") + 1);
    _graph->aPutText(50, 100 + 40 * i, "core/res/fonts/freaky_font.ttf",
                    30, arcade::GREEN, (*it));
    i++;
  }
}

void            Gui::affDispGames(std::vector<std::string> games, std::string current)
{
  size_t i = 0;

  for (std::vector<std::string>::iterator it = games.begin(); it != games.end(); ++it)
  {
    if (*it == current)
      _graph->aPutText(950, 100 + 40 * i, "core/res/fonts/freaky_font.ttf",
                    30, arcade::YELLOW, "->");
    *it = (*it).substr(0, (*it).find_last_of("."));
    *it = (*it).erase(0, (*it).find_last_of("_") + 1);
    _graph->aPutText(970, 100 + 40 * i, "core/res/fonts/freaky_font.ttf",
                    30, arcade::CYAN, (*it));
    i++;
  }
}

Status          &Gui::getStatus()
{
  return (_status);
}
