/*
** LSfml.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 10:07:35 2017 gastal_r
** Last update	Wed Mar 22 23:06:19 2017 gastal_r
*/

#ifndef         _LSFML_HPP_
#define         _LSFML_HPP_

#include        <SFML/Graphics.hpp>
#include        <thread>
#include        <chrono>
#include        "IGraph.hh"
#include        "Exception.hpp"

class LSfml : public arcade::IGraph
{
public:
  LSfml ();
  virtual ~LSfml ();

  void          aInit(size_t, size_t);
  void          aClose();

  sf::Uint8     *fillPixelsColor(arcade::Color);
  sf::Sprite    createSprite(const sf::Texture &texture);
  sf::Texture   createColoredTexture(const arcade::Color color);

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
  sf::RenderWindow _win;
  sf::Event        _event;
  sf::Texture      _emptyTex;
  sf::Texture      _blockTex;
  sf::Texture      _obstacleTex;
  sf::Texture      _evilDudeTex;
  sf::Texture      _evilShotTex;
  sf::Texture      _myShootTex;
  sf::Texture      _powerupTex;
  sf::Texture      _otherTex;
};

#endif         /* !_LSFML_HPP_ */
