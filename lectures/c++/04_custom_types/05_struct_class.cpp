#include <array>
#include <iostream>
#include <vector>

struct Point_s { //default visibility: public
  double x;
  double y;
  void print();
};  // note ; at the end, since it's a declaration

void Point_s::print() {
  std::cout << "Structure. x = " << x << "; y = " << y << std::endl;
}

class Point_c { //default visibility: private
  double x;
  double y;

 public: //whatever follows is public
  void print() {
    std::cout << "Class. x = " << x << "; y = " << y << std::endl;
  }  // note no ; at the end
};   // note ; at the end, since it's a declaration

/* 
defining things inside or outside the class
is not the same in fact functions declered
inside the class are inline, so copied and pasted 
while outside are not. 
Suggestion: functions that 
are small should be written inside the class
 */

int main() {
  Point_s ps;
  ps.x = 9.9;
  ps.y = 3. / 7;

  ps.print();

  Point_c pc;
  // pc.x =7.6; // error
  pc.print();  // I can access private data through public functions

  //public members, functions: interface of the class

  Point_s* p = &ps;
  p->x = 0.0; // or (*p).x
  p->print();

  auto& pr = ps;
  ++pr.x;
  pr.print();

  Point_s array_of_structs[8];  // built-in array
  array_of_structs[0].x = 1;
  array_of_structs[0].y = 2;

  std::array<Point_s, 5> as;
  as[3].x = 3;

  std::vector<Point_s> vs;
  vs.push_back(ps); //object is copied by value so
  vs[0].x = 999; //vs[0] != ps
  ps.x = 11;
  ps.print();
  vs[0].print();

  return 0;
}
