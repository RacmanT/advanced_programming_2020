#include <iostream>

enum month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
// enum starts with 1
using namespace std;

int main() {

  //notice that we don't need std:: anymore however this cause an
  cout << nov << endl; //compile error because there is an std::del
  // cout << dec << endl;

  //first solution - scope enum: // cout << static_cast<int>(month::dec)   << endl;
  //alternative: using std::cout, std::endl instead of the whole namespace

  return 0;
}
