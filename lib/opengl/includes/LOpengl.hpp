/*
** LOpengl.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 19 01:04:21 2017 gastal_r
** Last update	Wed Apr 05 23:39:04 2017 gastal_r
*/

#ifndef         _LOPENGL_HPP_
#define         _LOPENGL_HPP_

#ifndef         GL_SRGB8_ALPHA8
#define         GL_SRGB8_ALPHA8 0x8C43
#endif

#include        <SFML/Graphics.hpp>
#include        <SFML/OpenGL.hpp>
#include        <SFML/Audio.hpp>
#include        <GL/glu.h>
#include        <thread>
#include        <chrono>
#include        <cmath>
#include        "IGraph.hh"
#include        "AObj.hpp"

class           LOpengl : public arcade::IGraph
{
  class         Data
  {
  public:
    int         x;
    int         y;
    int         cf;
    int         speed;
    int         nbf;
    arcade::TileType    type;
    arcade::CommandType dir;
  };

public:
  LOpengl ();
  virtual ~LOpengl ();

  void          aInit(arcade::ICore *, size_t, size_t);
  void          aClose();

  void          loadVertex(const std::string &);
  void          checkRotation(arcade::CommandType dir);

  sf::Uint8     *fillPixelsColor(arcade::Color);
  sf::Sprite    createSprite(const sf::Texture &texture);
  sf::Texture   createColoredTexture(arcade::Color color);

  void          aTile(size_t, size_t, int, arcade::TileType, arcade::CommandType);
  void          aTile(size_t, size_t, void *);

  void          aAssignTexture(arcade::TileType tile, const std::string &path, arcade::Color color);
  void          *aGetTexture(const std::string &);

  void          aAssignSound(arcade::Sound sound, const std::string &);
  void          aPlaySound(arcade::Sound);
  void          aPlayMusic(const std::string &);

  sf::Color     fillColor(arcade::Color);
  void          aPutText(size_t, size_t, arcade::Font, size_t, arcade::Color, const std::string &);

  void          transition();
  void          drawElem(size_t x, size_t y, arcade::TileType type, arcade::CommandType, int dx, int dy);
  void          aClearAnimBuffer();
  void          aClear();
  void          aRefresh();
  std::string   aChar();
  arcade::CommandType aCommand();

private:
  std::vector<LOpengl::Data> _data;
  arcade::CommandType        _dir;
  sf::RenderWindow   _win;

  sf::Event          _event;
  sf::Font           _freakyFont;
  sf::Font           _pressStartFont;

  sf::Texture        _emptyTex;
  sf::Texture        _blockTex;
  sf::Texture        _obstacleTex;
  sf::Texture        _evilDudeTex;
  sf::Texture        _evilShootTex;
  sf::Texture        _myShootTex;
  sf::Texture        _powerupTex;
  sf::Texture        _shipTex;
  sf::Texture        _otherTex;

  sf::Music          _music;
  sf::SoundBuffer    _newGameSound;
  sf::SoundBuffer    _gameOverSound;
  sf::SoundBuffer    _shootSound;
  sf::SoundBuffer    _powerupSound;
  sf::SoundBuffer    _explosionSound;
  sf::SoundBuffer    _deadSound;
  sf::SoundBuffer    _otherSound;

  float              _xView;
  float              _yView;
  arcade::ICore     *_core;
  bool               _checkLoadObj;
  AObj               _objs;
};

#endif          /* !_LOPENGL_HPP_ */
