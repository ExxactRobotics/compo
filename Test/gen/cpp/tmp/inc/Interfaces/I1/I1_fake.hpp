#pragma once

#include "Data/Types.hpp"
#include "Interfaces/I1/I1.hpp"

#include <ostream>

template <typename To, typename Ti>
class I1_fake : public I1
{
public:
  //! Default constructor
  I1_fake(std::string& des, To& out, Ti& in):des(des),o(out),i(in)
            {

            }

  //! Destructor
  virtual ~I1_fake() noexcept{}

  /////////////////////////////////////////////////////////////////////////////
  //                               GET and SET                               //
  /////////////////////////////////////////////////////////////////////////////


protected:

private:
  std::string des;
  To& o;
  Ti& i;
};
