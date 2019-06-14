#pragma once

#include <ostream>

#include "Data/test.hpp"

#include "Data/Struct_B.hpp"

struct B_1 : public B {

  /////////////////////////////////////////////////////////////////////////////
  //                                ATTRIBURE                                //
  /////////////////////////////////////////////////////////////////////////////
  int t;

  /////////////////////////////////////////////////////////////////////////////
  //                               CONSTRUCTEUR                              //
  /////////////////////////////////////////////////////////////////////////////
  B_1();

  B_1(int p_t);

  /////////////////////////////////////////////////////////////////////////////
  //                               GET and SET                               //
  /////////////////////////////////////////////////////////////////////////////
  int get_t() const;

  void set_t(const int value);

  /////////////////////////////////////////////////////////////////////////////
  //                               FUNCTION                                  //
  /////////////////////////////////////////////////////////////////////////////

  virtual void action1();
  virtual void action2(int a);
  virtual int action3();
  virtual int action4(int a);
  virtual int action5(int a, int b);

  virtual void to_stream(std::ostream &) const;
};

///////////////////////////////////////////////////////////////////////////////
//                               << STREAM >>                                //
///////////////////////////////////////////////////////////////////////////////
std::ostream &operator<<(std::ostream &os, const B_1 &c);
std::istream &operator>>(std::istream &os, B_1 &c);

std::ostream &operator<<(std::ostream &os, const B_1 *c);
std::istream &operator>>(std::istream &os, B_1 *&c);
