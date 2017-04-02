/*
** LOpengl.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 19 01:04:21 2017 gastal_r
** Last update	Sun Apr 02 02:19:59 2017 gastal_r
*/

#ifndef         _LOPENGL_HPP_
#define         _LOPENGL_HPP_

#ifndef         GL_SRGB8_ALPHA8
#define         GL_SRGB8_ALPHA8 0x8C43
#endif

//#define GL_GLEXT_PROTOTYPES

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
  void          loadShip();

  sf::Uint8     *fillPixelsColor(arcade::Color);
  sf::Sprite    createSprite(const sf::Texture &texture);
  sf::Texture   createColoredTexture(arcade::Color color);

  void          aTile(size_t, size_t, arcade::TileType, arcade::CommandType);
  void          aTile(size_t, size_t, void *);

  void          aAssignTexture(arcade::TileType tile, const std::string &path, arcade::Color color);
  void          *aGetTexture(const std::string &);
  sf::Color     fillColor(arcade::Color);
  void          aPutText(size_t, size_t, arcade::Font, size_t, arcade::Color, const std::string &);

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

  const GLfloat _enemy[450] =
  {
    //back square
    1,  15, 9, 0, 0,
   -6,  15, 9, 1, 0,
    1, -15, 9, 0, 1,

    1, -15, 9, 0, 0,
   -6,  15, 9, 1, 0,
   -6, -15, 9, 0, 1,

   -6, -15, 9, 0, 0,
    1, -15, 9, 1, 0,
    1, -15, -1, 0, 1,

    1, -15, -1, 0, 0,
    -6, -15, -1, 1, 0,
    -6, -15, 9, 0, 1,

    -6, -15, -1, 0, 0,
    1, -15, -1, 1, 0,
    -6, 15, -1, 0, 1,

    -6, 15, -1, 0, 0,
    1, 15, -1, 1, 0,
    1, -15, -1, 0, 1,

    1, 15, -1, 0, 0,
    -6, 15, -1, 1, 0,
    1, 15, 9, 0, 1,

    1, 15, 9, 0, 0,
    -6, 15, -1, 1, 0,
    -6, 15, 9, 0, 1,

    -6, 15, 9, 0, 0,
    -6, -15, 9, 1, 0,
    -6, -15, -1, 0, 1,

    -6, -15, -1, 0, 0,
    -6, 15, -1, 1, 0,
    -6, 15, 9, 0, 1,

    1, -15, 9, 0, 0,
    1, 15, 9, 1, 0,
    1, 15, -1, 0, 1,

    1, 15, -1, 0, 0,
    1, -15, -1, 1, 0,
    1, -15, 9, 0, 1,


    //middle square
    1, -4, 6, 0, 0,
    1, 4, 6, 1, 1,
    3, 4, 6, 0, 1,

    3, 4, 6, 0, 0,
    3, -4, 6, 1, 0,
    1, -4, 6, 0, 1,

    1, 4, 6, 0, 0,
    1, 4, 2, 1, 0,
    3, 4, 6, 0, 1,

    3, 4, 6, 0, 0,
    1, 4, 2, 1, 0,
    3, 4, 2, 0, 1,

    3, 4, 2, 0, 0,
    1, 4, 2, 1, 0,
    1, -4, 2, 0, 1,

    1, -4, 2, 0, 0,
    3, -4, 2, 1, 0,
    3, 4, 2, 0, 1,

    3, -4, 2, 0, 0,
    1, -4, 2, 1, 0,
    3, -4, 6, 0, 1,

    3, -4, 6, 0, 0,
    1, -4, 6, 1, 0,
    1, -4, 2, 0, 0,

    3, 4, 6, 0, 0,
    4, 4, 2, 1, 0,
    3, -4, 6, 0, 1,

    3, -4, 6, 0, 0,
    3, -4, 2, 1, 0,
    3, 4, 2, 0, 1,

    // Left triangle
    1, -15, 9, 0, 0,
    1, -11, 9, 1, 0,
    9, -4, 4, 0, 1,

    9, -4, 4, 0, 0,
    1, -11, 9, 1, 0,
    1, -11, -1, 0, 1,

    1, -11, -1, 0, 0,
    9, -4, 4, 1, 0,
    1, -15, -1, 0, 1,

    9, -4, 4, 0, 0,
    1, -15, 9, 1, 0,
    1, -15, -1, 0, 1,

    // Right triangle
    1, 15, 9, 0, 0,
    1, 11, 9, 1, 0,
    9, 4, 4, 0, 1,

    9, 4, 4, 0, 0,
    1, 11, 9, 1, 0,
    1, 11, -1, 0, 1,

    1, 11, -1, 0, 0,
    9, 4, 4, 1, 0,
    1, 15, -1, 0, 1,

    9, 4, 4, 0, 0,
    1, 15, 9, 1, 0,
    1, 15, -1, 0, 1
  };

  const GLfloat _ship[394] =
  {
    //Body
    -8,  0,  0, 0, 0,
    -3, -2,  0, 1, 0,
    -3, -2,  1, 0, 1,

    -8,  0,  0, 0, 0,
    -3, -2,  1, 1, 0,
    -3,  0,  2, 0, 1,

    -8,  0,  0, 0, 0,
    -3,  0,  2, 1, 0,
    -3,  2,  1, 0, 1,

    -8,  0,  0, 0, 0,
    -3,  2,  1, 1, 0,
    -3,  2,  0, 0, 1,

    -8,  0,  0, 0, 0,
    -3, -2,  0, 1, 0,
    -3,  2,  0, 0, 1,

    -3,  0,  2, 0, 1,
    4,  2,  1, 1, 0,
    4, -2,  1, 0, 0,

    -3,  0,  2, 0, 0,
    -3,  2,  1, 0, 1,
    4,  2,  1, 1, 0,

    -3,  2,  1, 0, 0,
    4,  2,  1, 1, 0,
    5,  2,  0, 0, 1,

    -3,  2,  1, 0, 0,
    -3,  2,  0, 1, 0,
    5,  2,  0, 0, 1,

    -3,  2,  0, 0, 0,
    5,  2,  0, 1, 0,
    5,  0,  0, 0, 1,

    -3,  2,  0, 0, 0,
    -3, -2,  0, 1, 0,
    5,   0,  0, 0, 1,

    -3, -2, 0, 0, 0,
    5,  -2,  0, 1, 0,
    5,   0,  0, 0, 1,

    -3, -2,  0, 0, 0,
    5,  -2,  0, 1, 0,
    4, -2,  1, 0, 1,

    -3, -2,  1, 0, 0,
    -3, -2,  0, 1, 0,
    4, -2,  1, 0, 1,

    -3, -2,  1, 0, 0,
    4, -2,  1, 1, 0,
    -3, 0,  2, 0, 1,

    4, -2,  1, 0, 0,
    4,  2,  1, 1, 0,
    5,  0,  0, 0, 1,

    4, 2,  1, 0, 0,
    5, 2,  0, 1, 0,
    5, 0,  0, 0, 1,

    4,  -2,  1, 0, 0,
    5,  -2,  0, 1, 0,
    5,  0,  0, 0, 1,


    //Wings
    0, 2,  1, 0, 0,
    4, 2,  1, 1, 0,
    8, 7,  1, 0, 1,

    4, 2,  1, 0, 0,
    5, 2,  0, 1, 0,
    8, 7,  1, 0, 1,

    5, 2,  0, 0, 0,
    3, 2,  0, 1, 0,
    8, 7,  1, 0, 1,

    3, 2,  0, 0, 0,
    8, 7,  1, 1, 0,
    0, 2,  1, 0, 1,

    0, -2,  1, 0, 0,
    4, -2,  1, 1, 0,
    8, -7,  1, 0, 1,

    4, -2,  1, 0, 0,
    5, -2,  0, 1, 0,
    8, -7,  1, 0, 1,

    5, -2,  0, 0, 0,
    3, -2,  0, 1, 0,
    8, -7,  1, 0, 1,

    3, -2,  0, 0, 0,
    8, -7,  1, 1, 0,
    0, -2,  1, 0, 1
  };

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
    0,  0,  5,   1, 0

    /*  -5,  5,  0,   0, 0,
    5,  5,  0,   0, 1,
    5, -5,  0,   1, 0,
    -5, -5,  0,   1, 1 */
  };
};

#endif          /* !_LOPENGL_HPP_ */
