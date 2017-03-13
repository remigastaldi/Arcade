/*
** File.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Mon Mar 13 16:22:53 2017 gastal_r
** Last update	Mon Mar 13 21:42:49 2017 gastal_r
*/

#include                   "File.hpp"

File::File (const std::string path)
{
  _path = path;
}

bool                      File::checkExtension(std::string str)
{
  if (str.substr(str.find_last_of(".") + 1) == "so")
    return (true);
  return (false);
}

std::vector<std::string>   File::getLibs()
{
  dirent                   *de;
  DIR                      *dir;
  std::vector <std::string> result;

  dir = File::Opendir(_path.c_str());
  if (dir)
  {
    while (true)
    {
      de = File::Readdir(dir);
      if (de == NULL)
        break;
      if (de->d_type != DT_DIR && checkExtension(de->d_name))
        result.push_back(std::string( de->d_name ));
    }
    File::Closedir(dir);
    std::sort(result.begin(), result.end());
  }
  else
    throw arcade::Exception(_path, " Folder doesn't exist");
  return (result);
}
