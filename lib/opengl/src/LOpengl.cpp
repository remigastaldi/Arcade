/*
** LOpengl.cpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Mar 19 01:04:30 2017 gastal_r
** Last update	Sun Apr 09 15:41:52 2017 gastal_r
*/

#include        "LOpengl.hpp"

LOpengl::LOpengl()
{}

LOpengl::~LOpengl()
{}

void            LOpengl::aInit(arcade::ICore *core, size_t width, size_t height)
{
  sf::ContextSettings contextSettings;

  _xView = 0.f;
  _yView = 0.f;
  _core = core;
  _checkLoadObj = true;

  _freakyFont.loadFromFile("lib/res/fonts/freaky_font.ttf");
  _pressStartFont.loadFromFile("lib/res/fonts/press_start.ttf");
  _sound.loadSounds(core->getSounds());

  contextSettings.depthBits = 24;
  _win.create(sf::VideoMode(width, height),"Arcade",  sf::Style::Fullscreen, contextSettings);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  _win.setActive(true);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glClearDepth(1.f);

  glViewport(0, 0, _win.getSize().x, _win.getSize().y);
  glMatrixMode(GL_PROJECTION);
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
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  _win.setActive(false);
  _win.close();
}

sf::Uint8				*LOpengl::fillPixelsColor(arcade::Color col)
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

sf::Texture     LOpengl::createColoredTexture(arcade::Color color)
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

void            LOpengl::aTile(size_t x, size_t y, int speed, arcade::TileType type, arcade::CommandType dir)
{
  LOpengl::Data data;

  data.x = x;
  data.y = y;
  data.type = type;
  data.dir = dir;
  data.speed = speed;
  data.cf = speed;
  data.nbf = 0;
  _data.push_back(data);
}

void          LOpengl::loadVertex(std::pair<AObj::Data, size_t> &obj, const std::string &name)
{
  if (obj.first.getSize() == 0)
    {
      obj.first = _objs.getObj(name);
      obj.second = obj.first.getIndex(name);
    }
  glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), obj.first.getVertex());
  glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), obj.first.getVertex() + 3);
}

void          LOpengl::checkRotation(arcade::CommandType dir)
{
  switch (dir)
  {
    case arcade::CommandType::GO_UP :
      glRotatef(-90.f, 0.f, 0.f, 1.f);
      break;
    case arcade::CommandType::GO_DOWN:
      glRotatef(90.f, 0.f, 0.f, 1.f);
      break;
    case arcade::CommandType::GO_LEFT :
      //glRotatef(0.f, 0.f, 0.f, 1.f);
      break;
    case arcade::CommandType::GO_RIGHT :
      glRotatef(180.f, 0.f, 0.f, 1.f);
      break;
    default :
      break;
  }
}

void          LOpengl::drawElem(size_t x, size_t y, arcade::TileType type, arcade::CommandType dir, int dx, int dy)
{

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (type == arcade::TileType::SHIP)
  {
    _xView = -((x - 26.0) * 15.0) - dx * 1.5;
    _yView = -((y - 26.0) * 15.0) + dy * 1.5;
  }
  gluLookAt(255.f - _xView / 2,
            140.f + _yView / 2, 110.f,
            255.f - _xView / 2,
            205.f + _yView / 2, 0.f,
            0.f, 0.f, 1.f);

  glPushMatrix();

  switch (type)
  {
    case arcade::TileType::BLOCK :
      loadVertex(_blockObj, "BLOCK");
      sf::Texture::bind(&_blockTex);
      glTranslatef((x * 10) + dx, 500.f  -((y * 10) - dy), _blockObj.second);
      glDrawArrays(GL_TRIANGLES, 0, _blockObj.first.getSize() / 5);
      break;
    case arcade::TileType::EMPTY :
      loadVertex(_emptyObj, "EMPTY");
      sf::Texture::bind(&_emptyTex);
      glTranslatef((x * 10) + dx, 500.f  -((y * 10) - dy), _emptyObj.second);
      glDrawArrays(GL_TRIANGLES, 0, _emptyObj.first.getSize() / 5);
      break;
    case arcade::TileType::OBSTACLE :
      loadVertex(_obstacleObj, "OBSTACLE");
      sf::Texture::bind(&_obstacleTex);
      glTranslatef((x * 10) + dx, 500.f  -((y * 10) - dy), _obstacleObj.second);
      glDrawArrays(GL_TRIANGLES, 0, _obstacleObj.first.getSize() / 5);
      break;
    case arcade::TileType::EVIL_DUDE :
      loadVertex(_evilDudeObj, "EVIL_DUDE");
      sf::Texture::bind(&_evilDudeTex);
      glTranslatef((x * 10) + dx, 500.f  -((y * 10) - dy), _evilDudeObj.second);
      if (x == 40)
        glRotatef(-180.f, 0.f, 0.f, 1.f);
      else if (y == 2)
        glRotatef(-90.f, 0.f, 0.f, 1.f);
      else if (y == 40)
        glRotatef(90.f, 0.f, 0.f, 1.f);
      glDrawArrays(GL_TRIANGLES, 0, _evilDudeObj.first.getSize() / 5);
      break;
    case arcade::TileType::EVIL_SHOOT :
      loadVertex(_evilShootObj, "EVIL_SHOOT");
      sf::Texture::bind(&_evilShootTex);
      glTranslatef((x * 10) + dx, 500.f  -((y * 10) - dy), _evilShootObj.second);
      checkRotation(dir);
      glDrawArrays(GL_TRIANGLES, 0, _evilShootObj.first.getSize() / 5);
      break;
    case arcade::TileType::MY_SHOOT :
      loadVertex(_myShootObj, "MY_SHOOT");
      sf::Texture::bind(&_myShootTex);
      glTranslatef((x * 10) + dx, 500.f  -((y * 10) - dy), _myShootObj.second);
      checkRotation(dir);
      glDrawArrays(GL_TRIANGLES, 0, _myShootObj.first.getSize() / 5);
      break;
    case arcade::TileType::POWERUP :
      loadVertex(_powerUpObj, "POWERUP");
      sf::Texture::bind(&_powerupTex);
      glTranslatef((x * 10) + dx, 500.f  -((y * 10) - dy), _powerUpObj.second);
      glDrawArrays(GL_TRIANGLES, 0, _powerUpObj.first.getSize() / 5);
      break;
    case arcade::TileType::SHIP :
      loadVertex(_shipObj, "SHIP");
      sf::Texture::bind(&_shipTex);
      glTranslatef((x * 10) + dx, 500.f  -((y * 10) - dy), _shipObj.second);
      checkRotation(dir);
      glDrawArrays(GL_TRIANGLES, 0, _shipObj.first.getSize() / 5);
      break;
    case arcade::TileType::OTHER :
    {
      loadVertex(_otherObj, "OTHER");
      sf::Texture::bind(&_otherTex);
      glTranslatef((x * 10) + dx, 500.f  -((y * 10) - dy), _otherObj.second);
      glDrawArrays(GL_TRIANGLES, 0, _otherObj.first.getSize() / 5);
    }
      break;
  }
  glPopMatrix();
}

