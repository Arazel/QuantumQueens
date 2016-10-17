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


int queen0[2] = {0,1};
int queen1[2] = {2,3};
int queen2[2] = {4,5};
int queen3[2] = {6,7};
int queenWidth = 8;

int quControlBit = 8;

int quRAM[10] = {9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

int totalWidth = 19;

#ifdef M_PI
#define pi M_PI
#else
#define pi 3.141592654
#endif


void FirstDiagonalIsEmpty(int *q, int OutReg, quantum_reg *quReg)
{
    int reg0 = OutReg+1;
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    int D00 = q[0];
    int D01 = q[0]+1;
    int D10 = q[0]+2;
    int D11 = q[0]+3;
    
    quantum_toffoli(D00, D01, reg0, quReg);
    quantum_sigma_x(D00, quReg);
    quantum_sigma_x(D10, quReg);
    quantum_toffoli(D00, D10, reg1, quReg);
    quantum_sigma_x(D10, quReg);
    
    quantum_sigma_x(D01, quReg);
    quantum_toffoli(D01,D10, reg2,quReg);
    quantum_toffoli(reg2, D11, OutReg, quReg);
    quantum_toffoli(D01, reg1, OutReg, quReg);
    
    quantum_sigma_x(D11, quReg);
    quantum_sigma_x(reg0, quReg);
    quantum_toffoli(D11, reg0, OutReg, quReg);
    
    quantum_sigma_x(reg1, quReg);
    quantum_toffoli(reg1, D11, OutReg, quReg);
    
}

void InvFirstDiagonalIsEmpty(int *q, int OutReg, quantum_reg *quReg)
{
    int reg0 = OutReg+1;
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    int D00 = q[0];
    int D01 = q[0]+1;
    int D10 = q[0]+2;
    int D11 = q[0]+3;
    
    quantum_toffoli(reg1, D11, OutReg, quReg);
    quantum_sigma_x(reg1, quReg);
    
    quantum_toffoli(D11, reg0, OutReg, quReg);
    quantum_sigma_x(reg0, quReg);
    quantum_sigma_x(D11, quReg);
    
    quantum_toffoli(D01, reg1, OutReg, quReg);
    quantum_toffoli(reg2, D11, OutReg, quReg);
    quantum_toffoli(D01,D10, reg2,quReg);
    quantum_sigma_x(D01, quReg);
    
    quantum_sigma_x(D10, quReg);
    quantum_toffoli(D00, D10, reg1, quReg);
    quantum_sigma_x(D10, quReg);
    quantum_sigma_x(D00, quReg);
    quantum_toffoli(D00, D01, reg0, quReg);
    
    //quantum_print_qureg(*quReg);
}

void CheckDiagonals(int OutReg, quantum_reg *quReg)
{
    int reg0 = OutReg+1;
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    int reg3 = OutReg+4;
    int reg5 = OutReg+5;
    int reg6 = OutReg+6;
    int reg7 = OutReg+7;
 
    FirstDiagonalIsEmpty(queen0, reg0, quReg);
    quantum_cnot(reg0, reg5, quReg);
    InvFirstDiagonalIsEmpty(queen0, reg0, quReg);
    
    FirstDiagonalIsEmpty(queen1, reg0, quReg);
    quantum_cnot(reg0, reg6, quReg);
    InvFirstDiagonalIsEmpty(queen1, reg0, quReg);
    
    FirstDiagonalIsEmpty(queen2, reg0, quReg);
    quantum_toffoli(reg0, reg5,reg7, quReg);
    quantum_toffoli(reg6, reg7, OutReg, quReg); //Main Symmetrie
    quantum_toffoli(reg0, reg5,reg7, quReg);
    InvFirstDiagonalIsEmpty(queen2, reg0, quReg);
    
    FirstDiagonalIsEmpty(queen1, reg0, quReg);
    quantum_cnot(reg0, reg6, quReg);
    InvFirstDiagonalIsEmpty(queen1, reg0, quReg);
    
    FirstDiagonalIsEmpty(queen0, reg0, quReg);
    quantum_cnot(reg0, reg5, quReg);
    InvFirstDiagonalIsEmpty(queen0, reg0, quReg);
    
}


void QueenCmp(int *qu0, int *qu1, int OutReg, quantum_reg *quReg)
{
    int reg0 = OutReg+1;
    
    //return 1 if queens are on different lines
    quantum_cnot(qu0[0], qu1[0], quReg);
    quantum_cnot(qu0[1], qu1[1], quReg);
    quantum_sigma_x(qu1[0], quReg);
    quantum_sigma_x(qu1[1], quReg);
    quantum_toffoli(qu1[0], qu1[1], reg0, quReg);
    quantum_sigma_x(reg0, quReg);
    quantum_cnot(reg0, OutReg, quReg);
    quantum_sigma_x(reg0, quReg);
    quantum_toffoli(qu1[0], qu1[1], reg0, quReg);
    quantum_sigma_x(qu1[1], quReg);
    quantum_sigma_x(qu1[0], quReg);
    quantum_cnot(qu0[1], qu1[1], quReg);
    quantum_cnot(qu0[0], qu1[0], quReg);
    
}

void CheckLines(int OutReg, quantum_reg *quReg)
{
    int reg0 = OutReg + 1;
    int reg1 = OutReg + 2;
    int reg2 = OutReg + 3;
    int reg3 = OutReg + 4;
    int reg4 = OutReg + 5;
    int reg5 = OutReg + 6;
    int reg6 = OutReg + 7;
    int reg7 = OutReg + 8;
    
    QueenCmp(queen0, queen1, reg0, quReg);
    QueenCmp(queen1, queen2, reg2, quReg);
    quantum_toffoli(reg0, reg2, reg4, quReg); //symetrie
    QueenCmp(queen1, queen2, reg2, quReg);
    QueenCmp(queen0, queen1, reg0, quReg);
    
    QueenCmp(queen0, queen2, reg0, quReg);
    QueenCmp(queen0, queen3, reg2, quReg);
    quantum_toffoli(reg0, reg2, reg5, quReg);
    QueenCmp(queen0, queen3, reg2, quReg);
    QueenCmp(queen0, queen2, reg0, quReg);
    
    QueenCmp(queen1, queen3, reg0, quReg);
    QueenCmp(queen2, queen3, reg2, quReg);
    quantum_toffoli(reg0, reg2, reg6, quReg);
    QueenCmp(queen2, queen3, reg2, quReg);
    QueenCmp(queen1, queen3, reg0, quReg);
    
    quantum_toffoli(reg4, reg5, reg7, quReg);
    quantum_toffoli(reg6, reg7, OutReg, quReg); // MAIN SYMMETRIE
    quantum_toffoli(reg4, reg5, reg7, quReg);
    
    QueenCmp(queen1, queen3, reg0, quReg);
    QueenCmp(queen2, queen3, reg2, quReg);
    quantum_toffoli(reg0, reg2, reg6, quReg);
    QueenCmp(queen2, queen3, reg2, quReg);
    QueenCmp(queen1, queen3, reg0, quReg);
    
    QueenCmp(queen0, queen2, reg0, quReg);
    QueenCmp(queen0, queen3, reg2, quReg);
    quantum_toffoli(reg0, reg2, reg5, quReg);
    QueenCmp(queen0, queen3, reg2, quReg);
    QueenCmp(queen0, queen2, reg0, quReg);
    
    QueenCmp(queen0, queen1, reg0, quReg);
    QueenCmp(queen1, queen2, reg2, quReg);
    quantum_toffoli(reg0, reg2, reg4, quReg); //symetrie
    QueenCmp(queen1, queen2, reg2, quReg);
    QueenCmp(queen0, queen1, reg0, quReg);

}

void Oracle(quantum_reg *quReg)
{
    CheckDiagonals(quRAM[0], quReg);
    quantum_cnot(quRAM[0], quRAM[9], quReg);
    CheckDiagonals(quRAM[0], quReg);
    
    CheckLines(quRAM[0], quReg);
    quantum_toffoli(quRAM[0], quRAM[9], quControlBit, quReg);
    CheckLines(quRAM[0], quReg);
    
    CheckDiagonals(quRAM[0], quReg);
    quantum_cnot(quRAM[0], quRAM[9], quReg);
    CheckDiagonals(quRAM[0], quReg);
    
}

void Inversion(quantum_reg *quReg)
{
    for (int i = 0; i< queenWidth; i++)
        quantum_hadamard(i, quReg);
    for (int i = 0; i< queenWidth; i++)
        quantum_sigma_x(i, quReg);
    
    quantum_toffoli(queen0[0], queen0[1], quRAM[0], quReg);
    quantum_toffoli(queen1[0], quRAM[0], quRAM[1], quReg);
    quantum_toffoli(queen1[1], quRAM[1], quRAM[2], quReg);
    quantum_toffoli(queen2[0], quRAM[2], quRAM[3], quReg);
    quantum_toffoli(queen2[1], quRAM[3], quRAM[4], quReg);
    quantum_toffoli(queen3[0], quRAM[4], quRAM[5], quReg);
    quantum_toffoli(queen3[1], quRAM[5], quRAM[6], quReg);
    
    quantum_cnot(quRAM[6], quControlBit, quReg);
    
    quantum_toffoli(queen3[1], quRAM[5], quRAM[6], quReg);
    quantum_toffoli(queen3[0], quRAM[4], quRAM[5], quReg);
    quantum_toffoli(queen2[1], quRAM[3], quRAM[4], quReg);
    quantum_toffoli(queen2[0], quRAM[2], quRAM[3], quReg);
    quantum_toffoli(queen1[1], quRAM[1], quRAM[2], quReg);
    quantum_toffoli(queen1[0], quRAM[0], quRAM[1], quReg);
    quantum_toffoli(queen0[0], queen0[1], quRAM[0], quReg);
    
    for (int i = 0; i< queenWidth; i++)
        quantum_sigma_x(i, quReg);
    for (int i = 0; i< queenWidth; i++)
        quantum_hadamard(i, quReg);
    
}

int main(int argc, const char * argv[])
{
    quantum_reg quReg;
    
    srand((unsigned int)clock()*100000);
    
    quReg = quantum_new_qureg(0, totalWidth);
    
    //superpose queens states
    for (int i = 0; i< queenWidth; i++)
        quantum_hadamard(i, &quReg);
    
    
    //initialize control bit
    quantum_sigma_x(quControlBit, &quReg);
    quantum_hadamard(quControlBit, &quReg);
    
    for (int i = 0; i< 8; i++) {
        Oracle(&quReg);
        Inversion(&quReg);
    }

    quantum_sigma_z(quControlBit, &quReg);
    quantum_hadamard(quControlBit, &quReg);
    
    quantum_print_qureg(quReg);
    
    int measured_value = quantum_measure(quReg);
    
    int returnVal = measured_value % 255;
    
    int Queens[4] = {returnVal % 4, (returnVal >> 2) % 4, (returnVal >> 4) % 4, (returnVal >> 6) % 4};
    
    printf("D0 : %d\nD1 : %d\nD2 : %d\nD3 : %d\n", Queens[0], Queens[1], Queens[2], Queens[3]);
    

    return 0;
}
