#include <cstring>  // strcmp
#include <iostream>

int func1(const char* a);
int func2(const char* a);
void func3(const char* a);

int main() {
  int a{8};
  int* pi{&a};

  char** ppc; //array of strings char* ppc[];

  int* ap[7];

  void* pv{pi};
  // *pv; // we cannot dereference void* - we need to know how many bytes have the type pointed
  // ++pv; // we cannot increment. Why?
  int* pi2{static_cast<int*>(pv)}; //casting to int* in order to use pv

  pv = ppc;
  pv = ap;
  pv = pi;

  pi = nullptr;
  ppc = nullptr;
  // ap = nullptr;  // error, why? Because ap is a static array which is not stricty equal to a pointer
  ap[0] = nullptr; //ap[0] is a normal pointer to int
  int** bbb;
  bbb = ap;
  pv = nullptr;
  pi2 = 0;  // older codes. gets the nullptr

  // pi = NULL; // please don't do this

  double* da{new double[5]{}};
  delete[] da;  // dangling pointer 
  da = nullptr; // dereferencing it would lead to segmentation fault, it points to adress 0 which doesn't exist

  if (pi != nullptr)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi == nullptr)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  if (!pi)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  // strings are special type of char[]  - use rather std::string 
  char word[]{"Hello"}; //it it stored with a final value 0 which recognize the end of the string 
  char word2[]{'H', 'e', 'l', 'l', 'o', 0};
  if (strcmp(word, word2) == 0)  // word == word2 is
                                 // implementation-dependent (it might
                                 // compare the two pointers, i.e. the
                                 // two addresses of word and word2)
    std::cout << "same\n";
  else
    std::cout << "different\n";

  int (*fp)(const char*); // return_type (*name) (arg1,arg2,...)
  fp = func1; //it should be = & func1 but we can omit it with functions

  fp("hello");

  fp = &func2;
  fp("world");

  auto xx = func3; // pointer to func3

  xx("auto");

  decltype(&func3) x = func3; //same as auto
  x("decltype");

  return 0;
}

int func1(const char* a) {
  std::cout << "1111: " << a << std::endl;
  return 1;
}

int func2(const char* a) {
  std::cout << "2222: " << a << std::endl;
  return 2;
}

void func3(const char* a) {
  std::cout << "3333: " << a << std::endl;
}
