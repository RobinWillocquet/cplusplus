#include <iostream>
class IntStack {

public: 
  IntStack (int s) : size(s), tab(new int [size]), top(0){
  }

  void push (int element) {
      try{
        if (is_full()){
          throw "ERREUR : la pile est pleine, impossible de push !";
        }
        else{
          tab[top] = element;
          top = top+1;
        }
      }
      catch(const char* chain){
        std::cerr << chain << std::endl;
      }
  }

  int pop () {
      try{
        if (is_empty()){
          throw "ERREUR : La pile est vide , impossible de pop !";
        }
        else{
          top = top-1;
          return tab[top];
        }
      }
      catch(const char* chain){
        std::cerr << chain << std::endl;
      }
      return 0;
  }

  bool is_empty () {
      return (top==0);
  }

  bool is_full () {
      return (top==size);
  }

  void print () {
      std::cout << "[ ";
      for(int i=0;i<top;i++){
          std::cout << tab[i] << " ";
          }
      std::cout << "[" << std::endl;
  }

  void delete_stack () {
    delete [] tab;
  }

  ~IntStack () {
    delete [] tab;
  }

private:

  int size;
  int* tab;
  int top;

};