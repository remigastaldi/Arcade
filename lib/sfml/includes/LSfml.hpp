/*
** LSfml.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Tue Mar 14 10:07:35 2017 gastal_r
** Last update	Tue Mar 14 10:20:15 2017 gastal_r
*/

#ifndef        _LSFML_HPP_
#define        _LSFML_HPP_

#include       "IGraph.hh"

class LSfml : public arcade::IGraph
{
public:
  LSfml ();
  virtual ~LSfml ();

  void        aInit(size_t, size_t);
  void        aClose();
  void        aTile(size_t, size_t, arcade::TileType);
  void        aRefresh();

private:
};

#endif         /* !_LSFML_HPP_ */
