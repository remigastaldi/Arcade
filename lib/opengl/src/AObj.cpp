/*
** AObj.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Apr 02 23:40:00 2017 gastal_r
** Last update	Sun Apr 09 03:37:58 2017 gastal_r
*/

#include    "AObj.hpp"

void        AObj::readObj(const std::string &path)
{
  Data  data;
  std::string line;
  std::pair<std::string, size_t> name;

  std::ifstream in(path, std::ios::in);
  if (!in)
    throw arcade::Exception("Cannot open ", path);
  getline(in, line);
  size_t pos;
  while ((pos = line.find('=')) != std::string::npos)
  {
    std::string token = line.substr(0, pos);
    name.first = token;
    line.erase(0, pos + 1);
    if ((pos = line.find(':')) != std::string::npos)
    {
      std::string value = line.substr(0, pos);
      name.second = std::stoi(value);
      line.erase(0, pos + 1);
    }
    data.addName(name);
  }
  while (getline(in, line))
  {
    if (line.substr(0,1) != "#" && !line.empty())
    {
      std::istringstream s(line);

      for (short i = 0; i < 5; ++i)
      {
        float value;
        s >> value;
        data.addVertex(value);
      }
    }
  }
  _objs.push_back(data);
}

bool      AObj::checkExtension(const std::string &str) const
{
  if (str.substr(str.find_last_of(".") + 1) == "aobj")
    return (true);
  return (false);
}

void      AObj::loadObjs()
{
  DIR                      *dir;
  std::vector <std::string> result;


  _objs.clear();
  std::string path("games/");
  path += _game;
  path += "/res/objs/";
  dir = File::Opendir(path.c_str());
  if (dir)
  {
    while (true)
    {
      dirent *de = File::Readdir(dir);
      if (de == NULL)
        break;
      if (de->d_type != DT_DIR && checkExtension(de->d_name))
      {
        std::ostringstream filename;
        filename << path << de->d_name;
        readObj(filename.str());
      }
    }
    File::Closedir(dir);
  }
}

bool            AObj::Data::checkName(const std::string &name) const
{
  for (std::vector<std::pair<std::string, size_t>>::const_iterator it = _name.begin(); it != _name.end(); ++it)
  {
    if (it->first == name)
      return (true);
  }
  return (false);
}

const AObj::Data &AObj::getObj(const std::string &name) const
{
  for (std::vector<Data>::const_iterator it = _objs.begin(); it != _objs.end(); ++it)
  {
    if (it->checkName(name))
    {
      return (*it);
    }
  }
  throw arcade::Exception(name, " doesn't exist");
}

size_t            AObj::Data::getIndex(const std::string &name)   const
{
  for (std::vector<std::pair<std::string, size_t>>::const_iterator it = _name.begin(); it != _name.end(); ++it)
  {
    if (it->first == name)
      return (it->second);
  }
  throw arcade::Exception(name, " doesn't exist");
}

void              AObj::Data::reset()
{
  _name.clear();
  _vertex.clear();
}
