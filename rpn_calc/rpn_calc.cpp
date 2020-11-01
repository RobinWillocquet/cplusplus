#include <iostream>
#include"stack.h"

bool is_operand(const char* token){
    return ((token[0]>='0') and (token[0]<='9'));
}


bool is_operator(const char* token){
    return ((token[0]=='!') or (token[0]=='x') or (token[0]=='+') or (token[0]=='-') or (token[0]=='/'));
}


int rpn_eval(int n, const char* tab[]){
    int* stack = init_stack(n);
    int top = 0;
    for(int i=0;i<n;i++){
        const char* token = tab[i];
        if(is_operand(token)){
            push(atoi(token),stack,&top);
        }

        else if(is_operator(token)){
            if(token[0]=='!'){
                push(-pop(stack,&top),stack,&top);
            }
            else if(token[0]=='+'){
                push(pop(stack,&top)+pop(stack,&top),stack,&top);
            }
            else if(token[0]=='-'){
                int val0 = pop(stack,&top);
                int val1 = pop(stack,&top);
                push(val1-val0,stack,&top); 
            }
            else if(token[0]=='x'){
                push(pop(stack,&top)*pop(stack,&top),stack,&top);
            }
            else if(token[0]=='/'){
                int val0 = pop(stack,&top);
                int val1 = pop(stack,&top);
                push(val1/val0,stack,&top);
            }
        }
        
        print_stack(stack,top);

    }
    int result = stack[0];
    delete_stack(stack);
    return result;

}

