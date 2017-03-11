/*
** Ncurses.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Mar 11 19:29:04 2017 gastal_r
** Last update	Sat Mar 11 19:29:08 2017 gastal_r
*/

#ifndef                 NCURSES_HPP_
#define                 NCURSES_HPP_

#include                <curses.h>

class                   Ncurses
{
public:
    static      WINDOW *mInitscr()
    {
        return (initscr());
    }

    static int mStartColor(void)
    {
        return (start_color());
    }

    static int mCursSet(int visibility)
    {
        return (curs_set(visibility));
    }

    static int mEndwin(void)
    {
        return (endwin());
    }

    static void mClear()
    {
        clear();
    }

    static int mRefresh()
    {
        return (refresh());
    }

    static int mMvwin(WINDOW *win, int y, int x)
    {
        return (mvwin(win, y, x));
    }

    static int mWrefresh(WINDOW *win)
    {
        return (wrefresh(win));
    }

    static int mInitPair(short pair, short f, short b)
    {
        return (init_pair(pair, f, b));
    }

    static WINDOW *mNewwin(int nlines, int ncols, int begin_y, int begin_x)
    {
        return newwin(nlines, ncols, begin_y, begin_x);
    }

    static int  mMvwprintw(WINDOW *win, int y, int x, const char *fmt)
    {
        return (mvwprintw(win, y, x, fmt));
    }

    static int  mWattron(WINDOW *win, int attrs)
    {
        return (wattron(win, attrs));
    }

    static int  mWattroff(WINDOW *win, int attrs)
    {
        return (wattroff(win, attrs));
    }

    static int mWerase(WINDOW *win)
    {
        return (werase(win));
    }

    static int mBox(WINDOW *win, chtype verch, chtype horch)
    {
        return (box(win, verch, horch));
    }

    static int mCbreak()
    {
        return (cbreak());
    }

    static int mNodelay(WINDOW *win, bool bf)
    {
        return (nodelay(win, bf));
    }

    static int mNoecho()
    {
        return (noecho());
    }

    static int mWresize(WINDOW *win, int lines, int column)
    {
      return wresize(win, lines, column);
    }
};

#endif
