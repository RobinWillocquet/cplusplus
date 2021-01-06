#include <iostream> 

class Integer {

public:
  Integer (int v = 0) : value(v) {
  }
  void incr () {
    value = value + 1;
  }
  void decr () {
    value = value - 1;
  }
  void print () {
    std::cout << value << std::endl;
  }

private:
    int value = 0;
}; // attention ';' obligatoire !

int main () {
  return 0;
}