#pragma once

#include "Ports/Port.hpp"

// TYPES

// STRUCT

namespace CompoMe {

namespace Core {

class in : public CompoMe::Port {
public:
  //! Default constructor
  in();

  //! Destructor
  virtual ~in() noexcept;

  // FUNCTION_IN //////////////////////////////////////////////////////////////
  virtual bool connect_interface(CompoMe::Interface &p_i);

  virtual CompoMe::Interface &get_interface();

  virtual bool is_connected_interface(CompoMe::Interface &p_i);
  virtual bool is_connected_interface();

  virtual bool disconnect_interface();
  virtual bool disconnect_interface(CompoMe::Interface &p_i);

  // FUNCTION /////////////////////////////////////////////////////////////////

  // GET/SET //////////////////////////////////////////////////////////////////

private:
  // YOU PRIVATE DATA//////////////////////////////////////////////////////////
  CompoMe::Interface *a_interface;
  //---------------------------------------------------------------------------
};

} // namespace Core

} // namespace CompoMe