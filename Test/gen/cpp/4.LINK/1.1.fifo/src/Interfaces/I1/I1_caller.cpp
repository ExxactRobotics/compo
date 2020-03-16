
#include "Interfaces/I1/I1_caller.hpp"
#include "Errors/Error.hpp"
#include "Errors/Error_fac.hpp"

constexpr unsigned int str2int(const char *str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

I1_caller::I1_caller(I1 &pcomp) : Caller(), comp(pcomp) { return; }

bool I1_caller::call(Function_stream &is, Return_stream &os) {
  is.start();

  std::string name_function;
  std::getline(is, name_function, '(');
  bool b = this->call(name_function, is, os);

  std::string end_function;
  std::getline(is, end_function);
  if (end_function != "") {
    b = false;
  }

  os.end();
  return b;
}

bool I1_caller::call(std::string &name_function, Function_stream &is,
                     Return_stream &os) {
  bool result = false;

  switch (str2int(name_function.c_str())) {

  case str2int("f1"):
    result = this->f1(is, os);
    break;

  case str2int("f3"):
    result = this->f3(is, os);
    break;

  case str2int("f2"):
    result = this->f2(is, os);
    break;

  case str2int("f4"):
    result = this->f4(is, os);
    break;

  case str2int("f5"):
    result = this->f5(is, os);
    break;

  case str2int("get_a"):
    result = this->get_a(is, os);
    break;

  case str2int("set_a"):
    result = this->set_a(is, os);
    break;

  case str2int("get_b"):
    result = this->get_b(is, os);
    break;

  case str2int("set_b"):
    result = this->set_b(is, os);
    break;
  };

  return result;
}

bool I1_caller::f1(Function_stream &is, Return_stream &os) {

  char _l = is.get();
  if (_l != ')') {
    return false;
  }

  try {

    this->comp.f1();

  } catch (const Error &e) {
    os << "!" << &e;
  }

  return true;
}

bool I1_caller::f3(Function_stream &is, Return_stream &os) {

  char _l = is.get();
  if (_l != ')') {
    return false;
  }

  try {

    os << this->comp.f3();

  } catch (const Error &e) {
    os << "!" << &e;
  }

  return true;
}

bool I1_caller::f2(Function_stream &is, Return_stream &os) {

  int l_p1;
  is >> l_p1;

  char _l = is.get();
  if (_l != ')') {
    return false;
  }

  try {

    this->comp.f2(l_p1);

  } catch (const Error &e) {
    os << "!" << &e;
  }

  return true;
}

bool I1_caller::f4(Function_stream &is, Return_stream &os) {

  int l_p1;
  is >> l_p1;

  char _l = is.get();
  if (_l != ')') {
    return false;
  }

  try {

    os << this->comp.f4(l_p1);

  } catch (const Error &e) {
    os << "!" << &e;
  }

  return true;
}

bool I1_caller::f5(Function_stream &is, Return_stream &os) {

  int l_p1;
  is >> l_p1;
  is.get();

  int l_p2;
  is >> l_p2;

  char _l = is.get();
  if (_l != ')') {
    return false;
  }

  try {

    os << this->comp.f5(l_p1, l_p2);

  } catch (const Error &e) {
    os << "!" << &e;
  }

  return true;
}

bool I1_caller::get_a(Function_stream &is, Return_stream &os) {
  char _l = is.get();
  if (_l != ')') {
    return false;
  }

  try {
    os << this->comp.get_a();
  } catch (const Error &e) {
    os << "!" << &e;
  }

  return true;
}

bool I1_caller::set_a(Function_stream &is, Return_stream &os) {
  int set_val;
  is >> set_val;

  char l = is.get();
  if (l != ')') {
    return false;
  }

  try {
    this->comp.set_a(set_val);
  } catch (const Error &e) {
    os << "!" << &e;
  }

  return true;
}

bool I1_caller::get_b(Function_stream &is, Return_stream &os) {
  char _l = is.get();
  if (_l != ')') {
    return false;
  }

  try {
    os << this->comp.get_b();
  } catch (const Error &e) {
    os << "!" << &e;
  }

  return true;
}

bool I1_caller::set_b(Function_stream &is, Return_stream &os) {
  int set_val;
  is >> set_val;

  char l = is.get();
  if (l != ')') {
    return false;
  }

  try {
    this->comp.set_b(set_val);
  } catch (const Error &e) {
    os << "!" << &e;
  }

  return true;
}