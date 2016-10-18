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


int queen0[3] = {0,1,2};
int queen1[3] = {3,4,5};
int queen2[3] = {6,7,8};
int queen3[3] = {9,10,11};
int queen4[3] = {12,13,14};
/*int queen5[3] = {15,16,17};
int queen6[3] = {18,19,20};
int queen7[3] = {21,22,23};
*/
int queenWidth = 15;

int quControlBit = 15;

int quRAM[29] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44};


int totalWidth = 45;

#ifdef M_PI@
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
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    int reg3 = OutReg+4;
    int reg4 = OutReg+5;
    int reg5 = OutReg+6;
    int reg6 = OutReg+7;
    int reg7 = OutReg+8;
    

    //2 first gates 1,2
    quantum_sigma_x(qu0[1], quReg);
    quantum_sigma_x(qu1[0], quReg);
    quantum_toffoli(qu0[1], qu1[0], reg0, quReg);
    quantum_sigma_x(qu1[0], quReg);
    quantum_toffoli(qu0[0], qu0[1], reg1, quReg);
    quantum_sigma_x(qu0[1], quReg);
    
    //next gate 3
    quantum_toffoli(qu0[0], qu0[1], reg2, quReg);
    
    //2 next gates 4,5
    quantum_sigma_x(qu0[0], quReg);
    quantum_toffoli(qu0[0], qu1[1], reg3, quReg);
    quantum_sigma_x(qu0[2], quReg);
    quantum_toffoli(qu0[0], qu0[2], reg4, quReg);
    quantum_sigma_x(qu0[2], quReg);
    quantum_sigma_x(qu0[0], quReg);
    
    //3 next gates 6,7,8
    quantum_toffoli(qu1[1], qu1[0], reg5, quReg);
    quantum_toffoli(qu1[0], qu0[2], reg6, quReg);
    quantum_toffoli(qu0[2], qu0[1], reg7, quReg);

    //start rewinding registers 9
    quantum_sigma_x(qu1[0], quReg);
    quantum_toffoli(qu1[0], reg7, OutReg, quReg);
    quantum_sigma_x(qu1[0], quReg);
    

    
    //next rewind 10
    quantum_sigma_x(qu0[2], quReg);
    quantum_toffoli(reg2, qu0[2], OutReg, quReg);
    quantum_sigma_x(qu0[2], quReg);

    
    //11
    quantum_sigma_x(qu1[1], quReg);
    quantum_sigma_x(reg4, quReg);
    quantum_toffoli(qu1[1], reg4, OutReg, quReg);

    
    //12
    quantum_sigma_x(reg6, quReg);
    quantum_toffoli(qu1[1], reg6, OutReg, quReg);
    quantum_sigma_x(qu1[1], quReg);

    
    //13
    quantum_sigma_x(qu1[2], quReg);
    quantum_sigma_x(reg5, quReg);
    quantum_toffoli(qu1[2], reg5, OutReg, quReg);
    quantum_sigma_x(qu1[2], quReg);

    
    //14
    quantum_sigma_x(reg1, quReg);
    quantum_toffoli(qu1[2], reg1, OutReg, quReg);


    
    //15
    quantum_sigma_x(reg0, quReg);
    quantum_sigma_x(qu1[2], quReg);
    quantum_toffoli(qu1[2], reg0, OutReg, quReg);
    quantum_sigma_x(qu1[2], quReg);
    
    //16
    quantum_sigma_x(reg3, quReg);
    quantum_toffoli(reg3, qu1[2], OutReg, quReg);
}

