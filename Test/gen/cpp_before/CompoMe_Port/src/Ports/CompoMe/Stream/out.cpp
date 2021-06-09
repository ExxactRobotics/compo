#include "Ports/CompoMe/Stream/out.hpp"

namespace CompoMe {

namespace Stream {

//! Default constructor
out::out() : CompoMe::Core::out() {}

//! Destructor
out::~out() {}

// Function OUT ////////////////////////////////////////////////////////////////
bool out::connect_require(CompoMe::Require_helper &p_r) {
  return CompoMe::Core::out::connect_require(p_r);
}

bool out::is_connected_require() {
  return CompoMe::Core::out::is_connected_require();
}

bool out::is_connected_require(CompoMe::Require_helper &p_i) {
  return CompoMe::Core::out::is_connected_require(p_i);
}

bool out::disconnect_require() {
  return CompoMe::Core::out::disconnect_require();
}

bool out::disconnect_require(CompoMe::Require_helper &p_r) {
  return CompoMe::Core::out::disconnect_require(p_r);
}

CompoMe::Require_helper &out::get_require() {
  return CompoMe::Core::out::get_require();
}

} // namespace Stream

} // namespace CompoMe