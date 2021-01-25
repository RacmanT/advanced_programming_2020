#include <iostream>
#include <memory>  // std::uniqe_ptr

#include "ap_error.h"

class Vector {
  std::unique_ptr<double[]> elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {
    // std::cout << "Vector ctor\n";
  }

  Vector(Vector&&) noexcept = default;
  Vector& operator=(Vector&&) noexcept = default;

  double& operator[](const unsigned int i) noexcept {  // noexcept ---> better
                                                       // code, faster code
    return elem[i];
  }  // you can use smart pointers almost like raw pointers

  const double& operator[](const unsigned int i)
      const noexcept {  // noexcept ---> better code, faster code
    return elem[i];
  }  // you can use smart pointers almost like raw pointers

  ~Vector() noexcept { std::cout << "~Vector\n"; }
};
/*
  noexcept keyword: marks that a function will not throw any exception
  and the overall performance will increase. Some examples of these functions could
  be the move assignament (since the resources have already been aquired), [] operator,
  all destructors without std::cout! 
  if an excpetion is thrown in an noexcept then the program abort
*/
class ManyResources {
  std::unique_ptr<double[]> ptr;
  Vector v;

 public:
  ManyResources() : ptr{new double[5]}, v{3} {
    std::cout << "ManyResources ctor\n";
    AP_ERROR(false) << "I am simulating something wrong.\n";
  }
  ~ManyResources() noexcept { std::cout << "~ManyResources\n"; }
};

 /*  smart pointers implements RAII so releases resources as 
  soon as the vector is not available anymore */

int main() {
  try {
    std::unique_ptr<int[]> up{new int[7]};  // RAII 
    ManyResources mr;

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}
