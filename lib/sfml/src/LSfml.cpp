/*
** LSfml.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 10:08:10 2017 gastal_r
** Last update	Sat Mar 25 21:54:28 2017 gastal_r
*/

#include        "LSfml.hpp"

LSfml::LSfml()
{}

LSfml::~LSfml()
{}

void            LSfml::aInit(arcade::ICore *core, size_t width, size_t height)
{
  _core = core;
  _freakyFont.loadFromFile("core/res/fonts/freaky_font.ttf");
  _pressStartFont.loadFromFile("core/res/fonts/press_start.ttf");
  _win.create(sf::VideoMode(width, height),"Arcade",  sf::Style::Fullscreen);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  _win.clear();
}

void            LSfml::aClose()
{
  _win.close();
}

sf::Uint8				*LSfml::fillPixelsColor(const arcade::Color &col)
{
  sf::Uint8 *pixels = new sf::Uint8[BLOCK_Y * BLOCK_Y * 4];

  sf::Color color = fillColor(col);
  for (int i = 0; i < BLOCK_Y * BLOCK_Y * 4; i +=4)
  {
    pixels[i] = color.r;
    pixels[i+1] = color.g;
    pixels[i+2] = color.b;
    pixels[i+3] = color.a;
  }
  return (pixels);
}

sf::Sprite      LSfml::createSprite(const sf::Texture &texture)
{
  sf::Sprite sprite;

  sprite.setTexture(texture);
  sprite.setScale(sf::Vector2f((float)BLOCK_Y / texture.getSize().x, (float)BLOCK_Y / texture.getSize().x));
  return (sprite);
}

void            LSfml::aTile(size_t x, size_t y, arcade::TileType type, const arcade::CommandType &dir)
{
  LSfml::Data data;

  data.x = x;
  data.y = y;
  data.type = type;
  data.dir = dir;
  _data.push_back(data);
}

sf::Texture     LSfml::createColoredTexture(const arcade::Color &color)
{
  sf::Texture texture;

  texture.create(BLOCK_Y, BLOCK_Y);
  texture.update(fillPixelsColor(color));
  texture.setSmooth(true);
  return (texture);
}

void            LSfml::aTile(size_t x, size_t y, void *texture)
{
  sf::Sprite sprite;
  sf::Texture *test = (sf::Texture*) texture;

  sprite.setTexture(*test);
  sprite.scale(sf::Vector2f(1.f, 1.f));
  sprite.setPosition((x * BLOCK_Y) + X_PAD * BLOCK_X, (y * BLOCK_Y) + Y_PAD * BLOCK_Y);
  _win.draw(sprite);
}

void            LSfml::aAssignTexture(const arcade::TileType tile, const std::string &path, const arcade::Color color)
{
  switch (tile)
  {
    case arcade::TileType::EMPTY :
      if (!_emptyTex.loadFromFile(path))
        _emptyTex = createColoredTexture(color);
      break;
    case arcade::TileType::BLOCK :
      if (!_blockTex.loadFromFile(path))
        _blockTex = createColoredTexture(color);
      break;
    case arcade::TileType::OBSTACLE :
      if (!_obstacleTex.loadFromFile(path))
        _obstacleTex = createColoredTexture(color);
      break;
    case arcade::TileType::EVIL_DUDE :
      if (!_evilDudeTex.loadFromFile(path))
        _evilDudeTex = createColoredTexture(color);
      break;
    case arcade::TileType::EVIL_SHOOT :
      if (!_evilShootTex.loadFromFile(path))
        _evilShootTex = createColoredTexture(color);
      break;
    case arcade::TileType::MY_SHOOT :
      if (!_myShootTex.loadFromFile(path))
        _myShootTex = createColoredTexture(color);
      break;
    case arcade::TileType::POWERUP :
      if (!_powerupTex.loadFromFile(path))
        _powerupTex = createColoredTexture(color);
      break;
    case arcade::TileType::OTHER :
      if (!_otherTex.loadFromFile(path))
        _otherTex = createColoredTexture(color);
      break;
      }
}

void            *LSfml::aGetTexture(const std::string &path)
{
  sf::Texture *texture = new sf::Texture();

  if (!texture->loadFromFile(path))
    throw arcade::Exception("Failed to load ", path);
  return (texture);
}

sf::Color     LSfml::fillColor(const arcade::Color &color)
{
  sf::Color   n;

  (color == arcade::A_WHITE ? n = sf::Color::White :
   (color == arcade::A_BLUE ? n = sf::Color::Blue :
    (color == arcade::A_RED ? n = sf::Color::Red :
     (color == arcade::A_GREEN ? n = sf::Color::Green :
      (color == arcade::A_MAGENTA ? n = sf::Color::Magenta :
       (color == arcade::A_CYAN ? n = sf::Color::Cyan :
         (color == arcade::A_YELLOW ? n = sf::Color::Yellow : sf::Color::Black)))))));
  return (n);
}

void          LSfml::aPutText(size_t x, size_t y, const arcade::Font &font,
                              size_t size, arcade::Color color, const std::string &text)
{
  sf::Text sfText;

  switch (font)
  {
    case arcade::Font::FREAKY :
      sfText.setFont(_freakyFont);
      break;
    case arcade::Font::PRESS_START :
      sfText.setFont(_pressStartFont);
      break;
  }
  sfText.setString(text);
  sfText.setFillColor(fillColor(color));
  sfText.setPosition(x * BLOCK_X, (y * BLOCK_Y) + size);
  sfText.setCharacterSize(size);
  _win.draw(sfText);
}

