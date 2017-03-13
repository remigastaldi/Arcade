/*
** LNcurses.hpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 19:10:52 2017 gastal_r
** Last update	Mon Mar 13 23:00:38 2017 gastal_r
*/

#ifndef       _LNcurses_HPP_
#define       _LNcurses_HPP_

#include      "IGraph.hh"

class LNcurses : public arcade::IGraph
{
public:
  LNcurses ();
  virtual ~LNcurses ();

  void        aInit(size_t, size_t);
  void        aClose();
  void        aTile(size_t, size_t, arcade::TileType);
  void        aRefresh();

private:
};

#endif        /* !_LNcurses_HPP_ */
