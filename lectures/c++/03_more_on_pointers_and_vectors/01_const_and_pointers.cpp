#include <iostream>

template <typename T>
void print_sentinel(const T* a, const std::size_t l);

int main() {
  int a{8}, b{7};
  int* pi{&a};

  const int* pc{&a}; // trick: const int *pc - pointer pointing to int const
  // *pc = 7; 	// error
  a = 15;  // I can obviously change a
  pc = &b; //valid

  int* const cp{&a}; //pointed adress cannot change
  a = b;
  *cp = 33;
  // cp = &b;   // error

  const int* const cpc{&a};

  // *cpc = 0;  // error
  // cpc = &n;  // error
  a = 99;

  int aa[4]{};
  print_sentinel(aa, 4);

  return 0;
}

template <typename T>
void print_sentinel(const T* a, const std::size_t length) {
  const T* const end{a + length}; //the sentinel
  for (; a != end; ++a)
    std::cout << *a << std::endl;
    // we declare the sentinel as const const because we do not
    //want to chenge a memory location that doesn't belong to our array
    //and we do not want to move it since the length is fixed
}
