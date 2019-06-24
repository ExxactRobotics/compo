#include "Interfaces/Temperature_i/Temperature_i_fake.hpp"

Temperature_i_fake::Temperature_i_fake(Function_stream &out, Return_stream &in)
    : Fake(out, in) {}

Temperature_i_fake::~Temperature_i_fake() noexcept {}

///////////////////////////////////////////////////////////////////////////////
//                                  FUNCTION                                 //
///////////////////////////////////////////////////////////////////////////////

// INTERFACE Function Temperature_i
// ////////////////////////////////////////////////

Temperature_sample Temperature_i_fake::get() {
  o.start();
  o << "get("

    << ")";
  o.call();

  i.pull();

  Temperature_sample ri;
  i >> ri;
  i.end();
  return ri;
}

///////////////////////////////////////////////////////////////////////////////
//                                    DATA                                   //
///////////////////////////////////////////////////////////////////////////////

// INTERFACE get/set Temperature_i
// /////////////////////////////////////////////////