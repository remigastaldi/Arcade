/*
** File.hpp for Arcade
**
** Made by	gastal_r
** Login	gastal_r
**
** Started on	Mon Mar 13 16:23:03 2017 gastal_r
** Last update	Sun Apr 09 14:56:36 2017 gastal_r
*/

#ifndef         _FILE_HPP_
#define         _FILE_HPP_

#include        <dirent.h>
#include        <sys/types.h>
#include        <algorithm>
#include        <vector>
#include        <string>
#include        <sstream>

class File
{
public:
  explicit File (const std::string &);
  virtual ~File (){};

  bool                     checkExtension(const std::string &str) const;
  std::vector<std::string> getLibs();

  static DIR           *Opendir(const char *name) { return (opendir(name)); }
  static struct dirent *Readdir(DIR *dirp)        { return (readdir(dirp)); }
  static int           Closedir(DIR *dirp)        { return (closedir(dirp)); }

private:
  std::string   _path;
};

#endif          /* !_FILE_HPP_ */
