#include <iostream>

struct Base {
  Base() { std::cout << "Base\n"; }
  ~Base() { std::cout << "~Base\n"; }
};

struct Derived : public Base {
  Derived() { std::cout << "Derived\n"; }
  ~Derived() { std::cout << "~Derived\n"; }
};

int main() {
  { Derived d; }

  std::cout << "\n\npointers\n";
  Base* p = new Derived;
  delete p;

  return 0;
}
/* 
in order to call the right destructor 
this should be marked as virtual 
we will pay in terms of memory overload */