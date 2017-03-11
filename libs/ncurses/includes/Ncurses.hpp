/*
** Ncurses.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 19:29:04 2017 gastal_r
** Last update	Sat Mar 11 19:51:39 2017 gastal_r
*/

#ifndef                 NCURSES_HPP_
#define                 NCURSES_HPP_

#include                <curses.h>

class                   Ncurses
{
public:
    static void   Clear()           { clear(); }
    static WINDOW *Initscr()        { return (initscr()); }
    static int    Cbreak()          { return (cbreak());  }
    static int    StartColor(void)  { return (start_color()); }
    static int    Endwin(void)      { return (endwin());  }
    static int    Refresh()         { return (refresh()); }
    static int    Noecho()          { return (noecho());  }
    static int    Wrefresh(WINDOW *win)   { return (wrefresh(win)); }
    static int    CursSet(int visibility) { return (curs_set(visibility)); }
    static int    Werase(WINDOW *win)     { return (werase(win)); }
    static int    Nodelay(WINDOW *win, bool bf)     { return (nodelay(win, bf));  }
    static int    Mvwin(WINDOW *win, int y, int x)  { return (mvwin(win, y, x));  }
    static int    Wattron(WINDOW *win, int attrs)   { return (wattron(win, attrs)); }
    static int    Wattroff(WINDOW *win, int attrs)  { return (wattroff(win, attrs)); }
    static WINDOW *Newwin(int nlines, int ncols, int begin_y, int begin_x)
    {
      return newwin(nlines, ncols, begin_y, begin_x);
    }
    static int    Mvwprintw(WINDOW *win, int y, int x, const char *fmt)
    {
      return (mvwprintw(win, y, x, fmt));
    }
    static int    Box(WINDOW *win, chtype verch, chtype horch)
    {
        return (box(win, verch, horch));
    }
    static int    Wresize(WINDOW *win, int lines, int column)
    {
      return wresize(win, lines, column);
    }
    static int    InitPair(short pair, short f, short b)
    {
      return (init_pair(pair, f, b));
    }
};

#endif
