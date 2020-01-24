#include "Components/C1/C1.hpp"
#include "Components/C4/C4.hpp"
#include "Components/C2/C2.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
  C1::C1 c1;
  c1.save(std::cout);
  std::cout <<  "\n";

  C2::C2 c2;
  c2.save(std::cout);
  std::cout <<  "\n";

  C4::C4 c4;
  c4.save(std::cout);
  std::cout <<  "\n";
  return 0;
}