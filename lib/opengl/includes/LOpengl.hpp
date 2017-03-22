/*
** LOpengl.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 19 01:04:21 2017 gastal_r
** Last update	Wed Mar 22 10:54:00 2017 gastal_r
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
#include        "IGraph.hh"
#include        "Exception.hpp"
#include        "Protocol.hpp"

class LOpengl : public arcade::IGraph
{
public:
  LOpengl ();
  virtual ~LOpengl ();

  void          aInit(size_t, size_t);
  void          aClose();
  void          aTile(size_t, size_t, arcade::TileType);
  void          aTile(size_t, size_t, void *);
  void          aAssignTexture(const arcade::TileType tile, const std::string &path, const arcade::Color color);
  void          *aGetTexture(const std::string &);
  sf::Color     fillColor(arcade::Color);
  void          aPutText(size_t, size_t, const std::string &,
                         size_t, arcade::Color, const std::string &);
  void          aClear();
  void          aRefresh();
  arcade::CommandType aCommand();
  std::string   aChar();

private:
  int          _player_x;
  int          _player_y;
  arcade::CommandType _dir;
  sf::RenderWindow _win;
  sf::Event        _event;
  sf::Texture      _obstacle;
  sf::Texture      _floor;

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

      -5,  5, -5,  0, 0,
       5,  5, -5,  1, 0,
      -5,  5,  5,  0, 1,
      -5,  5,  5,  0, 1,
       5,  5, -5,  1, 0,
       5,  5,  5,  1, 1,

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
};

#endif          /* !_LOPENGL_HPP_ */
