/*
** AObj.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Apr 02 23:40:00 2017 gastal_r
** Last update	Mon Apr 03 17:57:06 2017 gastal_r
*/

#include    "AObj.hpp"

AObj::AObj()
{}

AObj::~AObj()
{}

void        AObj::readObj(const std::string &path)
{
  Data  data;
  std::string line;

  std::ifstream in(path, std::ios::in);
  if (!in)
    throw arcade::Exception("Cannot open ", path);
  getline(in, line);
  size_t pos;
  while ((pos = line.find(':')) != std::string::npos)
  {
    std::string token = line.substr(0, pos);
    data.addName(token);
    line.erase(0, pos + 1);
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
        //std::cout << value << ' ';
        data.addVertex(value);
      }
      //std::cout << std::endl;
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
    std::sort(result.begin(), result.end());
  }
}

bool            AObj::Data::checkName(const std::string &name) const
{
  for (std::vector<std::string>::const_iterator it = _name.begin(); it != _name.end(); ++it)
  {
    if (*it == name)
      return (true);
  }
  return (false);
}

size_t          AObj::getObjSize(const std::string &name) const
{
  for (std::vector<Data>::const_iterator it = _objs.begin(); it != _objs.end(); ++it)
  {
    if (it->checkName(name))
    {
      return (it->getSize());
    }
  }
  return (0);
}

const GLfloat   *AObj::getObjVertex(const std::string &name) const
{
  for (std::vector<Data>::const_iterator it = _objs.begin(); it != _objs.end(); ++it)
  {
    if (it->checkName(name))
    {
      return (it->getVertex());
    }
  }
  return (0);
}
