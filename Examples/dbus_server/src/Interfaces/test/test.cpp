
#include "Interfaces//test/test.hpp"

test::test() : a_caller_stream(nullptr), a_caller_dbus(nullptr) {}

test::~test() noexcept {
  if (a_caller_stream != nullptr) {
    delete a_caller_stream;
  }

  if (a_caller_dbus != nullptr) {
    delete a_caller_dbus;
  }
}

CompoMe::Caller_stream *test::get_caller_stream() {
  if (a_caller_stream == nullptr) {
    a_caller_stream = new MyCallerStream(*this);
  }
  return a_caller_stream;
}

CompoMe::Caller_dbus *test::get_caller_dbus() {
  if (a_caller_dbus == nullptr) {
    a_caller_dbus = new MyCallerDbus(*this);
  }
  return a_caller_dbus;
}