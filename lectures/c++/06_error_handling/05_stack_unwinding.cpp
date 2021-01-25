#include <iostream>
#include <vector>

#include "ap_error.h"

class Foo {
 public:
  Foo() { std::cout << "Foo" << std::endl; }
  ~Foo() { std::cout << "~Foo" << std::endl; }
};

class Bar {
 public:
  Bar() { std::cout << "Bar" << std::endl; }
  ~Bar() { std::cout << "~Bar" << std::endl; }
};

class Vector {
  double* elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {
    std::cout << "Vector" << std::endl;
  }
  ~Vector() {
    delete[] elem;
    std::cout << "~Vector" << std::endl;
  }
};

class ManyResources {
  double* ptr;
  Vector v;

 public:
  ManyResources() : ptr{nullptr}, v{3} {
    std::cout << "Manyresources" << std::endl;
    try {
      ptr = new double[5];  // new(std::nothrow) double[5] could be better
      AP_ERROR(false) << "Error in ManyResources ctor." << std::endl;
    } catch (...) {
      delete[] ptr;  // <----
      throw;         // re-throw to the outer catch (passes the exception)
    }
  }

  ~ManyResources() {
    std::cout << "~Manyresources" << std::endl;
    delete[] ptr;  // <----
  }
};

/*
in the constructor ManyResources if the first resource (e.g. ptr{new double[5]})
triggers an exception then the compiler will recognize that
the object has not been properly initializated and the destructor will
not be called. On the other hand if the second resources triggers an error then
the destructor will not be called as well but the first resources is allocated and 
leads to a memory leak. To overcome that we put an try / catch block which
will deal with exceptions thrown by the first or the second resource
*/

int main() {
  Foo f;
  int* raw_ptr = new int[7];  // do not use raw ptr

  /*
  raw_ptr has to be outside otherwise the pointer would
  be deleted (but not the memory) as soon as a try block will face
  an exception (so we put it there in order to call delete[] raw_ptr in the catch)
  */
  try {
    // int * raw_ptr=new int[7]; // wrong because raw_ptr would not be visible
    // inside the catch-clause
    ManyResources mr;
    Bar b;

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;

    delete[] raw_ptr;  // <--- try to comment this and run valgrind or use the
                       // sanitize library
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;

    delete[] raw_ptr;  // <---
    return 2;
  }

  delete[] raw_ptr;  // <---
  return 0;
}
