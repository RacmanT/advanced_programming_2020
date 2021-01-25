#include <algorithm>  // std::copy
#include <iostream>
#include <memory>

template <typename T>
class Vector {
  std::size_t _size;
  std::unique_ptr<T[]> elem;

 public:
  // custom ctor
  explicit Vector(const std::size_t length)
      : _size{length}, elem{new T[length]{}} {
    std::cout << "custom ctor\n";
  }

  // Vector(const std::initializer_list<T> args)
  //     : _size{args.size()}, elem{new T[_size]} {
  //   std::cout << "list ctor\n";
  //   std::copy(args.begin(), args.end(), begin());
  // }

  // default ctor
  Vector() { std::cout << "default ctor\n"; }  // _size uninitialized
  // Vector() : _size{}, elem{} { std::cout << "default ctor\n"; } // this could
  // be better
  // best solution: Vector() = default;

  ~Vector() = default;

  // shallow copy - address is copied
  // deep copy - vfalue are copied

  /////////////////////////
  // copy semantics

  // copy ctor -- deep copy
  Vector(const Vector& v);

  // copy assignment -- deep copy
  Vector& operator=(const Vector& v); // l - value reference
  // end of copy semantics
  /////////////////////////

  /////////////////////////
  // move semantics - steal resources from v
  // supported also by unique ptrs because at the
  // end there is just one pntr pointing to that memory

  // move ctor
  Vector(Vector&& v) // r - value reference
   : _size{std::move(v._size)}, elem{std::move(v.elem)} {
    std::cout << "move ctor\n";
  }
  /*
  r value has no name and can't be on the right side of an equal assignament
  e.g v2 = Vector<double>(7) so the = will call the move assignment
  l value has a name a can be on the left side
  e.g v2 = v1 (named object) so the = will call the copy assignment

  to force a move on an l - value reference i can call Vector<double> v3{std::move(v1)}

  */

  // Vector(Vector&& v) = default; // ok if we would not have row pointers

  // move assignment
  Vector& operator=(Vector&& v) {
    std::cout << "move assignment\n";
    _size = std::move(v._size);
    elem = std::move(v.elem);
    return *this;
  }

  // Vector& operator=(Vector&& v) = default; // ok if we would not have row pointers

  // end move semantics
  /////////////////////////

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return &elem[0]; }
  T* begin() { return &elem[0]; }

  const T* end() const { return &elem[_size]; }
  T* end() { return &elem[_size]; }
};

// copy ctor
template <typename T>
Vector<T>::Vector(const Vector& v) : _size{v._size}, elem{new T[_size]} {
  // we allocate a new array and we populate it 
  std::cout << "copy ctor\n";
  std::copy(v.begin(), v.end(), begin() /* , end() - automatically deduced */);
  /* alternative:
  for(std::size_t i{0}; i<_size; ++i)
    elem[i] = v[i];
  */
}

// copy assignment
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
  std::cout << "copy assignment (\n";

  // we could decide that this operation is allowed if and only if
  // _size == v._size
  //

  elem.reset();              // first of all clean my memory
  auto tmp = v;              // deep copy: use copy ctor in order to create a temporary vector
  (*this) = std::move(tmp);  // finally move to swap temporary with myself
  
  // or we do everything by hand..
  // and we can do not reset and call new again if the sizes are suitable

  std::cout << ")\n";
  return *this;

  // is this approach consistent with self-assignment vx=vx?
}

template <typename T>
// why we return by value?
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) { // sum of vectors
  const auto size = lhs.size();

  // how we should check that the two vectors have the same size?

  Vector<T> res(size);
  for (std::size_t i = 0; i < size; ++i)
    res[i] = lhs[i] + rhs[i];

  return res; // copy or move?
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (const auto& x : v)
    os << x << " ";
  os << std::endl;
  return os;
}

int main() {
  std::cout << "Vector<int> v0; calls\n";
  Vector<int> v0;
  std::cout << v0.size() << "\n";
  std::cout << "Vector<int> v00{}; calls\n";
  Vector<int> v00{};
  std::cout << v00.size() << "\n";

  std::cout << "\nVector<double> v1{5}; calls\n";
  Vector<double> v1{5};

  std::cout << "\nVector<double> v2 = v1; calls\n";
  Vector<double> v2 = v1;
  std::cout << "\nv2 = Vector<double>{7}; calls\n";
  v2 = Vector<double>{7};
  std::cout << "\nVector<double> v3{std::move(v1)}; calls\n";
  Vector<double> v3{std::move(v1)};  // now v1 should not be used
  std::cout << "\nv3 = v2; calls\n";
  v3 = v2;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nassign some values to v3\n";
  {
    // auto i = v3.size();
    // while (i--)
    //   v3[i] = i;

    int c = 0;
    for (auto& x : v3)
      x = c++;
  }
  // v3=v3;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nVector<double> v4{v3 + v3}; calls\n";
  Vector<double> v4{v3 + v3};

  std::cout << "v4 = " << v4;

  std::cout << "\nNRVO: Named Return Value Optimization\n";

  std::cout << "\nv4 = v3 + v3 + v2 + v3; calls\n";
  v4 = v3 + v3 + v2 + v3;
  std::cout << "v4 = " << v4;

  return 0;
}
