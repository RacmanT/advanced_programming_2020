#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) { //or char** argv
  for (auto i = 0; i < argc; ++i)
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;

  unsigned int a;
  {
    std::istringstream s{argv[1]}; //converting numbers to int since they are stored as strings if we pass ./exec 23 22 443 22
    s >> a;
  }
  std::cout << "a is " << a << std::endl;
  return 0;
}
// ./executable 7 hello world
// argv[0] name of executable, argv[1] == "hello",...