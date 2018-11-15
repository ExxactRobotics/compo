#pragma once

#include <ostream>

#include "Data/Types.hpp"

#include "Data/Struct.hpp"






struct A : public Struct {

  /////////////////////////////////////////////////////////////////////////////
  //                                ATTRIBURE                                //
  /////////////////////////////////////////////////////////////////////////////
  int a;

  /////////////////////////////////////////////////////////////////////////////
  //                               CONSTRUCTEUR                              //
  /////////////////////////////////////////////////////////////////////////////
  A();

  

  A(int p_a);
  

  /////////////////////////////////////////////////////////////////////////////
  //                               GET and SET                               //
  /////////////////////////////////////////////////////////////////////////////
  // a
  int get_a() const {
    return this->a;
  }

  void set_a(const int value) {
    this->a = value;
  }
};

///////////////////////////////////////////////////////////////////////////////
//                               << STREAM >>                                //
///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const A& c);
std::istream& operator>>(std::istream& os,A& c);
