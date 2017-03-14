/*
** LSfml.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 10:07:35 2017 gastal_r
** Last update	Tue Mar 14 18:47:19 2017 gastal_r
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
  void          aTile(size_t, size_t, arcade::TileType);
  void          aTile(size_t, size_t, void *);
  void          *aGetTexture(const std::string &);
  sf::Color     fillColor(arcade::Color);
  void          aPutText(size_t, size_t, const std::string &,
                         size_t, arcade::Color, const std::string &);
  void          aRefresh();

private:
  sf::RenderWindow _win;
};

#endif         /* !_LSFML_HPP_ */