void            LOpengl::aAssignTexture(arcade::TileType tile, const std::string &path, arcade::Color color)
{
  if (_core->getCurrentGame() != _currentGame)
  {
    _blockObj.first.reset();
    _emptyObj.first.reset();
    _obstacleObj.first.reset();
    _evilDudeObj.first.reset();
    _evilShootObj.first.reset();
    _myShootObj.first.reset();
    _powerUpObj.first.reset();
    _shipObj.first.reset();
    _otherObj.first.reset();
    std::string game = _core->getCurrentGame().substr(0, _core->getCurrentGame().find_last_of("."));
    game.erase(0, game.find_last_of("_") + 1);
    _objs.setGame(game);
    _objs.loadObjs();
    _currentGame = _core->getCurrentGame();
  }

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
    case arcade::TileType::SHIP :
      if (!_shipTex.loadFromFile(path))
        _shipTex = createColoredTexture(color);
      _shipTex.generateMipmap();
      break;
    case arcade::TileType::OTHER :
      if (!_otherTex.loadFromFile(path))
        _otherTex = createColoredTexture(color);
      _otherTex.generateMipmap();
      break;
      }
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

void          LOpengl::aPutText(size_t x, size_t y, arcade::Font font,
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

  _win.pushGLStates();
  _win.draw(sfText);
  _win.popGLStates();
}

void            LOpengl::aClearAnimBuffer()
{
  _data.clear();
}

void            LOpengl::aClear()
{
  _win.clear();
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void            LOpengl::transition()
{
  _win.setActive(true);
  glEnable(GL_TEXTURE_2D);
  float i = 0;

  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  while (i < 5)
  {
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() >= 10000)
    {
      aClear();
      for (std::vector<LOpengl::Data>::iterator it = _data.begin(); it != _data.end(); ++it)
      {
        if (it->dir != arcade::CommandType::UNDEFINED)
        {
          switch (it->dir)
          {
            case arcade::CommandType::GO_LEFT :
              drawElem(it->x + 1, it->y, it->type, it->dir, -it->nbf, 0);
              break;
            case arcade::CommandType::GO_RIGHT :
              drawElem(it->x - 1, it->y, it->type, it->dir, it->nbf, 0);
              break;
            case arcade::CommandType::GO_UP :
              drawElem(it->x, it->y + 1, it->type, it->dir, 0, it->nbf);
              break;
            case arcade::CommandType::GO_DOWN :
              drawElem(it->x, it->y - 1, it->type, it->dir, 0, -it->nbf);
              break;
            default:
              drawElem(it->x, it->y, it->type, it->dir, 0, 0);
              break;
          }
          if (it->cf >= 10)
          {
            it->cf = it->speed;
            if (it->nbf >= 10)
            {
              it = _data.erase(it);
              it = it -1;
            }
            else
              it->nbf += 10 / 5;
          }
          else
          {
            it->cf += 1;
          }
        }
        else
        {
          drawElem(it->x, it->y, it->type, it->dir, 0, 0);
          if (i + 1 == 5)
          {
            it = _data.erase(it);
            it = it -1;
          }
        }
      }
      ++i;
      _core->refreshGui();
      _win.display();
      t1 = std::chrono::high_resolution_clock::now();
    }
  }
  _win.setActive(false);
}

void            LOpengl::aRefresh()
{
  if (!_data.empty())
    transition();
  _win.display();
}

arcade::CommandType   LOpengl::aCommand()
{
  _win.pollEvent(_event);

  if (_event.type == sf::Event::KeyPressed)
  {
    switch (_event.key.code)
    {
      case sf::Keyboard::S :
        return (arcade::CommandType::GO_FORWARD);
      case sf::Keyboard::Escape :
        return (arcade::CommandType::ESCAPE);
      case sf::Keyboard::Space :
        return (arcade::CommandType::SHOOT);
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
      case sf::Keyboard::Quote :
        return (arcade::CommandType::PREV_GAME);
      case sf::Keyboard::Num5 :
        return (arcade::CommandType::NEXT_GAME);
      case sf::Keyboard::Num8 :
        return (arcade::CommandType::RESTART);
      case sf::Keyboard::Num9 :
        return (arcade::CommandType::MENU);
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
