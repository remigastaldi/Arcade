/*
** Exception.hpp for cpp_nanotekspice
**
** Made by	Full Name
** Login	gastal_r
**
** Started on	Thu Mar 02 17:13:18 2017 Full Name
** Last update	Mon Apr 03 02:13:18 2017 gastal_r
*/

#ifndef     _EXCEPTION_HPP_
#define     _EXCEPTION_HPP_

#include    <exception>
#include    <string>

namespace arcade
{
  class Exception : public std::exception
  {
  public:
    explicit Exception(const std::string &message) : _message(message) {;}
    Exception(const std::string &message, const std::string &var) : _message(message)
    {
      _message += var;
    }
    virtual ~Exception() throw() {};
    virtual const char* what() const throw() { return(_message.c_str());}

  private:
    std::string   _message;
  };
}

#endif /* !_EXCEPTION_HPP_ */
