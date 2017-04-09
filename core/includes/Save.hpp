/*
** Save.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Fri Mar 17 00:03:26 2017 gastal_r
** Last update	Sun Apr 09 15:08:42 2017 gastal_r
*/

#ifndef         _SAVE_HPP_
#define         _SAVE_HPP_

#include        <vector>
#include        <string>
#include        <fstream>
#include        <iostream>
#include        <algorithm>

#define SAVE_PATH "core/res/save"

class           Save
{
  class         Data
  {
  public:
    void               setGame(const std::string &game)   { _game = game; }
    void               setValue(const std::string &value) { _value = value; }

    const std::string  &getValue() const { return (_value); }
    const std::string  &getGame() const  { return (_game); }

  private:
    std::string _game;
    std::string _value;
  };

  class         PlayerSave
  {
  public:
    const std::string       &getPlayer() const  { return (_player); }
    std::vector<Save::Data> &getSave()          { return (_data); }
    const std::string       getValue(const std::string &) const;

    void              addValue(const std::string &, const std::string &);
    void              addSave(Save::Data data)             { _data.push_back(data); }
    void              setPlayer(const std::string &player) { _player = player; }

  private:
    std::vector<Save::Data> _data;
    std::string _player;
  };

public:
  Save () {};
  virtual ~Save () {};

  void        saveScore(std::string, const std::string &);
  void        saveSetPlayer(const std::string &player) {_player = player;}
  void        loadPlayerSave();
  void        checkExistingUser();

  const std::string               getSavedScore(std::string) const;
  const std::vector<std::string>  getBestPlayersScores(std::string);


private:
  std::vector<Save::PlayerSave>  _playerSave;
  std::string        _player;
  std::fstream       _file;
};

#endif /* !_SAVE_HPP_ */
