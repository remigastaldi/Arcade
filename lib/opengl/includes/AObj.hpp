/*
** AObj.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sun Apr 02 23:40:58 2017 gastal_r
** Last update	Mon Apr 03 17:51:48 2017 gastal_r
*/

#ifndef       _AObj_HPP_
#define       _AObj_HPP_

#include      <SFML/OpenGL.hpp>
#include      <vector>
#include      <string>
#include      <iostream>
#include      <fstream>
#include      "File.hpp"
#include      "Exception.hpp"

class         AObj
{
  class       Data
  {
  public:
    void              addName(const std::string &name) {_name.push_back(name);}
    void              addVertex(float value)  {_vertex.push_back(value);}

    bool              checkName(const std::string &) const;
    const GLfloat     *getVertex() const {return (&_vertex[0]);}
    size_t            getSize() const {return (_vertex.size());}

  private:
    std::vector<std::string>  _name;
    std::vector<GLfloat>      _vertex;
  };

public:
  AObj ();
  virtual         ~AObj ();
  void            loadObjs();
  void            readObj(const std::string &);
  bool            checkExtension(const std::string &str) const;
  void            setGame(const std::string &game) {_game = game;}

  const GLfloat   *getObjVertex(const std::string &name) const;
  size_t          getObjSize(const std::string &name) const;

private:
  std::string       _game;
  std::vector<Data> _objs;
};

#endif        /* !A_Obj_HPP_ */
