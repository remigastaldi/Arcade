/*
** AObj.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Apr 02 23:40:00 2017 gastal_r
** Last update	Mon Apr 03 02:34:56 2017 gastal_r
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

  std::string name = path.substr(0, path.find_last_of("."));
  name.erase(0, name.find_last_of("/") + 1);

  data.setName(name);
  std::ifstream in(path, std::ios::in);
  if (!in)
    throw arcade::Exception("Cannot open ", path);
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

size_t          AObj::getObjSize(const std::string &name) const
{
  for (std::vector<Data>::const_iterator it = _objs.begin(); it != _objs.end(); ++it)
  {
    if (it->getName() == name)
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
    if (it->getName() == name)
    {
      return (it->getVertex());
    }
  }
  return (0);
}
