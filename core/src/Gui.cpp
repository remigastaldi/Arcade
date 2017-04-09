/*
** Gui.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 11:01:41 2017 gastal_r
** Last update	Sun Apr 09 15:05:27 2017 gastal_r
*/

#include        "Gui.hpp"
#include        "IGraph.hh"

Gui::Gui()
{
  _graph = 0;
  _status = CONTINUE;
}

Gui::~Gui()
{}

void            Gui::affName()
{
  _graph->aPutText(pos_x(2.4) - _player.length() / 2, pos_y(1.05), arcade::Font::PRESS_START,
                   WIDTH / 90, arcade::A_MAGENTA, _player);
  if (!_bestPlayerScore.empty())
  {
     _graph->aPutText(pos_x(1.9), pos_y(1.05) , arcade::Font::PRESS_START,
                      WIDTH / 100, arcade::A_WHITE, "Best:");
     _graph->aPutText(pos_x(1.7), pos_y(1.05) , arcade::Font::PRESS_START,
                      WIDTH / 100, arcade::A_WHITE, _bestPlayerScore);
  }
}

void            Gui::affScore()
{
  _graph->aPutText(pos_x(1.15) , pos_y(2.5), arcade::Font::PRESS_START,
                   WIDTH / 30, arcade::A_YELLOW, _score);
}

void            Gui::affGui()
{
  if (_currentGame.empty())
    _graph->aPutText(pos_x(2.4), pos_y(80), arcade::Font::PRESS_START,
                    WIDTH / 40, arcade::A_RED, "ARCADE");
  affDispLibs();
  affDispGames();
  affName();
  affScore();
  affPlayersScores();
}

void            Gui::affDispLibs()
{
  size_t i = 0;
  std::vector<std::string> libs(_libs);

  for (std::vector<std::string>::iterator it = libs.begin(); it != libs.end(); ++it)
  {
    if (*it == _currentGraph)
      _graph->aPutText(pos_x(24), pos_y(10) + pos_y(30) * i, arcade::Font::FREAKY,
                       WIDTH / 60, arcade::A_YELLOW, "->");
    *it = (*it).substr(0, (*it).find_last_of("."));
    *it = (*it).erase(0, (*it).find_last_of("_") + 1);
    _graph->aPutText(pos_x(16), pos_y(10) + pos_y(30)  * i, arcade::Font::FREAKY,
                     WIDTH / 60, arcade::A_GREEN, (*it));
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
      _graph->aPutText(pos_x(1.2), pos_y(10) + pos_y(30) * i, arcade::Font::FREAKY,
                       WIDTH / 60, arcade::A_YELLOW, "->");
    *it = (*it).substr(0, (*it).find_last_of("."));
    *it = (*it).erase(0, (*it).find_last_of("_") + 1);
    _graph->aPutText(pos_x(1.16), pos_y(10) + pos_y(30) * i, arcade::Font::FREAKY,
                     WIDTH / 60, arcade::A_CYAN, (*it));
    i++;
  }
}

const std::string     Gui::getName(arcade::ICore &core)
{
  std::string input;
  std::string name;

  while ((input = _graph->aChar()) != "ENTER" || name.empty())
  {
    _graph->aClear();
    _graph->aPutText(pos_x(2) - 3 * BLOCK_X, pos_y(4), arcade::Font::PRESS_START,
                     WIDTH / 60, arcade::A_MAGENTA, "ENTER NAME");
    if (!input.empty())
    {
      core.getLib()->aPlaySound(arcade::Sound::OTHER);
      if (input == "ESCAPE")
      {
        _status = EXIT;
        return (name);
      }
      else if (input == "BACKSPACE" && !name.empty())
        name.pop_back();
      else if (input != "BACKSPACE" && input != "ENTER" && name.size() + 1 < 10)
        name += input;
    }
    _graph->aPutText(pos_x(2.15) - name.length(), pos_y(3), arcade::Font::FREAKY,
                    WIDTH / 40, arcade::A_BLUE, name);
    core.refreshGui();
    _graph->aRefresh();
  }
  return (name);
}

void                  Gui::listGame(arcade::ICore &core, size_t selected)
{
  std::vector<std::string>::iterator it;
  std::vector<std::string> game(_games);
  size_t i = 0;

  _graph->aClear();
  _graph->aPutText(pos_x(3), pos_y(3.3555) + pos_y(20) * selected, arcade::Font::PRESS_START,
                   WIDTH / 70, arcade::A_YELLOW, "->");
  for (it = game.begin(); it != game.end(); ++it)
  {
    *it = (*it).substr(0, (*it).find_last_of("."));
    *it = (*it).erase(0, (*it).find_last_of("_") + 1);
    _graph->aPutText(pos_x(2.7), pos_y(3.5) + pos_y(20) * i, arcade::Font::PRESS_START,
                     WIDTH / 70, arcade::A_CYAN, (*it));
    i++;
  }
  _graph->aPutText(pos_x(1.9), pos_y(1.05) , arcade::Font::PRESS_START,
                   WIDTH / 100, arcade::A_WHITE, "Best: ");
  _graph->aPutText(pos_x(1.7), pos_y(1.05) , arcade::Font::PRESS_START,
                   WIDTH / 100, arcade::A_WHITE, core.getSave().getSavedScore(_games[selected]));

  affPlayersScores(core, _games[selected]);
  core.refreshGui();
  _graph->aRefresh();
}

