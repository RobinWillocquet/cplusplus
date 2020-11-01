#include<iostream>

int* init_stack(int n){
    return new int[n];
}

void print_stack(int* stack, int top){
    std::cout << "[ ";
    for(int i=0;i<top;i++){
        std::cout << stack[i] << " ";
    }
    std::cout << "[" << std::endl;
}

void delete_stack(int* stack){
    delete [] stack;
}

void push(int a, int* stack, int* top){
    stack[*top] = a;
    *top = *top+1;
}

int pop(int* stack, int* top){
    *top = *top-1;
    return stack[*top];
}
