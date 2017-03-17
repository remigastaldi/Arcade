/*
** Save.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Fri Mar 17 00:03:17 2017 gastal_r
** Last update	Fri Mar 17 02:26:34 2017 gastal_r
*/

#include        "Save.hpp"

Save::Save()
{}

Save::~Save()
{
  _file.close();
}

void            Save::loadPlayerSave()
{
  std::string   line;
  std::string   token;
  size_t        pos;
  std::vector<Save::Data>::iterator it = _saves.begin();

	_file.open(SAVE_PATH);
  while(!_file.eof() && line != _player)
    getline(_file, line);
  if (line == _player)
  {
    getline(_file, line);
    while ((pos = line.find(":")) != std::string::npos)
    {
      Save::Data data;
      token = line.substr(0, pos);
      data.setGame(token);
      line.erase(0, pos + 1);
      pos = line.find(":");
      token = line.substr(0, pos);
      data.setValue(token);
      _saves.push_back(data);
      line.erase(0, pos + 1);
      ++it;
   }
  }
}

const std::string     Save::getSavedScore(std::string name) const
{
  name = name.substr(0, name.find_last_of("."));
  name = name.erase(0, name.find_last_of("_") + 1);

  for (std::vector<Save::Data>::const_iterator it = _saves.begin(); it != _saves.end(); ++it)
  {
    if ((*it).getGame() == name)
      return ((*it).getValue());
  }
  return ("0");
}
