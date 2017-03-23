/*
** LOpengl.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 19 01:04:30 2017 gastal_r
** Last update	Thu Mar 23 17:09:02 2017 gastal_r
*/

#include        "LOpengl.hpp"

LOpengl::LOpengl()
{
  _player_x = 26;
  _player_y = 26;
}

LOpengl::~LOpengl()
{

}

void            LOpengl::loadCube()
{
  glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), _cube);
  glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), _cube + 3);
}

void            LOpengl::loadTriangle()
{
  glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), _triangle);
  glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), _triangle + 3);
}

void            LOpengl::aInit(size_t width, size_t height)
{
  sf::ContextSettings contextSettings;
  contextSettings.depthBits = 24;
  _win.create(sf::VideoMode(width, height),"Arcade",  sf::Style::Fullscreen, contextSettings);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  _win.setActive(true);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glClearDepth(1.f);

  glViewport(0, 0, _win.getSize().x, _win.getSize().y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLfloat ratio = static_cast<float>(_win.getSize().x) / _win.getSize().y;
  glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 1000.f);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

_win.setActive(false);
}

void            LOpengl::aClose()
{
  _win.close();
}

sf::Uint8				*LOpengl::fillPixelsColor(const arcade::Color &col)
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

sf::Texture     LOpengl::createColoredTexture(const arcade::Color &color)
{
  sf::Texture texture;

  texture.create(BLOCK_Y, BLOCK_Y);
  texture.update(fillPixelsColor(color));
  texture.setSmooth(true);
  return (texture);
}

sf::Sprite      LOpengl::createSprite(const sf::Texture &texture)
{
  sf::Sprite sprite;

  sprite.setTexture(texture);
  sprite.setScale(sf::Vector2f(16.f / texture.getSize().x, 16.f / texture.getSize().x));
  return (sprite);
}

void            LOpengl::aTile(size_t x, size_t y, arcade::TileType type)
{
  glEnable(GL_TEXTURE_2D);
  _win.setActive(true);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

if (type == arcade::TileType::OTHER)
    {
      _player_x = x;
      _player_y = y;
    }

  if (_player_x <= 26 && _player_y <= 26)
  gluLookAt(255.f  - (26 - _player_x) * (26 - _player_x) /3,
            140.f  +  (26 - _player_y) * (26 - _player_y) /3, 110.f,
            255.f  - (26 - _player_x) * (26 - _player_x) /3,
            205.f  + (26 - _player_y) * (26 - _player_y) /3, 0.f,
            0.f, 0.f, 1.f);
  else if (_player_x > 26 && _player_y < 26)
  gluLookAt(255.f + ((26 - _player_x) * (26 - _player_x)) /3,
              140.f + (26 - _player_y) * (26 - _player_y) /3, 110.f,
              255.f + ((26 - _player_x) * (26 - _player_x)) /3,
              205.f + (26 - _player_y) * (26 - _player_y) /3, 0.f,
              0.f, 0.f, 1.f);
  else if (_player_x < 26 && _player_y > 26)
  gluLookAt(255.f  - (26 - _player_x) * (26 - _player_x) /3,
            140.f  -  (26 - _player_y) * (26 - _player_y) /2.5, 110.f,
            255.f  - (26 - _player_x) * (26 - _player_x) /3,
            205.f  - (26 - _player_y) * (26 - _player_y) /2.5, 0.f,
            0.f, 0.f, 1.f);
  else if (_player_x >= 26 && _player_y >= 26)
  gluLookAt(255.f + ((26 - _player_x) * (26 - _player_x)) /3,
              140.f - (26 - _player_y) * (26 - _player_y) /2.5, 110.f,
              255.f + ((26 - _player_x) * (26 - _player_x)) /3,
              205.f - (26 - _player_y) * (26 - _player_y) /2.5, 0.f,
              0.f, 0.f, 1.f);
  glPushMatrix();
  switch (type)
  {
    case arcade::TileType::BLOCK:
      break;
    case arcade::TileType::EMPTY:
      loadCube();
      sf::Texture::bind(&_emptyTex);
      glTranslatef(x * 10, 500.f  -(y * 10), 0);
      break;
    case arcade::TileType::OBSTACLE:
      loadCube();
      sf::Texture::bind(&_obstacleTex);
      glTranslatef(x * 10, 500.f  -(y * 10), 10);
      break;
    case arcade::TileType::EVIL_DUDE:
      break;
    case arcade::TileType::EVIL_SHOOT:
      break;
    case arcade::TileType::MY_SHOOT:
      loadTriangle();
      sf::Texture::bind(&_myShootTex);
      glTranslatef(x * 10, 500.f  -(y * 10), 5);
      break;
    case arcade::TileType::POWERUP:
      loadTriangle();
      sf::Texture::bind(&_powerupTex);
      glTranslatef(x * 10, 500.f  -(y * 10), 5);
      break;
    case arcade::TileType::OTHER:
    {
      _player_x = x;
      _player_y = y;
      loadTriangle();
      sf::Texture::bind(&_otherTex);
      glTranslatef(x * 10, 500.f  -(y * 10), 5);
    }
      break;
  }
    glDrawArrays(GL_TRIANGLES, 0, 36);
  glPopMatrix();
  _win.setActive(false);
}

