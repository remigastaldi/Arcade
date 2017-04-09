/*
** Level.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Sat Apr 08 19:20:30 2017 gastal_r
** Last update	Sun Apr 09 15:19:18 2017 gastal_r
*/

#ifndef       _LEVEL_HPP
#define       _LEVEL_HPP

#include      <string>
#include      <vector>
#include      <fstream>
#include      <iostream>
#include      "File.hpp"
#include      "Exception.hpp"

#define SOLAR_RES "games/solarfox/res/"

class         Level
{
public:
  Level ();
  virtual     ~Level (){};

  bool        checkFileName(const std::string &str) const;

  const std::string &getNextLvl();
  size_t            getNbLvl() const        {return (_lvlNames.size());}
  size_t            getCurrentLvl() const   {return (_currentLvl);}

private:
  std::vector<std::string> _lvlNames;
  size_t                   _currentLvl;
};

#endif        /* !_LEVEL_HPP */
