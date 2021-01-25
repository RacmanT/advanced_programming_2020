#include <iostream>

// defining our default values:

struct X {
  int a = 5;  // in-class initialization
  double b;
  char c = 'a';
  X() = default;  // in-class initializers are used by the constructors
};

struct Y {
  int a = 77;
  double b;
  char c = 'a';
  Y() : a{5} {}  // what it is written here wins the in-class initialization
  Y(const Y&) = delete; // we ask the compiler to delete the copy constructor 
                        // which was automatically generated - with the delete 
                        // we can destroy every automatically genereted function
};

int main() {
  X x1;    // compiler-generated default ctor
  X x2{};  // compiler-generated default ctor calls {} on uninitialized vars
  std::cout << x1.a << "--" << x1.b << "--" << x1.c << "\n"; // 5 uninitialized 'a'
  std::cout << x2.a << "--" << x2.b << "--" << x2.c << "\n\n"; // 5 0 'a'

  Y y1;    // default ctor
  Y y2{};  // default ctor
          // the difference in using {} or not applies only when
          // we didn't declare our custom constructor (so here line 29 and 30 are the same
          // and b is uninitialized in both cases)
  std::cout << y1.a << "--" << y1.b << "--" << y1.c << "\n";
  std::cout << y2.a << "--" << y2.b << "--" << y2.c << "\n";

  // Y y3{y2}; // error: call to a deleted function 

  return 0;

/* 
if you define a custom constructor then the 
compiler will not generate a default constructor,
same if we generate a copy constructor the compiler will not
generate the move constructor. To be assure the default we use =default();

if we have one custom cunstructor the compiler
 will not generate other constructors
and so on so if you want to be sure you have these 
automatically constructed artifacts you should use default
*/
}
