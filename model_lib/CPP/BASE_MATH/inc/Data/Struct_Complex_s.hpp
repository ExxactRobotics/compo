#pragma once

#include <ostream>

#include "Data/Types.hpp"

#include "Data/Struct.hpp"

struct Complex_s : public Struct {

  /////////////////////////////////////////////////////////////////////////////
  //                                ATTRIBURE                                //
  /////////////////////////////////////////////////////////////////////////////
  double i;
  double r;

  /////////////////////////////////////////////////////////////////////////////
  //                               CONSTRUCTEUR                              //
  /////////////////////////////////////////////////////////////////////////////
  Complex_s();

  Complex_s(double p_i, double p_r);

  /////////////////////////////////////////////////////////////////////////////
  //                               GET and SET                               //
  /////////////////////////////////////////////////////////////////////////////
  double get_i() const;

  void set_i(const double value);
  double get_r() const;

  void set_r(const double value);

  /////////////////////////////////////////////////////////////////////////////
  //                               FUNCTION                                  //
  /////////////////////////////////////////////////////////////////////////////

  virtual void to_stream(std::ostream &) const;
};

///////////////////////////////////////////////////////////////////////////////
//                               << STREAM >>                                //
///////////////////////////////////////////////////////////////////////////////
std::ostream &operator<<(std::ostream &os, const Complex_s &c);
std::istream &operator>>(std::istream &os, Complex_s &c);

std::ostream &operator<<(std::ostream &os, const Complex_s *c);
std::istream &operator>>(std::istream &os, Complex_s *&c);