#include <iostream>
#include "rpn_calc.h"

bool tests(){
    bool val = false;
    const char** taba = new const char*[5] {"6", "3", "-", "5", "x"};
    const char** tabb = new const char*[5] {"25", "5", "/", "3", "+"};
    const char** tabc = new const char*[7] {"5", "!", "3", "+", "6", "!", "x"};
    int a = rpn_eval(5, taba); //doit donner 15
    int b = rpn_eval(5, tabb); //doit donner 8
    int c = rpn_eval(7, tabc); //doit donner 12
    if((a==15) and (b==8) and (c==12)){
        val = true;
    }
    if(val==1){
        std::cout << "Le test est concluant." << std::endl;
    }
    else{
        std::cout << "Le test n'est pas concluant." << std::endl;
    }
    delete [] taba;
    delete [] tabb;
    delete [] tabc;
    return val;
}

int main(){
    std::cout << tests() << std::endl;
    return 0;
}