void InvQueenCmp(int *qu0, int *qu1, int OutReg, quantum_reg *quReg)
{
    int reg0 = OutReg+1;
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    int reg3 = OutReg+4;
    int reg4 = OutReg+5;
    int reg5 = OutReg+6;
    int reg6 = OutReg+7;
    int reg7 = OutReg+8;
 
    //16
    quantum_toffoli(reg3, qu1[2], OutReg, quReg);
    quantum_sigma_x(reg3, quReg);
    
    //15
    quantum_sigma_x(qu1[2], quReg);
    quantum_toffoli(qu1[2], reg0, OutReg, quReg);
    quantum_sigma_x(qu1[2], quReg);
    quantum_sigma_x(reg0, quReg);
    
    //14
    quantum_toffoli(qu1[2], reg1, OutReg, quReg);
    quantum_sigma_x(reg1, quReg);
    

    
    //13
    quantum_sigma_x(qu1[2], quReg);
    quantum_toffoli(qu1[2], reg5, OutReg, quReg);
    quantum_sigma_x(reg5, quReg);
    quantum_sigma_x(qu1[2], quReg);

    
    //12
    quantum_sigma_x(qu1[1], quReg);
    quantum_toffoli(qu1[1], reg6, OutReg, quReg);
    quantum_sigma_x(reg6, quReg);

    
    //11
    quantum_toffoli(qu1[1], reg4, OutReg, quReg);
    quantum_sigma_x(reg4, quReg);
    quantum_sigma_x(qu1[1], quReg);
    

    
    //next rewind 10
    quantum_sigma_x(qu0[2], quReg);
    quantum_toffoli(reg2, qu0[2], OutReg, quReg);
    quantum_sigma_x(qu0[2], quReg);
    

    
    //start rewinding registers 9
    quantum_sigma_x(qu1[0], quReg);
    quantum_toffoli(qu1[0], reg7, OutReg, quReg);
    quantum_sigma_x(qu1[0], quReg);

    //3 next gates 6,7,8
    quantum_toffoli(qu0[2], qu0[1], reg7, quReg);
    quantum_toffoli(qu1[0], qu0[2], reg6, quReg);
    quantum_toffoli(qu1[1], qu1[0], reg5, quReg);
    
    //2 next gates 4,5
    quantum_sigma_x(qu0[0], quReg);
    quantum_sigma_x(qu0[2], quReg);
    quantum_toffoli(qu0[0], qu0[2], reg4, quReg);
    quantum_sigma_x(qu0[2], quReg);
    quantum_toffoli(qu0[0], qu1[1], reg3, quReg);
    quantum_sigma_x(qu0[0], quReg);
    
    //next gate 3
    quantum_toffoli(qu0[0], qu0[1], reg2, quReg);

    //2 first gates 1,2
    quantum_sigma_x(qu0[1], quReg);
    quantum_toffoli(qu0[0], qu0[1], reg1, quReg);
    quantum_sigma_x(qu1[0], quReg);
    quantum_toffoli(qu0[1], qu1[0], reg0, quReg);
    quantum_sigma_x(qu1[0], quReg);
    quantum_sigma_x(qu0[1], quReg);
    
}

void Check4Lines(int *qu0, int *qu1, int *qu2, int *qu3, int OutReg, quantum_reg *quReg)
{
    
    int reg0 = OutReg + 1;
    int reg10 = OutReg + 10;
    
    int reg18 = OutReg + 19;
    int reg19 = OutReg + 20;
    int reg20 = OutReg + 21;
    int reg21 = OutReg + 22;
    int reg22 = OutReg + 23;
    int reg23 = OutReg + 24;
    
    //quantum_print_qureg(*quReg);
    
    QueenCmp(qu0, qu1, reg0, quReg);
    QueenCmp(qu1, qu2, reg10, quReg);
    quantum_toffoli(reg0, reg10, reg18, quReg); //symetrie
    InvQueenCmp(qu1, qu2, reg10, quReg);
    InvQueenCmp(qu0, qu1, reg0, quReg);
    
    QueenCmp(qu0, qu2, reg0, quReg);
    QueenCmp(qu0, qu3, reg10, quReg);
    quantum_toffoli(reg0, reg10, reg19, quReg);
    InvQueenCmp(qu0, qu3, reg10, quReg);
    InvQueenCmp(qu0, qu2, reg0, quReg);
    
    QueenCmp(qu1, qu3, reg0, quReg);
    QueenCmp(qu2, qu3, reg10, quReg);
    quantum_toffoli(reg0, reg10, reg20, quReg);
    InvQueenCmp(qu2, qu3, reg10, quReg);
    InvQueenCmp(qu1, qu3, reg0, quReg);
    
    quantum_toffoli(reg18, reg19, reg21, quReg);
    quantum_toffoli(reg20, reg21, OutReg, quReg); // MAIN SYMMETRIE
    quantum_toffoli(reg18, reg19, reg21, quReg);
    
    QueenCmp(qu1, qu3, reg0, quReg);
    QueenCmp(qu2, qu3, reg10, quReg);
    quantum_toffoli(reg0, reg10, reg20, quReg);
    InvQueenCmp(qu2, qu3, reg10, quReg);
    InvQueenCmp(qu1, qu3, reg0, quReg);
    
    QueenCmp(qu0, qu2, reg0, quReg);
    QueenCmp(qu0, qu3, reg10, quReg);
    quantum_toffoli(reg0, reg10, reg19, quReg);
    InvQueenCmp(qu0, qu3, reg10, quReg);
    InvQueenCmp(qu0, qu2, reg0, quReg);
    
    QueenCmp(qu0, qu1, reg0, quReg);
    QueenCmp(qu1, qu2, reg10, quReg);
    quantum_toffoli(reg0, reg10, reg18, quReg); //symetrie
    InvQueenCmp(qu1, qu2, reg10, quReg);
    InvQueenCmp(qu0, qu1, reg0, quReg);

    //quantum_print_qureg(*quReg);
}

