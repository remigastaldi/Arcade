/*
** LNcurses.hpp for cpp_arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Thu Mar 09 19:10:52 2017 gastal_r
** Last update	Sat Mar 18 23:57:56 2017 gastal_r
*/

#ifndef       _LNcurses_HPP_
#define       _LNcurses_HPP_

#include      "IGraph.hh"
#include      "Ncurses.hpp"

class LNcurses : public arcade::IGraph
{
public:
  LNcurses ();
  virtual ~LNcurses ();

  void        aInit(size_t, size_t);
  void        aClose();
  void        aTile(size_t, size_t, arcade::TileType);
  void        aTile(size_t, size_t, void *){};
  void        *aGetTexture(const std::string &){return (NULL);}
  void        aPutText(size_t, size_t, const std::string &,
                      size_t, arcade::Color, const std::string &);
  void        aClear();
  void        aRefresh();
  arcade::CommandType aCommand();
  std::string   aChar();

private:
  WINDOW	*_win;
};

#endif        /* !_LNcurses_HPP_ */