void            LOpengl::aTile(size_t x, size_t y, void *texture)
{
  sf::Sprite sprite;
  sf::Texture *test = (sf::Texture*) texture;

  sprite.setTexture(*test);
  sprite.scale(sf::Vector2f(1.f, 1.f));
  sprite.setPosition((x * BLOCK_Y) + X_PAD * BLOCK_X, (y * BLOCK_Y) + Y_PAD * BLOCK_Y);
  _win.draw(sprite);
}

void            LOpengl::aAssignTexture(const arcade::TileType tile, const std::string &path, const arcade::Color color)
{
  switch (tile)
  {
    case arcade::TileType::EMPTY :
      if (!_emptyTex.loadFromFile(path))
        _emptyTex = createColoredTexture(color);
      _emptyTex.generateMipmap();
      break;
    case arcade::TileType::BLOCK :
      if (!_blockTex.loadFromFile(path))
        _blockTex = createColoredTexture(color);
      _blockTex.generateMipmap();
      break;
    case arcade::TileType::OBSTACLE :
      if (!_obstacleTex.loadFromFile(path))
        _obstacleTex = createColoredTexture(color);
      _obstacleTex.generateMipmap();
      break;
    case arcade::TileType::EVIL_DUDE :
      if (!_evilDudeTex.loadFromFile(path))
        _evilDudeTex = createColoredTexture(color);
      _evilDudeTex.generateMipmap();
      break;
    case arcade::TileType::EVIL_SHOOT :
      if (!_evilShootTex.loadFromFile(path))
        _evilShootTex = createColoredTexture(color);
      _evilShootTex.generateMipmap();
      break;
    case arcade::TileType::MY_SHOOT :
      if (!_myShootTex.loadFromFile(path))
        _myShootTex = createColoredTexture(color);
      _myShootTex.generateMipmap();
      break;
    case arcade::TileType::POWERUP :
      if (!_powerupTex.loadFromFile(path))
        _powerupTex = createColoredTexture(color);
      _powerupTex.generateMipmap();
      break;
    case arcade::TileType::OTHER :
      if (!_otherTex.loadFromFile(path))
        _otherTex = createColoredTexture(color);
      _otherTex.generateMipmap();
      break;
      }
}


void            *LOpengl::aGetTexture(const std::string &path)
{
  sf::Texture *texture = new sf::Texture();

  if (!texture->loadFromFile(path))
    throw arcade::Exception("Failed to load ", path);
  return (texture);
}

sf::Color     LOpengl::fillColor(arcade::Color color)
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

void          LOpengl::aPutText(size_t x, size_t y, const std::string &fontPath,
                              size_t size, arcade::Color color, const std::string &text)
{
  sf::Font font;

  font.loadFromFile(fontPath);
  sf::Text sfText(text, font);
  sfText.setFillColor(fillColor(color));
  sfText.setPosition(x * BLOCK_X, (y * BLOCK_Y) + size);
  sfText.setCharacterSize(size);

  _win.pushGLStates();
  _win.draw(sfText);
  _win.popGLStates();
}

void            LOpengl::aClear()
{
  _win.clear();
  glClear(GL_DEPTH_BUFFER_BIT);
}

void            LOpengl::aRefresh()
{
  _win.display();
}

arcade::CommandType   LOpengl::aCommand()
{
  _win.pollEvent(_event);

  if (_event.type == sf::Event::KeyPressed)
  {
    switch (_event.key.code)
    {
      case sf::Keyboard::Escape :
        return (arcade::CommandType::ESCAPE);
      case sf::Keyboard::Up :
        _dir = arcade::CommandType::GO_UP;
        return (arcade::CommandType::GO_UP);
      case sf::Keyboard::Down :
        _dir = arcade::CommandType::GO_DOWN;
        return (arcade::CommandType::GO_DOWN);
      case sf::Keyboard::Left :
        _dir = arcade::CommandType::GO_LEFT;
        return (arcade::CommandType::GO_LEFT);
      case sf::Keyboard::Right :
        _dir = arcade::CommandType::GO_RIGHT;
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

std::string       LOpengl::aChar()
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
  LOpengl        *createGraph()
  {
    return (new LOpengl());
  }

  void            deleteGame(arcade::IGraph *graph)
  {
    delete(graph);
  }
}
