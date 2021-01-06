#include <iostream>
#include <string>

template <typename T>
class Vector {
  T* elem; // because we know that this is the way arrays works
  std::size_t _size;

 public: // interface:
  Vector(const std::size_t size) : elem{new T[size]}, _size{size} {}
  // RAII (constructor + destructor)
  // automatically release the acquired memory
  ~Vector() { delete[] elem; }

  // try to remove the const and recompile
  std::size_t size() const { return _size; } // const means that the status of our vector should not be 
                                             // modified by this function

  T& operator[](const std::size_t i) { return elem[i]; } //without const because we want to write data

  // try to comment this line and recompile
  const T& operator[](const std::size_t i) const { return elem[i]; } //with because it is used to retrive data
/* if we can modify the object the compiler will call the function without const
on the other hand if we can't modify it he will chose the functions marked with const
if a function with const is called then the compiler simply puts const in front of 
each member (for pointers it is the pointer that shouldn't change not the value so (T* const)
and i could have elem[0]= 99 is size function (changing the value not the reference)
*/

};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (auto i = 0u; i < v.size(); ++i)
    os << "v[" << i << "] = " << v[i] << std::endl;
  return os;
}

int main() {
  Vector<double> v{10};

  for (auto i = 0u; i < v.size(); ++i)
    v[i] = i;

  std::cout << v << std::endl;

  Vector<double>* pv{&v};

  // first dereference the pointer, then I can use the defined operators
  (*pv)[0] = -99.999;

  pv->operator[](1) = 77777.3333;  // or I call the function "operator" by name

  std::cout << *pv << std::endl; //again dereference in order to use the operator

  Vector<double>& rv{v};

  rv[5] = 555;

  std::cout << v << std::endl;

  return 0;
}