void CheckLines(int OutReg, quantum_reg *quReg)
{
    int reg0 = OutReg+1;
    int reg25 = OutReg+26;
    int reg26 = OutReg+27;
    
    
    //quantum_print_qureg(*quReg);
    Check4Lines(queen0, queen1, queen2, queen3, reg0, quReg);
    quantum_cnot(reg0, reg25, quReg);
    Check4Lines(queen0, queen1, queen2, queen3, reg0, quReg);
    
    Check4Lines(queen4, queen1, queen2, queen3, reg0, quReg);
    quantum_cnot(reg0, reg26, quReg);
    Check4Lines(queen4, queen1, queen2, queen3, reg0, quReg);
    
    quantum_toffoli(reg25, reg26, OutReg,  quReg);                   //MainSymetrie
    
    Check4Lines(queen4, queen1, queen2, queen3, reg0, quReg);
    quantum_cnot(reg0, reg26, quReg);
    Check4Lines(queen4, queen1, queen2, queen3, reg0, quReg);
    
    Check4Lines(queen0, queen1, queen2, queen3, reg0, quReg);
    quantum_cnot(reg0, reg25, quReg);
    Check4Lines(queen0, queen1, queen2, queen3, reg0, quReg);
    
    //quantum_print_qureg(*quReg);
    
}

void Oracle(quantum_reg *quReg)
{
    /*CheckDiagonals(quRAM[0], quReg);
    quantum_cnot(quRAM[0], quRAM[9], quReg);
    CheckDiagonals(quRAM[0], quReg);
    */
    //quantum_print_qureg(*quReg);
    CheckLines(quRAM[0], quReg);
    //quantum_toffoli(quRAM[0], quRAM[9], quControlBit, quReg);
    quantum_cnot(quRAM[0], quControlBit, quReg);
    CheckLines(quRAM[0], quReg);
    
    //quantum_print_qureg(*quReg);
    //quantum_print_qureg(*quReg);
    /*
    CheckDiagonals(quRAM[0], quReg);
    quantum_cnot(quRAM[0], quRAM[9], quReg);
    CheckDiagonals(quRAM[0], quReg);
    */
}

void Inversion(quantum_reg *quReg)
{
    for (int i = 0; i< queenWidth; i++)
        quantum_hadamard(i, quReg);
    for (int i = 0; i< queenWidth; i++)
        quantum_sigma_x(i, quReg);
    
    quantum_toffoli(queen0[0], queen0[1], quRAM[0], quReg);
    quantum_toffoli(queen0[2], quRAM[0], quRAM[1], quReg);
    quantum_toffoli(queen1[0], quRAM[1], quRAM[2], quReg);
    quantum_toffoli(queen1[1], quRAM[2], quRAM[3], quReg);
    quantum_toffoli(queen1[2], quRAM[3], quRAM[4], quReg);
    quantum_toffoli(queen2[0], quRAM[4], quRAM[5], quReg);
    quantum_toffoli(queen2[1], quRAM[5], quRAM[6], quReg);
    quantum_toffoli(queen2[2], quRAM[6], quRAM[7], quReg);
    quantum_toffoli(queen3[0], quRAM[7], quRAM[8], quReg);
    quantum_toffoli(queen3[1], quRAM[8], quRAM[9], quReg);
    quantum_toffoli(queen3[2], quRAM[9], quRAM[10], quReg);
    
    
    quantum_cnot(quRAM[10], quControlBit, quReg);
    
    quantum_toffoli(queen3[2], quRAM[9], quRAM[10], quReg);
    quantum_toffoli(queen3[1], quRAM[8], quRAM[9], quReg);
    quantum_toffoli(queen3[0], quRAM[7], quRAM[8], quReg);
    quantum_toffoli(queen2[2], quRAM[6], quRAM[7], quReg);
    quantum_toffoli(queen2[1], quRAM[5], quRAM[6], quReg);
    quantum_toffoli(queen2[0], quRAM[4], quRAM[5], quReg);
    quantum_toffoli(queen1[2], quRAM[3], quRAM[4], quReg);
    quantum_toffoli(queen1[1], quRAM[2], quRAM[3], quReg);
    quantum_toffoli(queen1[0], quRAM[1], quRAM[2], quReg);
    quantum_toffoli(queen0[2], quRAM[0], quRAM[1], quReg);
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
    
    quReg = quantum_new_qureg(0, queenWidth);
    quantum_addscratch(totalWidth-queenWidth, &quReg);
    
    //superpose queens states
    for (int i = 0; i< queenWidth; i++)
        quantum_hadamard(i, &quReg);
    
    //initialize control bit
    quantum_sigma_x(quControlBit, &quReg);
    quantum_hadamard(quControlBit, &quReg);
    
    for (int i = 0; i< 4; i++) {
        Oracle(&quReg);
        Inversion(&quReg);
    }

    quantum_sigma_z(quControlBit, &quReg);
    quantum_hadamard(quControlBit, &quReg);
    
    quantum_print_qureg(quReg);
    
    int measured_value = quantum_measure(quReg);
    
    
    int returnVal = measured_value;
    
    printf("%d, \n",returnVal, measured_value);
    
    int Queens[5] = {returnVal % 8, (returnVal >> 3) % 8, (returnVal >> 6) % 8, (returnVal >> 9) % 8, (returnVal >> 12) % 8};
    
    printf("D0 : %d\nD1 : %d\nD2 : %d\nD3 : %d\nD4 : %d\n", Queens[0], Queens[1], Queens[2], Queens[3], Queens[4]);
    

    return 0;
}
