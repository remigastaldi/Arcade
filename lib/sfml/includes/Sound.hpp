/*
** Sound.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Fri Apr 07 10:40:32 2017 gastal_r
** Last update	Sun Apr 09 23:15:36 2017 gastal_r
*/

#ifndef       _SOUND_HPP_
#define       _SOUND_HPP_

#include      <SFML/Graphics.hpp>
#include      <SFML/Audio.hpp>
#include      "IGraph.hh"

class         Sound
{
  class       Data
  {
  public:
    arcade::Sound       getType()  const { return(_type); }
    void                loadTypeSound(arcade::Sound, const std::string &);
    void                playSound()
    {
      _sound.setBuffer(_soundBuffer);
      _sound.play();
    }

  private:
    arcade::Sound       _type;
    sf::SoundBuffer     _soundBuffer;
    sf::Sound           _sound;
  };

public:
  Sound() {};
  virtual ~Sound() {};

  void    loadSounds(const std::vector<std::string> &path);

  void    playSound(arcade::Sound);
  void    playMusic(const std::string &);

private:
  std::vector<Sound::Data>  _data;
  sf::Music                 _music;
};


#endif /* !_SOUND_HPP_ */