void          LSfml::drawElem(size_t x, size_t y, arcade::TileType type, int dx, int dy)
{
  sf::Sprite sprite;

  switch (type)
  {
    case arcade::TileType::EMPTY :
      sprite = createSprite(_emptyTex);
      break;
    case arcade::TileType::BLOCK :
      sprite = createSprite(_blockTex);
      break;
    case arcade::TileType::OBSTACLE :
      sprite = createSprite(_obstacleTex);
      break;
    case arcade::TileType::EVIL_DUDE :
      sprite = createSprite(_evilDudeTex);
      break;
    case arcade::TileType::EVIL_SHOOT :
      sprite = createSprite(_evilShootTex);
      break;
    case arcade::TileType::MY_SHOOT :
      sprite = createSprite(_myShootTex);
      break;
    case arcade::TileType::POWERUP :
      sprite = createSprite(_powerupTex);
      break;
    case arcade::TileType::OTHER :
      sprite = createSprite(_otherTex);
      break;
  }
  sprite.setPosition((x * BLOCK_Y) + dx + X_PAD * BLOCK_X, (y * BLOCK_Y) - dy + Y_PAD * BLOCK_Y);
  _win.draw(sprite);
}

void          LSfml::transition()
{
  int  i = 0;

  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  while (i < BLOCK_Y)
  {
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() >= 2)
    {
      aClear();
      for (std::vector<LSfml::Data>::const_iterator it = _data.begin(); it != _data.end(); ++it)
      {
        if (it->dir != arcade::CommandType::UNDEFINED)
        {
          switch (it->dir)
          {
            case arcade::CommandType::GO_LEFT :
              drawElem(it->x + 1, it->y, it->type, -i, 0);
              break;
            case arcade::CommandType::GO_RIGHT :
              drawElem(it->x - 1, it->y, it->type, i, 0);
              break;
            case arcade::CommandType::GO_UP :
              drawElem(it->x, it->y + 1, it->type, 0, i);
              break;
            case arcade::CommandType::GO_DOWN :
              drawElem(it->x, it->y - 1, it->type, 0, -i);
              break;
            default:
              drawElem(it->x, it->y, it->type, 0, 0);
              break;
          }
      }
      else
        drawElem(it->x, it->y, it->type, 0, 0);
      }
      ++i;
      _core->refreshGui();
      _win.display();
      t1 = std::chrono::high_resolution_clock::now();
    }
  }
}

void            LSfml::aClear()
{
  _win.clear();
}

void            LSfml::aRefresh()
{
  if (!_data.empty())
  {
    transition();
    _data.clear();
  }
  _win.display();
}

arcade::CommandType   LSfml::aCommand()
{
  _win.pollEvent(_event);

  if (_event.type == sf::Event::KeyPressed)
  {
    switch (_event.key.code)
    {
      case sf::Keyboard::Escape :
        return (arcade::CommandType::ESCAPE);
      case sf::Keyboard::Up :
        return (arcade::CommandType::GO_UP);
      case sf::Keyboard::Down :
        return (arcade::CommandType::GO_DOWN);
      case sf::Keyboard::Left :
        return (arcade::CommandType::GO_LEFT);
      case sf::Keyboard::Right :
        return (arcade::CommandType::GO_RIGHT);
      case sf::Keyboard::Return :
        return (arcade::CommandType::PLAY);
      case sf::Keyboard::Num2 :
        return (arcade::CommandType::PREV_LIB);
      case sf::Keyboard::Num3 :
        return (arcade::CommandType::NEXT_LIB);
      case sf::Keyboard::Num4 :
        return (arcade::CommandType::PREV_GAME);
      case sf::Keyboard::Num5 :
        return (arcade::CommandType::NEXT_GAME);
      default :
        return (arcade::CommandType::UNDEFINED);
    }
  }
  return (arcade::CommandType::UNDEFINED);
}

std::string       LSfml::aChar()
{
  _win.pollEvent(_event);

  if (_event.type == sf::Event::KeyPressed)
  {
    switch (_event.key.code)
    {
      case sf::Keyboard::A :
        return ("A");
      case sf::Keyboard::B :
        return ("B");
      case sf::Keyboard::C :
        return ("C");
      case sf::Keyboard::D :
        return ("D");
      case sf::Keyboard::E :
        return ("E");
      case sf::Keyboard::F :
        return ("F");
      case sf::Keyboard::G :
        return ("G");
      case sf::Keyboard::H :
        return ("H");
      case sf::Keyboard::I :
        return ("I");
      case sf::Keyboard::J :
        return ("J");
      case sf::Keyboard::K :
        return ("K");
      case sf::Keyboard::L :
        return ("L");
      case sf::Keyboard::M :
        return ("M");
      case sf::Keyboard::N :
        return ("N");
      case sf::Keyboard::O :
        return ("O");
      case sf::Keyboard::P :
        return ("P");
      case sf::Keyboard::Q :
        return ("Q");
      case sf::Keyboard::R :
        return ("R");
      case sf::Keyboard::S :
        return ("S");
      case sf::Keyboard::T :
        return ("T");
      case sf::Keyboard::U :
        return ("U");
      case sf::Keyboard::V :
        return ("V");
      case sf::Keyboard::W :
        return ("W");
      case sf::Keyboard::X :
        return ("X");
      case sf::Keyboard::Y :
        return ("Y");
      case sf::Keyboard::Z :
        return ("Z");
      case sf::Keyboard::BackSpace :
        return ("BACKSPACE");
      case sf::Keyboard::Return :
        return ("ENTER");
      case sf::Keyboard::Escape :
        return ("ESCAPE");
      default :
        return ("");
    }
  }
  return ("");
}

extern "C"
{
  LSfml        *createGraph()
  {
    return (new LSfml());
  }

  void            deleteGame(arcade::IGraph *graph)
  {
    delete(graph);
  }
}
