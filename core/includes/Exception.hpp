/*
** Exception.hpp for cpp_nanotekspice
**
** Made by	Full Name
** Login	gastal_r
**
** Started on	Thu Mar 02 17:13:18 2017 Full Name
** Last update	Mon Mar 13 21:34:09 2017 gastal_r
*/

#include    <exception>
#include    <string>

namespace arcade
{
  class Exception : public std::exception
  {
  public:
    Exception(const std::string &message) { _message = message;}
    Exception(const std::string &message, const std::string &var)
    {
       _message = message;
       _message += var;
    }
    virtual ~Exception() throw() {};
    virtual const char* what() const throw() { return(_message.c_str());}

  private:
    std::string   _message;
  };
}
