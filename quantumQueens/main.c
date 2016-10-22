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

const int queen0[3] = {0,1,2};
const int queen1[3] = {3,4,5};
const int queen2[3] = {6,7,8};
const int queen3[3] = {9,10,11};
const int queen4[3] = {12,13,14};
/*int queen5[3] = {15,16,17};
int queen6[3] = {18,19,20};
int queen7[3] = {21,22,23};
*/

const int queenWidth = 15;

const int nb_queens =  queenWidth/ 3;

const int quControlBit = 15;

const int quRAM = 16;

const int totalWidth = 48;



void QueenCmp(const int *qu0, const int *qu1, int OutReg, quantum_reg *quReg)
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

void InvQueenCmp(const int *qu0, const int *qu1, int OutReg, quantum_reg *quReg)
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

void QueensAreNotInDiagonal(const int *q0, const int* q1, int OutReg, int n, quantum_reg *quReg)
{
    //max depth = 6 + 8 = 14
    int reg0 = OutReg+1;
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    int reg4 = OutReg+5;
    int reg5 = OutReg+6;
    


    switch (n) {
        case 1:
            //(q0 != 7)
            quantum_toffoli(q0[0], q0[1], reg0, quReg);
            quantum_toffoli(q0[2], reg0, reg1, quReg);
            quantum_sigma_x(reg1, quReg);
            
            //add 1 to q0
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);
            break;
        case 2:
            //q0 < 6
                //quantum_print_qureg(*quReg);
            quantum_toffoli(q0[1], q0[2], reg1, quReg);
            quantum_sigma_x(reg1, quReg);
            
            //add 2 to q0
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);
            break;
        default:
            break;
    }

    //(q0 != n) & !(q0 +n != q1)
    QueenCmp(q0, q1, reg5, quReg);
    quantum_sigma_x(reg5, quReg);
    quantum_toffoli(reg5, reg1, reg2, quReg); //symetrie
    quantum_sigma_x(reg2, quReg);
    
    //rewind
    quantum_sigma_x(reg5, quReg);
    InvQueenCmp(q0, q1, reg5, quReg);
    
    switch(n) {
        case 1:
            //add one to q0
            quantum_sigma_x(q0[0], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            
            //(q0 != 7)
            quantum_sigma_x(reg1, quReg);
            quantum_toffoli(q0[2], reg0, reg1, quReg);
            quantum_toffoli(q0[0], q0[1], reg0, quReg);
            break;
        case 2:
            //add 2 to q0
            quantum_sigma_x(q0[0], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_sigma_x(q0[0], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            
            //q0 < 6
            quantum_toffoli(q0[1], q0[2], reg1, quReg);
            quantum_sigma_x(reg1, quReg);
            break;
        default:
            break;
    }

    //end rewind
    
    switch (n) {
        case 1:
            //(q0 != 0)
            quantum_sigma_x(q0[0], quReg);
            quantum_sigma_x(q0[1], quReg);
            quantum_sigma_x(q0[2], quReg);
            quantum_toffoli(q0[0], q0[1], reg0, quReg);
            quantum_toffoli(q0[2], reg0, reg1, quReg);
            quantum_sigma_x(reg1, quReg);
            quantum_sigma_x(q0[2], quReg);
            quantum_sigma_x(q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);
            
            //q0 = q0 - 1
            quantum_sigma_x(q0[0], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            break;
        case 2:
            //(q0 > 2)
            quantum_sigma_x(q0[1], quReg);
            quantum_sigma_x(q0[2], quReg);
            quantum_toffoli(q0[2], q0[1], reg1, quReg);
            quantum_sigma_x(reg1, quReg);
            quantum_sigma_x(q0[2], quReg);
            quantum_sigma_x(q0[1], quReg);
            
            //q0 = q0 - 2
            quantum_sigma_x(q0[0], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_sigma_x(q0[0], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            break;
            
    }

    
    //(q0 > n) & !(q0 -n != q1)
    QueenCmp(q0, q1, reg5, quReg);
    quantum_sigma_x(reg5, quReg);
    quantum_toffoli(reg1, reg5, reg4, quReg);
    quantum_sigma_x(reg5, quReg);
    quantum_sigma_x(reg4, quReg);
    
    //ni l'un ni l'autre
    quantum_toffoli(reg4, reg2, OutReg, quReg); // Main symetrie

    
    //main rewind
    //(q0 != 0) & (q0 -1 != q1)
    quantum_sigma_x(reg4, quReg);
    quantum_sigma_x(reg5, quReg);
    quantum_toffoli(reg1, reg5, reg4, quReg);
    quantum_sigma_x(reg5, quReg);
    InvQueenCmp(q0, q1, reg5, quReg);
    
    switch (n) {
        case 1:
            //q0 = q0 - 1
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);
            
            //(q0 != 0)
            quantum_sigma_x(q0[0], quReg);
            quantum_sigma_x(q0[1], quReg);
            quantum_sigma_x(q0[2], quReg);
            quantum_sigma_x(reg1, quReg);
            quantum_toffoli(q0[2], reg0, reg1, quReg);
            quantum_toffoli(q0[0], q0[1], reg0, quReg);
            quantum_sigma_x(q0[2], quReg);
            quantum_sigma_x(q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);

            break;
        case 2:
            //q0 = q0 - 2
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);
            
            //(q0 > 2)
            quantum_sigma_x(q0[1], quReg);
            quantum_sigma_x(q0[2], quReg);
            quantum_sigma_x(reg1, quReg);
            quantum_toffoli(q0[2], q0[1], reg1, quReg);
            quantum_sigma_x(q0[2], quReg);
            quantum_sigma_x(q0[1], quReg);
            break;
            
    }
    
    //end rewind
    
    switch (n) {
        case 1:
            //(q0 != 7)
            quantum_toffoli(q0[0], q0[1], reg0, quReg);
            quantum_toffoli(q0[2], reg0, reg1, quReg);
            quantum_sigma_x(reg1, quReg);
            
            //add 1 to q0
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);
            break;
        case 2:
            //q0 < 6
            quantum_sigma_x(reg1, quReg);
            quantum_toffoli(q0[1], q0[2], reg1, quReg);
            
            //add 2 to q0
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_sigma_x(q0[0], quReg);
            break;
        default:
            break;
    }
    
    //rewind
    //(q0 != 7) & (q0 +1 != q1)
    QueenCmp(q0, q1, reg5, quReg);
    quantum_sigma_x(reg5, quReg);
    quantum_sigma_x(reg2, quReg);
    quantum_toffoli(reg5, reg1, reg2, quReg); //symetrie
    quantum_sigma_x(reg5, quReg);
    InvQueenCmp(q0, q1, reg5, quReg);
    
    switch(n) {
        case 1:
            //add one to q0
            quantum_sigma_x(q0[0], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            
            //(q0 != 7)
            quantum_sigma_x(reg1, quReg);
            quantum_toffoli(q0[2], reg0, reg1, quReg);
            quantum_toffoli(q0[0], q0[1], reg0, quReg);
            break;
        case 2:
            //add 2 to q0
            quantum_sigma_x(q0[0], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            quantum_sigma_x(q0[0], quReg);
            quantum_cnot(q0[0], q0[1], quReg);
            quantum_toffoli(q0[0], q0[1], q0[2], quReg);
            
            //q0 < 6
            quantum_sigma_x(reg1, quReg);
            quantum_toffoli(q0[1], q0[2], reg1, quReg);

            break;
        default:
            break;
    }
}

void CheckDiagonals(int OutReg, quantum_reg *quReg)
{
    int reg0 = OutReg+1;
    int reg1 = OutReg+16;
    int reg2 = OutReg+17;
    int reg3 = OutReg+18;
    
    
    QueensAreNotInDiagonal(queen0, queen1, reg0, 1, quReg);
    quantum_cnot(reg0, reg1, quReg);

    QueensAreNotInDiagonal(queen0, queen1, reg0, 1, quReg);
    
    QueensAreNotInDiagonal(queen1, queen2, reg0, 1, quReg);
    quantum_toffoli(reg0, reg1, reg2, quReg);
    QueensAreNotInDiagonal(queen1, queen2, reg0, 1, quReg);
    
    QueensAreNotInDiagonal(queen2, queen3, reg0, 1, quReg);
    quantum_toffoli(reg0, reg2, reg3, quReg);
    QueensAreNotInDiagonal(queen2, queen3, reg0, 1, quReg);
    
    QueensAreNotInDiagonal(queen3, queen4, reg0, 1, quReg);
    quantum_toffoli(reg0, reg3, OutReg, quReg);             //MAIN symetrie
    QueensAreNotInDiagonal(queen3, queen4, reg0, 1, quReg);
    
    QueensAreNotInDiagonal(queen2, queen3, reg0, 1, quReg);
    quantum_toffoli(reg0, reg2, reg3, quReg);
    QueensAreNotInDiagonal(queen2, queen3, reg0, 1, quReg);
    
    QueensAreNotInDiagonal(queen1, queen2, reg0, 1, quReg);
    quantum_toffoli(reg0, reg1, reg2, quReg);
    QueensAreNotInDiagonal(queen1, queen2, reg0, 1, quReg);
    
    QueensAreNotInDiagonal(queen0, queen1, reg0, 1, quReg);
    quantum_cnot(reg0, reg1, quReg);
    QueensAreNotInDiagonal(queen0, queen1, reg0, 1, quReg);
    
}

void Check2ndDiagonal(int OutReg, quantum_reg *quReg)
{
    int reg0 = OutReg+1;
    int reg1 = OutReg+16;
    int reg2 = OutReg+17;
    
    
    QueensAreNotInDiagonal(queen0, queen2, reg0, 2, quReg);
    quantum_cnot(reg0, reg1, quReg);
    QueensAreNotInDiagonal(queen0, queen2, reg0, 2, quReg);
    
    QueensAreNotInDiagonal(queen1, queen3, reg0, 2, quReg);
    quantum_toffoli(reg0, reg1, reg2, quReg);
    QueensAreNotInDiagonal(queen1, queen3, reg0, 2, quReg);
    
    QueensAreNotInDiagonal(queen2, queen4, reg0, 2, quReg);
    quantum_toffoli(reg0, reg2, OutReg, quReg);                   //MAIN Symetrie
    QueensAreNotInDiagonal(queen2, queen4, reg0, 2, quReg);
    
    QueensAreNotInDiagonal(queen1, queen3, reg0, 2, quReg);
    quantum_toffoli(reg0, reg1, reg2, quReg);
    QueensAreNotInDiagonal(queen1, queen3, reg0, 2, quReg);
    
    QueensAreNotInDiagonal(queen0, queen2, reg0, 2, quReg);
    quantum_cnot(reg0, reg1, quReg);
    QueensAreNotInDiagonal(queen0, queen2, reg0, 2, quReg);
    
}

void CheckAllLinesForQueen(const int *q, int OutReg, quantum_reg *quReg)
{
    //max depth = nb queens + 11
    const int *queens[nb_queens] = {queen0, queen1, queen2, queen3, queen4};
    
    int reg0 = OutReg + 1;
    int reg1 = OutReg + 11;
    int i;
    
    quantum_sigma_x(reg1, quReg);
    
    for (i = 0; i<nb_queens; i++) {
        reg1 = reg1-1;
        if (queens[i] != q) {
            reg1=reg1+1;
            QueenCmp(q, queens[i], reg0, quReg);
            quantum_toffoli(reg0, reg1+i, reg1+i+1, quReg); //symetrie
            InvQueenCmp(q, queens[i], reg0, quReg);
        }
    }
    
    quantum_cnot(reg1+i, OutReg, quReg); //symetrie
    
    for (i = nb_queens-1; i>=0; i--) {
        reg1 = reg1 + 1;
        if (queens[i] != q) {
            reg1 = reg1 - 1;
            QueenCmp(q, queens[i], reg0, quReg);
            quantum_toffoli(reg0, reg1+i, reg1+i+1, quReg); //symetrie
            InvQueenCmp(q, queens[i], reg0, quReg);
        }
    }
    
    quantum_sigma_x(reg1, quReg);
}

void CheckLines(int OutReg, quantum_reg *quReg)
{
    //depth = nb_queens + 17
    const int *queens[nb_queens] = {queen0, queen1, queen2, queen3, queen4};
    int i;
    int reg0 = OutReg+1;
    int reg1 = OutReg+17;
    
    quantum_sigma_x(reg1, quReg);
    
    for (i = 0; i<nb_queens; i++) {
        CheckAllLinesForQueen(queens[i], reg0, quReg);
        quantum_toffoli(reg0, reg1+i, reg1+i+1, quReg);
        CheckAllLinesForQueen(queens[i], reg0, quReg);
    }
    
    quantum_cnot(reg1+i, OutReg, quReg);
    
    
    for (i =nb_queens-1; i>=0; i--) {
        CheckAllLinesForQueen(queens[i], reg0, quReg);
        quantum_toffoli(reg0, reg1+i, reg1+i+1, quReg);
        CheckAllLinesForQueen(queens[i], reg0, quReg);
    }
    
    quantum_sigma_x(reg1, quReg);

}

void CheckLimit(int OutReg, quantum_reg *quReg) {
    const int *queens[5] = {queen0, queen1, queen2, queen3, queen4};
    int i;
    int reg0 = OutReg+1;
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    
    
    quantum_sigma_x(reg2, quReg);
    
    for (i = 0; i< nb_queens; i++) {
        quantum_sigma_x(queens[i][1], quReg);
        quantum_sigma_x(queens[i][0], quReg);
        quantum_toffoli(queens[i][0], queens[i][2], reg0, quReg);
        quantum_toffoli(queens[i][1], reg0, reg1, quReg);
        quantum_sigma_x(queens[i][2], quReg);
        quantum_cnot(queens[i][2], reg1, quReg);
        quantum_toffoli(reg1, reg2+i, reg2+i+1, quReg);
        quantum_cnot(queens[i][2], reg1, quReg);
        quantum_sigma_x(queens[i][2], quReg);
        quantum_toffoli(queens[i][1], reg0, reg1, quReg);
        quantum_toffoli(queens[i][0], queens[i][2], reg0, quReg);
        quantum_sigma_x(queens[i][0], quReg);
        quantum_sigma_x(queens[i][1], quReg);
        
    }
    
    quantum_cnot(reg2+i, OutReg, quReg);
    
    for (i = nb_queens-1; i>=0; i--) {
        quantum_sigma_x(queens[i][1], quReg);
        quantum_sigma_x(queens[i][0], quReg);
        quantum_toffoli(queens[i][0], queens[i][2], reg0, quReg);
        quantum_toffoli(queens[i][1], reg0, reg1, quReg);
        quantum_sigma_x(queens[i][2], quReg);
        quantum_cnot(queens[i][2], reg1, quReg);
        quantum_toffoli(reg1, reg2+i, reg2+i+1, quReg);
        quantum_cnot(queens[i][2], reg1, quReg);
        quantum_sigma_x(queens[i][2], quReg);
        quantum_toffoli(queens[i][1], reg0, reg1, quReg);
        quantum_toffoli(queens[i][0], queens[i][2], reg0, quReg);
        quantum_sigma_x(queens[i][0], quReg);
        quantum_sigma_x(queens[i][1], quReg);
        
    }
    
    quantum_sigma_x(reg2, quReg);
}

void Oracle(quantum_reg *quReg)
{
    int reg0 = quRAM;
    int reg1 = quRAM+29;
    int reg2 = quRAM+30;
    int reg3 = quRAM+31;
    
    CheckLines(reg0, quReg);
    quantum_cnot(reg0, reg1, quReg);
    CheckLines(reg0, quReg);
    
    CheckDiagonals(reg0, quReg);
    quantum_toffoli(reg0, reg1, reg2, quReg);
    CheckDiagonals(reg0, quReg);
    
    Check2ndDiagonal(reg0, quReg);
    quantum_toffoli(reg0, reg2, reg3, quReg);
    Check2ndDiagonal(reg0, quReg);
    
    CheckLimit(reg0, quReg);
    quantum_toffoli(reg0, reg3, quControlBit, quReg);
    CheckLimit(reg0, quReg);
    
    Check2ndDiagonal(reg0, quReg);
    quantum_toffoli(reg0, reg2, reg3, quReg);
    Check2ndDiagonal(reg0, quReg);
    
    CheckDiagonals(reg0, quReg);
    quantum_toffoli(reg0, reg1, reg2, quReg);
    CheckDiagonals(reg0, quReg);

    
    CheckLines(reg0, quReg);
    quantum_cnot(reg0, reg1, quReg);
    CheckLines(reg0, quReg);

}

void Inversion(quantum_reg *quReg)
{
    int i = 0;
    
    for (int i = 0; i< queenWidth; i++)
        quantum_hadamard(i, quReg);
    for (int i = 0; i< queenWidth; i++)
        quantum_sigma_x(i, quReg);
    
    quantum_sigma_x(quRAM, quReg);
    
    for (i = 0; i< queenWidth; i++) {
        quantum_toffoli(queen0[0] + i, quRAM+i, quRAM+i+1, quReg);
    }

    quantum_cnot(quRAM+i, quControlBit, quReg);
    
    for (i = queenWidth - 1; i >=0; i--) {
        quantum_toffoli(queen0[0] + i, quRAM+i, quRAM+i+1, quReg);
    }
    
    quantum_sigma_x(quRAM, quReg);
    
    for (int i = 0; i< queenWidth; i++)
        quantum_sigma_x(i, quReg);
    for (int i = 0; i< queenWidth; i++)
        quantum_hadamard(i, quReg);
    
}

void printQueensFromState(unsigned long long state) {
    
    
    int Queens[nb_queens] = {state % 8, (state >> 3) % 8, (state >> 6) % 8, (state >> 9) % 8, (state >> 12) % 8};

    for (int i = 0; i< nb_queens; i++) {
        printf("\n|");
        for (int j = 0; j<nb_queens; j++) {
            if (Queens[j] == 4-i) {
                printf("x|");
            }
            else {
                printf(" |");
            }
        }
    }
    printf("\n");
}
unsigned long long quantum_max_proba_state (quantum_reg quReg) {
    
    double maxProba = 0.0;
    int maxProbaIndex=0;
    for (int index=0; index < quReg.size; index++) {
        double proba = 0.0;
        proba = quantum_prob(quReg.amplitude[index])*2.0;
        if (proba > maxProba) {
            maxProbaIndex = index;
            maxProba = proba;
        }
    }
    printf("cheating DeltaP = %.15f\n", maxProba - quantum_prob(quReg.amplitude[0]*2.0));
    
    return quReg.state[maxProbaIndex];

}


int main(int argc, const char * argv[])
{
    //cheat code, do not use grover algorithm till the end, read directly the max probability after 1 passes (gain for 5 queens : 2m40 -> 2s40)
    int cheat_code_active = 0;
    
    if( argc == 2 ) {
        printf("cheat code activated\n");
        cheat_code_active = 1;
    }
    
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
    
    int order=1;
    if (!cheat_code_active)
        order = 43;
    
    for (int i = 0; i< order; i++) {
        Oracle(&quReg);
        Inversion(&quReg);
    }

    quantum_sigma_z(quControlBit, &quReg);
    quantum_hadamard(quControlBit, &quReg);
    
    unsigned long long returnVal = 0;
    
    if (cheat_code_active)
        returnVal = quantum_max_proba_state(quReg);
    else
        returnVal = quantum_measure(quReg);
    
    quantum_delete_qureg(&quReg);
    
    printQueensFromState(returnVal);
    
    return 0;
}

