//
//  main.c
//  quantumQueens
//
//  Created by Luc on 16/10/2016.
//
//

#include "quantum.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#ifdef M_PI
#define pi M_PI
#else
#define pi 3.141592654
#endif

int main(int argc, const char * argv[]) {
    quantum_reg reg;
    int i, width=18;
    
    int Queen0[2] = {0,1};
    int Queen1[2] = {2,3};
    int Queen2[2] = {4,5};
    int Queen3[2] = {6,7};
    
    
    srand(time(0));
    
    reg = quantum_new_qureg(0, width);
    
    return 0;
}