const std::string     Gui::chooseGame(arcade::ICore &core)
{
  arcade::CommandType cmd;

  size_t i = 0;
  listGame(core, i);
  while ((cmd = _graph->aCommand()) != arcade::CommandType::PLAY)
  {
    if (cmd != arcade::CommandType::UNDEFINED)
    {
      core.getLib()->aPlaySound(arcade::Sound::OTHER);
      if (cmd == arcade::CommandType::ESCAPE)
      {
        _status = EXIT;
        return ("");
      }
      else if (cmd == arcade::CommandType::NEXT_LIB)
        {
          core.switchLib(arcade::CommandType::NEXT_LIB);
          _graph->aPlayMusic(CORE_RES "sounds/menu_music.wav");
        }
      else if (cmd == arcade::CommandType::PREV_LIB)
      {
        core.switchLib(arcade::CommandType::PREV_LIB);
        _graph->aPlayMusic(CORE_RES "sounds/menu_music.wav");
      }
      if (cmd == arcade::CommandType::GO_UP)
        (i == 0 ? i = _games.size() - 1: i--);
      else if (cmd == arcade::CommandType::GO_DOWN)
        (i == _games.size() - 1 ? i = 0: i++);
      listGame(core, i);
      while ((cmd = _graph->aCommand()) == arcade::CommandType::GO_UP);
      while ((cmd = _graph->aCommand()) == arcade::CommandType::GO_DOWN);
    }
  }
  _currentGame = _games[i];
  _bestPlayerScore = core.getSave().getSavedScore(_games[i]);
  _bestPlayersScores = core.getSave().getBestPlayersScores(_games[i]);
  return (_games[i]);
}

void                  Gui::affPlayersScores(arcade::ICore &core, std::string game)
{
  game = game .substr(0, game .find_last_of("."));
  game = game .erase(0, game .find_last_of("_") + 1);
  std::vector<std::string> scores = core.getSave().getBestPlayersScores(game);

  size_t i = 0;
  for (std::vector<std::string>::const_iterator it = scores.begin(); it != scores.end(); ++it)
  {
    _graph->aPutText(pos_x(16), pos_y(2) + pos_y(30)  * i, arcade::Font::FREAKY,
                     WIDTH / 70, arcade::A_YELLOW, (*it));
    i++;
  }
}

void                  Gui::affPlayersScores()
{
  size_t i = 0;

  for (std::vector<std::string>::const_iterator it = _bestPlayersScores.begin();
   it != _bestPlayersScores.end(); ++it)
  {
    _graph->aPutText(pos_x(16), pos_y(2) + pos_y(30)  * i, arcade::Font::FREAKY,
                     WIDTH / 70, arcade::A_YELLOW, (*it));
    i++;
  }
}

Status                Gui::getStatus()
{
  return (_status);
}

void                  Gui::guiClearBestScores()
{
  _bestPlayersScores.clear();
  _bestPlayerScore.clear();
}

void                  Gui::guiGameWin()
{
  _graph->aPlaySound(arcade::Sound::GAME_OVER);
  _graph->aClear();
  _graph->aPutText(pos_x(2.7), pos_y(2.25), arcade::Font::PRESS_START, WIDTH / 40, arcade::Color::A_RED, "GG YOU WIN!");
  _graph->aPutText(pos_x(2.8), pos_y(1.8), arcade::Font::PRESS_START, WIDTH / 100, arcade::Color::A_WHITE, "PRESS ENTER TO PLAY AGAIN.");
  _graph->aPutText(pos_x(2.1) - _score.length() * BLOCK_X, pos_y(6), arcade::Font::PRESS_START,
                            WIDTH / 15, arcade::Color::A_YELLOW, _score);
  _graph->aRefresh();
}

void                  Gui::guiGameOver()
{
  _graph->aPlaySound(arcade::Sound::GAME_OVER);
  _graph->aClear();
  _graph->aPutText(pos_x(2.7), pos_y(2.25), arcade::Font::PRESS_START, WIDTH / 40, arcade::Color::A_RED, "GAME OVER");
  _graph->aPutText(pos_x(2.8), pos_y(1.8), arcade::Font::PRESS_START, WIDTH / 100, arcade::Color::A_WHITE, "PRESS ENTER TO PLAY AGAIN.");
  _graph->aPutText(pos_x(2.1) - _score.length() * BLOCK_X, pos_y(6), arcade::Font::PRESS_START,
                            WIDTH / 15, arcade::Color::A_YELLOW, _score);
  _graph->aRefresh();
}
