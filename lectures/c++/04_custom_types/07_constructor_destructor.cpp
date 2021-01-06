#include <iostream>
#include <string>

struct Foo {
  int _i;
  double _d;
  std::string _s;

  Foo(const int i, const double d,
      const std::string& s);  // custom constructor

  Foo();  // default constructor

  ~Foo();  // destructor
};

Foo::Foo(const int i, const double d, const std::string& s) // constructor outside the class
    : _i{i}, //initialization of the constructor - can be stated in a row
      _d{d},
      _s{s}
// _i, _d, _s must be initialized in the same order they have been declared

{ //body of the constructor: {} are necessary even if it's empty
  std::cout << "custom ctor\n";
  // if you want/need you can use _i, _d, _s and change their value
  // with the usual notation +,-,=,*, call a function..
  // don't use {} because this notation is reserved for the
  // construction of the variables and at this point they have already
  // been constructed
}

Foo::Foo() {
  std::cout << "default ctor\n";  // what happens to our member variables?
                                  // default values - build in types are not initialized
                                  // while build in types uses default constructors
}

Foo::~Foo() {
  std::cout << "dtor\n";
}


//again if a constructor is short we should 
//put it inside the class
std::ostream& operator<<(std::ostream& os, const Foo& f) {
  os << f._i << " " << f._d << " " << f._s << std::endl;
  return os;
}

int main() {
  Foo f0;    // call default ctor
  Foo f1{};  // call default ctor
  /* Foo f2();  compiler error - round parethesis: it is trying to construct 
               a function. However round parentheis can be used when there are
               some arguments (but is suggested to use {})
               */

  Foo f2{8, 2.2, "hello"};
  std::cout << "f0: " << f0 << "f1: " << f1 << "f2: " << f2 << std::endl;

  // the destructor is called when the variable goes out of scope
  // constructors are called from top to bottom while
  // destructor are called from bottom to top
  return 0;
}
