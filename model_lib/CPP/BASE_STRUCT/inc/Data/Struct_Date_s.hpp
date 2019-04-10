#pragma once

#include <ostream>

#include "Data/Types.hpp"

#include "Data/Struct.hpp"

struct Date_s : public Struct {

  /////////////////////////////////////////////////////////////////////////////
  //                                ATTRIBURE                                //
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  //                               CONSTRUCTEUR                              //
  /////////////////////////////////////////////////////////////////////////////
  Date_s();

  /////////////////////////////////////////////////////////////////////////////
  //                               GET and SET                               //
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  //                               FUNCTION                                  //
  /////////////////////////////////////////////////////////////////////////////

  virtual void to_stream(std::ostream &) const;
};

///////////////////////////////////////////////////////////////////////////////
//                               << STREAM >>                                //
///////////////////////////////////////////////////////////////////////////////
std::ostream &operator<<(std::ostream &os, const Date_s &c);
std::istream &operator>>(std::istream &os, Date_s &c);

std::ostream &operator<<(std::ostream &os, const Date_s *c);
std::istream &operator>>(std::istream &os, Date_s *&c);
