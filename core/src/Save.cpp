/*
** Save.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Fri Mar 17 00:03:17 2017 gastal_r
** Last update	Sun Apr 09 22:53:39 2017 gastal_r
*/

#include        "Save.hpp"

void            Save::loadPlayerSave()
{
  std::string   line;
  std::string   token;
  size_t        pos;
  Save::Data    data;
  std::fstream  file;

	file.open(SAVE_PATH, std::fstream::in);
  if (!file.is_open())
    return;
  while(!file.eof())
  {
    Save::PlayerSave playerSave;
    getline(file, line);
    if (line.empty() || line == "\n")
      continue;
    playerSave.setPlayer(line);
    getline(file, line);
    while ((pos = line.find(":")) != std::string::npos)
    {
      token = line.substr(0, pos);
      data.setGame(token);
      line.erase(0, pos + 1);
      pos = line.find(":");
      token = line.substr(0, pos);
      data.setValue(token);
      playerSave.addSave(data);
      line.erase(0, pos + 1);
   }
   _playerSave.push_back(playerSave);
  }
  file.close();
}

void                  Save::checkExistingUser()
{
  std::vector<Save::PlayerSave>::const_iterator it = _playerSave.begin();

  while (it != _playerSave.end() && (*it).getPlayer() != _player)
    ++it;
  if (it == _playerSave.end())
  {
    Save::PlayerSave newPlayer;

    newPlayer.setPlayer(_player);
    _playerSave.push_back(newPlayer);
  }
}

const std::string     Save::getSavedScore(std::string game) const
{
  game = game.substr(0, game.find_last_of("."));
  game.erase(0, game.find_last_of("_") + 1);

  for (std::vector<Save::PlayerSave>::const_iterator it = _playerSave.begin(); it != _playerSave.end(); ++it)
  {
    if ((*it).getPlayer() == _player)
      return ((*it).getValue(game));
  }
  return ("0");
}

bool        sortScores(std::string a, std::string b)
{
  a = a.erase(0, a.find_last_of(":") + 2);
  b = b.erase(0, b.find_last_of(":") + 2);
  return (std::stoi(a) > std::stoi(b));
}

const std::vector<std::string>   Save::getBestPlayersScores(std::string game)
{
  std::vector<std::string> scores;

game = game.substr(0, game.find_last_of("."));
game.erase(0, game.find_last_of("_") + 1);
for (std::vector<Save::PlayerSave>::const_iterator it = _playerSave.begin(); it != _playerSave.end(); ++it)
  {
    std::string player = (*it).getPlayer();
    player += ": ";
    player += (*it).getValue(game);
    scores.push_back(player);
  }
  std::sort(scores.begin(), scores.end(), sortScores);
  scores.resize(5);
  return (scores);
}

void                  Save::saveScore(std::string currentGame, const std::string &score)
{
  currentGame = currentGame.substr(0, currentGame.find_last_of("."));
  currentGame.erase(0, currentGame.find_last_of("_") + 1);

  _file.open(SAVE_PATH, std::fstream::out | std::fstream::trunc);
  for (std::vector<Save::PlayerSave>::iterator it = _playerSave.begin(); it != _playerSave.end(); ++it)
  {
    if ((*it).getPlayer() == _player)
      (*it).addValue(currentGame, score);
    _file << (*it).getPlayer() << std::endl;
    for (std::vector<Save::Data>::iterator it2 = (*it).getSave().begin(); it2 != (*it).getSave().end(); ++it2)
    {
      _file << (*it2).getGame() << ":" << (*it2).getValue() << ":";
    }
    if (it + 1 != _playerSave.end())
      _file << std::endl;
  }
  _file.close();
}

const std::string   Save::PlayerSave::getValue(const std::string &game) const
{
  for (std::vector<Save::Data>::const_iterator it = _data.begin(); it != _data.end(); ++it)
  {
    if ((*it).getGame() == game)
      return ((*it).getValue());
  }
  return ("0");
}

void               Save::PlayerSave::addValue(const std::string &game, const std::string &score)
{
  for (std::vector<Save::Data>::iterator it = _data.begin(); it != _data.end(); ++it)
  {
    if ((*it).getGame() == game)
    {
      (*it).setValue(score);
      return;
    }
  }
  Save::Data data;
  data.setGame(game);
  data.setValue(score);
  _data.push_back(data);
}
