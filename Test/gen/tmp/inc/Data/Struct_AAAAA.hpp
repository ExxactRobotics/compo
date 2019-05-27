#pragma once

#include <ostream>

#include "Data/Types.hpp"


#include "Data/Struct_AAAA.hpp"








struct AAAAA : public AAAA {

  /////////////////////////////////////////////////////////////////////////////
  //                                ATTRIBURE                                //
  /////////////////////////////////////////////////////////////////////////////
  int a5;

  /////////////////////////////////////////////////////////////////////////////
  //                               CONSTRUCTEUR                              //
  /////////////////////////////////////////////////////////////////////////////
  AAAAA();

  

  AAAAA(int p_a5);
  

  /////////////////////////////////////////////////////////////////////////////
  //                               GET and SET                               //
  /////////////////////////////////////////////////////////////////////////////
  int get_a5() const;

  void set_a5(const int value);
};

///////////////////////////////////////////////////////////////////////////////
//                               << STREAM >>                                //
///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const AAAAA& c);
std::istream& operator>>(std::istream& os,AAAAA& c);