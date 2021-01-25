#include <iostream>

struct foo{
    int a;
    /* explicit */    foo(const int a): a{a} {}
};

void bar(const foo& x){
    std::cout << x.a << std::endl;
}

int main(){
    int a{5};
    foo f{a};

    bar(f); /* output: 5
    bar(a)     output: 5
    a constructor with just one argument define an implicit 
    conversion, the constructor is invoked twice, once for f{a}
    and once for bar( f{5} ). If we want to avoid this we have
    to postpone the keyword explicit to the constructor 
    */
}
