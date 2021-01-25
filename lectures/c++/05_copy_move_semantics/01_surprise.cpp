#include <iostream>

struct X {
  char member;
};

int main() {

  // function automatically introduced by the compiler:
  X x1;                 // default ctor, built-in types are left un - initilized
  X x2{x1};             // copy ctor
  X x3{std::move(x2)};  // move ctor
  X x4{};               // default ctor calling {} to each member,  built-in types are initilized
                        // to the default value (e.g 0)
                        // for custom types there is no difference in using line 8 or 11
  x4 = x3;              // copy assignment
  X x5;                 // default ctor
  x5 = std::move(x4);   // move assignment
  std::cout << x5.member << std::endl; 
   /* what do you expect?? if you run the code
 many times the output changes - random valu
 since x5 it was moved from x4: the content of x4 was moved ("stolen")
 by x5, but x4 was equal to x3 which stole x2 which copied from x1 which is 
 ninitiualized. If you type x1{} then it would be initialized to the
 default value member="" */

                                      
  return 0;
}
