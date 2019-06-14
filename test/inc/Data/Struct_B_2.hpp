#pragma once

#include <ostream>

#include "Data/test.hpp"

#include "Data/Struct_B.hpp"

struct B_2 : public B {

  /////////////////////////////////////////////////////////////////////////////
  //                                ATTRIBURE                                //
  /////////////////////////////////////////////////////////////////////////////
  int t2;

  /////////////////////////////////////////////////////////////////////////////
  //                               CONSTRUCTEUR                              //
  /////////////////////////////////////////////////////////////////////////////
  B_2();

  B_2(int p_t2);

  /////////////////////////////////////////////////////////////////////////////
  //                               GET and SET                               //
  /////////////////////////////////////////////////////////////////////////////
  int get_t2() const;

  void set_t2(const int value);

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
std::ostream &operator<<(std::ostream &os, const B_2 &c);
std::istream &operator>>(std::istream &os, B_2 &c);

std::ostream &operator<<(std::ostream &os, const B_2 *c);
std::istream &operator>>(std::istream &os, B_2 *&c);
