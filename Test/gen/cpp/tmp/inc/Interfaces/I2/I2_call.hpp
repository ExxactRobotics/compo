#pragma once


#include <iostream>
#include "global/I2.hpp"

constexpr unsigned int str2int(const char* str, int h = 0)
{
  return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

template <typename Ti, typename To>
class I2_caller
{
 private:
  Ti& in ;
  To& out;
  I2& comp;

 public:

  I2_caller(Ti& pin, To& pout, I2& pcomp)
 :in(pin),
 out(pout),
 comp(pcomp)
 {

   return ;
 }

  bool call()
       {

         std::string name_function;

         std::getline(in, name_function, '(');
         std::cout << "function:<"<< name_function <<">"  << "\n";

         switch(str2int(name_function.c_str())){
           
           
         };

         std::getline(in, name_function);

         return false;
       }


  

  


};