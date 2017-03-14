/*
** LSfml.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 10:08:10 2017 gastal_r
** Last update	Tue Mar 14 15:52:09 2017 gastal_r
*/

#include        "LSfml.hpp"

LSfml::LSfml()
{}

LSfml::~LSfml()
{}

void            LSfml::aInit(size_t width, size_t height)
{
  std::cout << "TEST" << '\n';
  _win.create(sf::VideoMode(width, height),"Arcade");
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  _win.clear();
  _win.display();
}

void            LSfml::aClose()
{}

void            LSfml::aTile(size_t x, size_t y, arcade::TileType)
{
  sf::RectangleShape rectangle;

  rectangle.setSize(sf::Vector2f(10, 10));
  rectangle.setFillColor(sf::Color::Green);
  rectangle.setPosition(x, y);
  _win.draw(rectangle);
}

void            LSfml::aTile(size_t x, size_t y, void *texture)
{
  sf::Sprite sprite;
  sf::Texture *test = (sf::Texture*) texture;

  sprite.setTexture(*test);
  sprite.scale(sf::Vector2f(1.f, 1.f));
  sprite.setPosition(x, y);
  _win.draw(sprite);
}

void            *LSfml::aGetTexture(const std::string &path)
{
  sf::Texture *texture = new sf::Texture();

  if (!texture->loadFromFile(path))
    throw arcade::Exception("Failed to load ", path);
  return (texture);
}

void            LSfml::aRefresh()
{
  _win.display();
}

extern "C"
{
  LSfml        *createGraph()
  {
    std::cout << "GRAPH" << '\n';
    return (new LSfml());
  }

  void            deleteGame(arcade::IGraph *graph)
  {
    delete(graph);
  }
}
