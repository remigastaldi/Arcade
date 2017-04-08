/*
** Level.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Apr 08 19:19:26 2017 gastal_r
** Last update	Sun Apr 09 00:42:42 2017 gastal_r
*/

#include      "Level.hpp"

bool          Level::checkFileName(const std::string &str) const
{
  if (str.substr(0, str.find_last_of("_")) != "level")
    return (false);
  if (str.substr(str.find_last_of(".") + 1) != "map")
    return (false);
  std::string tmp = str.substr(str.find("_") + 1);
  if (tmp.substr(0, tmp.find_last_of(".")).find_first_not_of("0123456789") != std::string::npos)
    return (false);
  return (true);
}

Level::Level()
{
  DIR                      *dir;

  _currentLvl = -1;
  dir = File::Opendir(SOLAR_RES "map/");
  if (dir)
  {
    while (true)
    {
      dirent *de = File::Readdir(dir);
      if (de == NULL)
        break;
      if (de->d_type != DT_DIR && checkFileName(de->d_name))
      {
        std::ostringstream path;
        path << SOLAR_RES << "map/" << de->d_name;
        _lvlNames.push_back(path.str());
      }
    }
    File::Closedir(dir);
    std::sort(_lvlNames.begin(), _lvlNames.end());
  }
  else
    throw arcade::Exception("Map folder doesn't exist");
}

const std::string &Level::getNextLvl()
{
  _currentLvl++;
  return (_lvlNames.at(_currentLvl));
}
