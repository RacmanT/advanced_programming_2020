/* to use instead of static arrays */

#include <array>
#include <iostream>

// template <class T, std::size_t N> type T and #element N
// struct array; //better choice then static arrays

template <typename T, std::size_t N>
void print_array_two(const std::array<T, N>& a); //const because we are not going to 
                                                // modify the array - guarantee

template <typename T>
void print_array_one(const T& a);

int main() {
  std::array<int, 4> a{1, 2, 3, 4};
  std::array<int, 4> b{a};  // I can copy element-wise from another std::array
                            // this is not possible with plain built-in arrays - for loop needed
  b = a;  //less or more same as 15
  for (auto x : a)  //for accessing values or a we should write (auto& x : a)
    std::cout << x << " ";
  std::cout << std::endl;

  for (auto x : b)
    std::cout << x << " ";
  std::cout << std::endl;

  a[0] = 0;  // same subscripting operator without bound checking

  for (const auto x : a)
    std::cout << x << " ";
  std::cout << std::endl;

  for (const auto x : b)
    std::cout << x << " ";
  std::cout << std::endl;

  for (auto& x : a)
    x *= 10;

  for (auto i = 0u; i < a.size(); ++i) //classic way works as well
    std::cout << "a[" << i << "] = " << a[i] << std::endl;

  b.at(90);  // bound checking at run-time and exception can be thrown

  return 0;
}

template <typename T, std::size_t N>
void print_array_two(const std::array<T, N>& a) {
  for (const auto& x : a) //reference so we will not copy big objects 
    std::cout << x << " ";  //  because we don't know what T will be
  std::cout << std::endl;
}

template <typename T> //same thing different implementation
void print_array_one(const T& a) {
  for (const auto& x : a)
    std::cout << x << " ";
  std::cout << std::endl;
}

/* if we don't use it the compiler
will just ignore them */