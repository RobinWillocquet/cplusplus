#include <iostream>
#include "intstack.h"

void test () {
  try{
    IntStack st (-2);
    st.print();
  }
  catch(const char* err){
    std::cout << err << std::endl;
  }
  
  IntStack st (3);
  st.print(); // [ [

  st.push(81);
  st.print(); // [ 81 [

  st.push(52);
  st.print(); // [ 81 52 [

  st.push(36);
  st.print(); // [ 81 52 36 [

  try{  
    st.push(80);
    st.print(); // Là il y a erreur !
  }
  catch(const char* err){
    std::cout << err << std::endl;
  }

  std :: cout << st.pop () << std::endl; // 36
  st.print (); // [ 81 52 [

  std :: cout << st.pop () << std::endl; // 52
  st.print(); // [ 81 [

  std :: cout << st.pop () << std::endl; // 81
  st.print(); // [ [

  try{
    std :: cout << st.pop () << std::endl; // Là aussi il y a erreur !
    st.print(); // [ [
  }
  catch(const char* err){
    std::cout << err << std::endl;
  }
}





int main () {
  test();
  return 0;
}
