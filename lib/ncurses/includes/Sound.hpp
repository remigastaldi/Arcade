/*
** Sound.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Fri Apr 07 10:40:32 2017 gastal_r
** Last update	Fri Apr 07 15:53:27 2017 gastal_r
*/

#ifndef       _SOUND_HPP_
#define       _SOUND_HPP_

#include      <cstdlib>
#include      "IGraph.hh"

class         Sound
{
  class       Data
  {
  public:
    arcade::Sound       getType()  const {return(_type);}
    void                loadTypeSound(arcade::Sound, const std::string &);
    void                playSound();

  private:
    arcade::Sound       _type;
    std::string         _path;
  };

public:
  Sound() {};
  virtual ~Sound();

  void    loadSounds(const std::vector<std::string> &path);
  void    playSound(arcade::Sound);
  void    playMusic(const std::string &);

private:
  std::vector<Sound::Data> _data;
};


#endif /* !_SOUND_HPP_ */
