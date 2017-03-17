/*
** Save.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Fri Mar 17 00:03:26 2017 gastal_r
** Last update	Fri Mar 17 02:13:16 2017 gastal_r
*/

#include        <vector>
#include        <string>
#include        <fstream>
#include        <iostream>

#define SAVE_PATH "res/save"

class           Save
{
  class         Data
  {
  public:
    void        setGame(const std::string game) {_game = game;}
    void        setValue(const std::string value) {_value = value;}
    const std::string  getValue() const {return (_value);}
    const std::string  getGame() const {return (_game);}

  private:
    std::string _game;
    std::string _value;
  };

public:
  Save ();
  virtual ~Save ();

  void        saveSetPlayer(const std::string player) {_player = player;}
  void        loadPlayerSave();

  const std::string     getSavedScore(std::string) const;

private:
  std::vector<Save::Data>  _saves;
  std::string        _player;
  std::ifstream      _file;
};
