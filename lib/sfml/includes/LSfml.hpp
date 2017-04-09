/*
** LSfml.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 10:07:35 2017 gastal_r
** Last update	Sun Apr 09 23:15:30 2017 gastal_r
*/

#ifndef         _LSFML_HPP_
#define         _LSFML_HPP_

#include        <SFML/Graphics.hpp>
#include        <SFML/Audio.hpp>
#include        <thread>
#include        <chrono>
#include        "IGraph.hh"
#include        "Sound.hpp"

#define BLOCK_SFML 27.f

class LSfml : public arcade::IGraph
{
  class         Data
  {
  public:
    int         x;
    int         y;
    int         speed;
    int         nbf;
    float       cf;
    arcade::TileType    type;
    arcade::CommandType dir;
  };

public:
  LSfml ();
  virtual ~LSfml () {};

  void          aInit(arcade::ICore *, size_t, size_t);
  void          aClose();

  sf::Uint8     *fillPixelsColor(arcade::Color);
  sf::Sprite    createSprite(const sf::Texture &texture);
  sf::Texture   createColoredTexture(arcade::Color color);

  void          aTile(size_t, size_t, arcade::TileType);
  void          aTile(size_t, size_t, int, arcade::TileType, arcade::CommandType);
  void          aTile(size_t, size_t, void *);

  void          aAssignTexture(arcade::TileType tile, const std::string &path, arcade::Color color);
  void          *aGetTexture(const std::string &);

  void          aPlaySound(arcade::Sound sound)     { _sound.playSound(sound); }
  void          aPlayMusic(const std::string &path) { _sound.playMusic(path); }

  sf::Color     fillColor(arcade::Color);
  void          aPutText(size_t, size_t, arcade::Font,size_t, arcade::Color, const std::string &);

  void          transition();
  void          checkRotation(arcade::CommandType, sf::Sprite &);
  void          drawElem(size_t x, size_t y, arcade::TileType type, arcade::CommandType, float dx, float dy);
  void          aClear();
  void          aClearAnimBuffer();
  void          aRefresh();
  std::string   aChar();
  arcade::CommandType aCommand();

private:
  std::vector<LSfml::Data> _data;
  arcade::ICore    *_core;
  sf::RenderWindow  _win;

  Sound             _sound;

  sf::Event         _event;
  sf::Font          _freakyFont;
  sf::Font          _pressStartFont;

  sf::Texture       _emptyTex;
  sf::Texture       _blockTex;
  sf::Texture       _obstacleTex;
  sf::Texture       _evilDudeTex;
  sf::Texture       _evilShootTex;
  sf::Texture       _myShootTex;
  sf::Texture       _powerupTex;
  sf::Texture       _shipTex;
  sf::Texture       _otherTex;

} ;

#endif         /* !_LSFML_HPP_ */
