#include <iostream>

template <typename T>
class Vector {
  T* elem;
  std::size_t _size;

 public:
  explicit Vector(const std::size_t length)
      : elem{new T[length]{}}, _size{length} {} //new array ofT with initialized values {}

  ~Vector() { delete[] elem; }

  const T& operator[](const std::size_t& i) const { return elem[i]; } //read
  T& operator[](const std::size_t& i) { return elem[i]; } //write

  std::size_t size() const { return _size; }

  // implemented for the range-for (2 versions: one for read and one for write)
  const T* begin() const { return elem; }
  T* begin() { return elem; }

  const T* end() const { return elem + size(); }
  T* end() { return elem + size(); }
};

int main() {
  Vector<int> v1{3};
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;

  std::cout << "v1: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;

  Vector<int> v2{v1};  // compiler generated copy constructor
  // the behaviour is not what we expected because it is copied 
  // the address instead of the values

  std::cout << "v2 after default copy ctor: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v1[0] = 99;

  std::cout << "v2 after v1 has been changed: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v2[1] = -999;

  std::cout << "v1 after v2 has been changed: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;
/*
takeaway: the default copy constructor may not
behave as expected with object having a row pointer as a member
(because is copying by values but this doesn't work with pointers)
When a member is a pointer then copying the object correspond to
having another object with a member pointing to the same location as
before (while size_t is copied by value since is a build in type)
*/
  return 0;
}
