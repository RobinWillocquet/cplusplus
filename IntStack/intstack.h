#include <iostream>
class IntStack {

public: 
  IntStack (int s) : size(s), top(0){
    if(size>0){
      tab = new int[size];
    }
    else{
      throw "ERREUR : la taille de la pile est interdite";
    }
  }

  void push (int element) {
      if (is_full()){
        throw "ERREUR : la pile est pleine, impossible de push !";
      }
      else{
        tab[top] = element;
        top = top+1;
      }
  }

  int pop () {
      if (is_empty()){
        throw "ERREUR : La pile est vide , impossible de pop !";
      }
      else{
        top = top-1;
        return tab[top];
      }
      // return 0;  // vr: inutile
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
