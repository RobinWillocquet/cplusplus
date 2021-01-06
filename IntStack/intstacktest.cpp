#include <iostream>
#include "intstack.h"

void test () {
  IntStack st (3);
  st.print(); // [ [

  st.push(81);
  st.print(); // [ 81 [

  st.push(52);
  st.print(); // [ 81 52 [

  std::cout << std::boolalpha << st.is_full() << std::endl; // Faux, il reste une place !

  IntStack std = st;
  std.push(123);
  st.print(); // [ 81 52 [
  std.print(); // [ 81 52 123 [

  st.push(36);
  st.print(); // [ 81 52 36 [
  
  st.push(80); // Là il y a erreur !
  st.print(); 

  std::cout << std::boolalpha << st.is_full() << std::endl; // Vrai !

  std :: cout << st.pop () << std::endl; // 36
  st.print (); // [ 81 52 [

  std :: cout << st.pop () << std::endl; // 52
  st.print(); // [ 81 [

  std :: cout << st.pop () << std::endl; // 81
  st.print(); // [ [

  std :: cout << st.pop () << std::endl; // Là aussi il y a erreur !
  st.print(); // [ [

  std::cout << std::boolalpha << st.is_empty() << std::endl; // Vrai !
}

int main () {
  test();
  return 0;
}
