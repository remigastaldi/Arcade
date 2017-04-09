/*
** LOpengl.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 19 01:04:21 2017 gastal_r
** Last update	Sun Apr 09 23:14:39 2017 gastal_r
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
#include        "Sound.hpp"

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
  void          initObj();
  void          aClose();

  void          loadVertex(std::pair<AObj::Data, size_t> &, const std::string &);
  void          checkRotation(arcade::CommandType dir);

  sf::Uint8     *fillPixelsColor(arcade::Color);
  sf::Sprite    createSprite(const sf::Texture &texture);
  sf::Texture   createColoredTexture(arcade::Color color);

  void          aTile(size_t, size_t, int, arcade::TileType, arcade::CommandType);

  void          aAssignTexture(arcade::TileType tile, const std::string &path, arcade::Color color);

  void          aPlaySound(arcade::Sound sound)     { _sound.playSound(sound); }
  void          aPlayMusic(const std::string &path) { _sound.playMusic(path); }

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
  arcade::ICore     *_core;
  AObj               _objs;
  float              _xView;
  float              _yView;
  bool               _checkLoadObj;
  std::string        _currentGame;
  sf::RenderWindow   _win;
  arcade::CommandType        _dir;

  std::vector<LOpengl::Data> _data;

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

  std::pair<AObj::Data, size_t>  _blockObj;
  std::pair<AObj::Data, size_t>  _emptyObj;
  std::pair<AObj::Data, size_t>  _obstacleObj;
  std::pair<AObj::Data, size_t>  _evilDudeObj;
  std::pair<AObj::Data, size_t>  _evilShootObj;
  std::pair<AObj::Data, size_t>  _myShootObj;
  std::pair<AObj::Data, size_t>  _powerUpObj;
  std::pair<AObj::Data, size_t>  _shipObj;
  std::pair<AObj::Data, size_t>  _otherObj;

  Sound              _sound;
  sf::Music          _music;
};

#endif          /* !_LOPENGL_HPP_ */
