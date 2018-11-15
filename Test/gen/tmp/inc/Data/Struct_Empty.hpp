#pragma once

#include <ostream>

#include "Data/Types.hpp"

#include "Data/Struct.hpp"




struct Empty : public Struct {

  /////////////////////////////////////////////////////////////////////////////
  //                                ATTRIBURE                                //
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  //                               CONSTRUCTEUR                              //
  /////////////////////////////////////////////////////////////////////////////
  Empty();

  

  /////////////////////////////////////////////////////////////////////////////
  //                               GET and SET                               //
  /////////////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////////////
//                               << STREAM >>                                //
///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Empty& c);
std::istream& operator>>(std::istream& os,Empty& c);
