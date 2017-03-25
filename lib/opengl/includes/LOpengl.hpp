/*
** LOpengl.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 19 01:04:21 2017 gastal_r
** Last update	Sat Mar 25 23:21:20 2017 gastal_r
*/

#ifndef         _LOPENGL_HPP_
#define         _LOPENGL_HPP_

#ifndef         GL_SRGB8_ALPHA8
#define         GL_SRGB8_ALPHA8 0x8C43
#endif

#include        <SFML/Graphics.hpp>
#include        <SFML/OpenGL.hpp>
#include        <GL/glu.h>
#include        <thread>
#include        <chrono>
#include        <cmath>
#include        "IGraph.hh"

class           LOpengl : public arcade::IGraph
{
  class         Data
  {
  public:
    int         x;
    int         y;
    arcade::TileType    type;
    arcade::CommandType dir;
  };
public:
  LOpengl ();
  virtual ~LOpengl ();

  void          aInit(arcade::ICore *, size_t, size_t);
  void          aClose();

  void          loadCube();
  void          loadTriangle();

  sf::Uint8     *fillPixelsColor(const arcade::Color &);
  sf::Sprite    createSprite(const sf::Texture &texture);
  sf::Texture   createColoredTexture(const arcade::Color &color);

  void          aTile(size_t, size_t, arcade::TileType, const arcade::CommandType &);
  void          aTile(size_t, size_t, void *);

  void          aAssignTexture(const arcade::TileType tile, const std::string &path, const arcade::Color color);
  void          *aGetTexture(const std::string &);
  sf::Color     fillColor(arcade::Color);
  void          aPutText(size_t, size_t, const arcade::Font &,
                         size_t, arcade::Color, const std::string &);

  void          transition();
  void          drawElem(size_t x, size_t y, arcade::TileType type, int dx, int dy);
  void          aClear();
  void          aRefresh();
  arcade::CommandType aCommand();
  std::string   aChar();

private:
  std::vector<LOpengl::Data> _data;
  arcade::CommandType        _dir;
  sf::RenderWindow _win;
  sf::Event        _event;
  sf::Font         _freakyFont;
  sf::Font         _pressStartFont;
  sf::Texture      _emptyTex;
  sf::Texture      _blockTex;
  sf::Texture      _obstacleTex;
  sf::Texture      _evilDudeTex;
  sf::Texture      _evilShootTex;
  sf::Texture      _myShootTex;
  sf::Texture      _powerupTex;
  sf::Texture      _otherTex;
  float            _xView;
  float            _yView;
  arcade::ICore    *_core;
  bool             _init;

  const GLfloat _cube[180] =
  {
      -5, -5, -5,  0, 0,
      -5,  5, -5,  1, 0,
      -5, -5,  5,  0, 1,
      -5, -5,  5,  0, 1,
      -5,  5, -5,  1, 0,
      -5,  5,  5,  1, 1,

       5, -5, -5,  0, 0,
       5,  5, -5,  1, 0,
       5, -5,  5,  0, 1,
       5, -5,  5,  0, 1,
       5,  5, -5,  1, 0,
       5,  5,  5,  1, 1,

      -5, -5, -5,  0, 0,
       5, -5, -5,  1, 0,
      -5, -5,  5,  0, 1,
      -5, -5,  5,  0, 1,
       5, -5, -5,  1, 0,
       5, -5,  5,  1, 1,

    /*  -5,  5, -5,  0, 0,
       5,  5, -5,  1, 0,
      -5,  5,  5,  0, 1,
      -5,  5,  5,  0, 1,
       5,  5, -5,  1, 0,
       5,  5,  5,  1, 1, */

      -5, -5, -5,  0, 0,
       5, -5, -5,  1, 0,
      -5,  5, -5,  0, 1,
      -5,  5, -5,  0, 1,
       5, -5, -5,  1, 0,
       5,  5, -5,  1, 1,

      -5, -5,  5,  0, 0,
       5, -5,  5,  1, 0,
      -5,  5,  5,  0, 1,
      -5,  5,  5,  0, 1,
       5, -5,  5,  1, 0,
       5,  5,  5,  1, 1
  };

  const GLfloat _triangle[180] =
  {
      -5,  5,  0,   0, 0,
      -5, -5,  0,   0, 1,
       0,  0,  5,   1, 0,

      -5, -5,  0,   0, 0,
       5, -5,  0,   0, 1,
       0,  0,  5,   1, 0,

       5, -5,  0,   0, 0,
       5,  5,  0,   0, 1,
       0,  0,  5,   1, 0,

       5,  5,  0,   0, 0,
      -5,  5,  0,   0, 1,
       0,  0,  5,   1, 0,

    /*  -5,  5,  0,   0, 0,
       5,  5,  0,   0, 1,
       5, -5,  0,   1, 0,
      -5, -5,  0,   1, 1 */
  };
};

#endif          /* !_LOPENGL_HPP_ */
