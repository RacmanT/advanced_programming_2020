#include <iostream>

template <typename T>  //or template <class T>
T dwim(const T a, const T b);

template <typename T, int N>  //or template <class T>
T dwim2(const T a, const T b);

int main() {
  int a{5}, b{7};
  double c{3.332}, d{7.7};
  float e{23.4}, f{3.34e2};
  char g{'0'}, h{'6'};

  std::cout << dwim<int>(a, b) << '\n'
            << dwim(c, d) << '\n'
            << dwim(e, f) << '\n'
            << dwim(g, h) << std::endl;

   std::cout << dwim2<int, 3>(a, b) << '\n'
            << dwim2<double, 3>(c, d) << '\n'
            << dwim2<float, 3>(e, f) << '\n'
            << dwim2<char, 3>(g, h) << std::endl;

//if we swap the order of the arguments then the template
// can be automatically deduced
//however if we specify the type then it wins over the deduced
  std::cout << dwim3<3>(a, b) << std::endl; 
return 0;
}

template <typename T>
T dwim(const T a, const T b) {
  return a + b;
}

template <typename T, int N>
T dwim2(const T a, const T b) {
  return a + b + N;
}

template <int N, typename T>
T dwim3(const T a, const T b) {
  return a + b + N;
}