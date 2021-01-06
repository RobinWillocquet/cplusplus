#include<iostream>
#include "Integer.h"


int main () {
  Integer i;
  Integer* pi = &i;
  pi->incr();
  pi->decr();
  pi->print();
  return 0;
}