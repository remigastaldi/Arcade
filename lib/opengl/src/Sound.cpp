/*
** Sound.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Fri Apr 07 10:51:17 2017 gastal_r
** Last update	Fri Apr 07 15:28:15 2017 gastal_r
*/

#include        "Sound.hpp"

void            Sound::Data::loadTypeSound(arcade::Sound type, const std::string &path)
{
  _type = type;
  if (!_soundBuffer.loadFromFile(path))
    std::cerr << "Failed to load " << path << std::endl;
}

void            Sound::loadSounds(const std::vector<std::string> &path)
{
  int i = 0;
  for (std::vector<std::string>::const_iterator it = path.begin(); it != path.end(); ++it)
  {
    Sound::Data data;

    switch (i)
    {
      case 0 :
        data.loadTypeSound(arcade::NEW_GAME, *it);
      break;
      case 1 :
        data.loadTypeSound(arcade::GAME_OVER, *it);
      break;
      case 2 :
        data.loadTypeSound(arcade::MY_SHOOT, *it);
      break;
      case 3 :
        data.loadTypeSound(arcade::EVIL_SHOOT, *it);
      break;
      case 4 :
        data.loadTypeSound(arcade::POWERUP, *it);
      break;
      case 5 :
        data.loadTypeSound(arcade::EXPLOSION, *it);
      break;
      case 6 :
        data.loadTypeSound(arcade::OTHER, *it);
      break;
    }
    _data.push_back(data);
    ++i;
  }
}

void            Sound::playSound(arcade::Sound type)
{
  for (std::vector<Sound::Data>::iterator it = _data.begin(); it != _data.end(); ++it)
  {
    if (it->getType() == type)
      it->playSound();
  }
}

void            Sound::playMusic(const std::string &path)
{
  _music.stop();

  if (!_music.openFromFile(path))
    std::cerr << "Unable to open " << path << std::endl;
  _music.setVolume(80);
  _music.play();
  _music.setLoop(true);
}
