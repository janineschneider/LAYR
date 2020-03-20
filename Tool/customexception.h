#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <exception>

/**
 * \brief Custom exception class \n
 *        Exception for input sequence access border violation
 * \author Janine Schneider
 * \date March, 2019
 */
class border_violation: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Violation of lower or upper block sequence input border";
  }
} bvex;

#endif // CUSTOMEXCEPTION_H
