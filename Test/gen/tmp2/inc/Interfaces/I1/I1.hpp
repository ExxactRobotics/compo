#pragma once

#include "Data/code.hpp"

#include "Interfaces/Interface.hpp"

#include "Interfaces/Function_stream.hpp"
#include "Interfaces/Return_stream.hpp"

#include <functional>
class Caller;
class Fake;

class I1_caller;
class I1_fake;
class I1 : public Interface {
public:
  using MyCaller = I1_caller;
  using MyFake = I1_fake;

  virtual Caller *get_caller() override;

  //! Default constructor
  I1();

  //! Destructor
  virtual ~I1() noexcept;

  // //! Copy assignment operator
  // I1& operator=(const I1 &other){}

  // //! Move assignment operator
  // I1& operator=(I1 &&other) noexcept{}

  /////////////////////////////////////////////////////////////////////////////
  //                               GET and SET                               //
  /////////////////////////////////////////////////////////////////////////////

private:
  Caller *c;
};

Build_fake_F get_build_fake(I1 *t);
