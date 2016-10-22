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
const int queen5[3] = {15,16,17};
int queen6[3] = {18,19,20};
int queen7[3] = {21,22,23};


const int queenWidth = 24;
int nb_queens =  queenWidth/ 3;
const int *queens[queenWidth/ 3] = {queen0, queen1, queen2, queen3, queen4, queen5, queen6, queen7};

const int quControlBit = queenWidth;

const int quRAM = quControlBit+1;




int QueenCmp(const int *qu0, const int *qu1, int OutReg, int simulate, quantum_reg *quReg)
{
    int depth = 8;
    int reg0 = OutReg+1;
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    int reg3 = OutReg+4;
    int reg4 = OutReg+5;
    int reg5 = OutReg+6;
    int reg6 = OutReg+7;
    int reg7 = OutReg+8;
    
    
    if (simulate)
        return depth+1;
    
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
    
    return depth+1;
}

int InvQueenCmp(const int *qu0, const int *qu1, int OutReg, int simulate, quantum_reg *quReg)
{
    int depth = 8;
    int reg0 = OutReg+1;
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    int reg3 = OutReg+4;
    int reg4 = OutReg+5;
    int reg5 = OutReg+6;
    int reg6 = OutReg+7;
    int reg7 = OutReg+8;
    
    if (simulate)
        return depth+1;
    
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
    
    return depth+1;
}

int QueensAreNotInDiagonal(const int *q0, const int* q1, int OutReg, int n, int simulate, quantum_reg *quReg)
{
    int depth = 14;
    int reg0 = OutReg+1;
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    int reg4 = OutReg+5;
    int reg5 = OutReg+6;
    
    if (simulate)
        return depth+1;


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
            printf("order not supported");
            exit(-1);
            break;
    }

    //(q0 != n) & !(q0 +n != q1)
    QueenCmp(q0, q1, reg5, 0, quReg);
    quantum_sigma_x(reg5, quReg);
    quantum_toffoli(reg5, reg1, reg2, quReg); //symetrie
    quantum_sigma_x(reg2, quReg);
    
    //rewind
    quantum_sigma_x(reg5, quReg);
    InvQueenCmp(q0, q1, reg5, 0, quReg);
    
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
    QueenCmp(q0, q1, reg5, 0, quReg);
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
    InvQueenCmp(q0, q1, reg5, 0, quReg);
    
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
    QueenCmp(q0, q1, reg5, 0, quReg);
    quantum_sigma_x(reg5, quReg);
    quantum_sigma_x(reg2, quReg);
    quantum_toffoli(reg5, reg1, reg2, quReg); //symetrie
    quantum_sigma_x(reg5, quReg);
    InvQueenCmp(q0, q1, reg5, 0, quReg);
    
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
    
    return depth+1;
}

int CheckDiagonals(int OutReg, int order, quantum_reg *quReg)
{
    int depth = 0;
    int i = 0;
    int reg0 = OutReg+1;
    int maxDepth =     QueensAreNotInDiagonal(queens[0], queens[order], reg0, order, 1, quReg);
    QueensAreNotInDiagonal(queens[0], queens[order], reg0, order, 1, quReg);
    
    int reg1 = OutReg+maxDepth+1;
    
    quantum_sigma_x(reg1, quReg);
    
    for (i = 0; i< nb_queens-order; i++) {
        
        QueensAreNotInDiagonal(queens[i], queens[i+order], reg0, order, 0, quReg);
        quantum_toffoli(reg0, reg1+i, reg1+i+1, quReg);
        QueensAreNotInDiagonal(queens[i], queens[i+order], reg0, order, 0, quReg);
    }
    
    depth = reg1+i-OutReg;
    quantum_cnot(reg1+i, OutReg, quReg); //MAIN symetrie
    
    for (i = nb_queens - order -1; i>=0; i--) {
        
        QueensAreNotInDiagonal(queens[i], queens[i+order], reg0, order, 0, quReg);
        quantum_toffoli(reg0, reg1+i, reg1+i+1, quReg);
        QueensAreNotInDiagonal(queens[i], queens[i+order], reg0, order, 0, quReg);
    }
    quantum_sigma_x(reg1, quReg);
    
    return depth+1;
}

int CheckAllLinesForQueen(const int *q, int OutReg, int simulate, quantum_reg *quReg)
{
    //max depth = nb queens + 11
    int depth = 0;
    int reg0 = OutReg + 1;
    int i=0;
    int maxDepth = QueenCmp(q, queens[0], reg0, 1, quReg);
    InvQueenCmp(q, queens[0], reg0, 1, quReg);
    
    int reg1 = OutReg+maxDepth + 1;
    
    if (simulate)
        return nb_queens+maxDepth;
    
    quantum_sigma_x(reg1, quReg);
    
    for (i = 0; i<nb_queens; i++) {
        reg1 = reg1-1;
        if (queens[i] != q) {
            reg1=reg1+1;
            QueenCmp(q, queens[i], reg0, 0, quReg);
            quantum_toffoli(reg0, reg1+i, reg1+i+1, quReg); //symetrie
            InvQueenCmp(q, queens[i], reg0, 0, quReg);
        }
    }
    depth = reg1+i-OutReg;
    quantum_cnot(reg1+i, OutReg, quReg); //symetrie
    
    for (i = nb_queens-1; i>=0; i--) {
        reg1 = reg1 + 1;
        if (queens[i] != q) {
            reg1 = reg1 - 1;
            QueenCmp(q, queens[i], reg0, 0, quReg);
            quantum_toffoli(reg0, reg1+i, reg1+i+1, quReg); //symetrie
            InvQueenCmp(q, queens[i], reg0, 0, quReg);
        }
    }
    
    quantum_sigma_x(reg1, quReg);
    
    return depth+1;
}

int CheckLines(int OutReg, quantum_reg *quReg)
{
    //depth = nb_queens + 17
    int depth = 0;
    int i=0;
    int reg0 = OutReg+1;
    int maxDepth = CheckAllLinesForQueen(queens[0], reg0, 1, quReg);
    CheckAllLinesForQueen(queens[0], reg0, 1, quReg);

    int reg1 = OutReg+maxDepth+2;
    
    quantum_sigma_x(reg1, quReg);
    
    for (i = 0; i<nb_queens; i++) {
        CheckAllLinesForQueen(queens[i], reg0, 0, quReg);
        quantum_toffoli(reg0, reg1+i, reg1+i+1, quReg);
        CheckAllLinesForQueen(queens[i], reg0, 0, quReg);
    }
    depth = reg1+i - OutReg;
    quantum_cnot(reg1+i, OutReg, quReg);
    
    
    for (i =nb_queens-1; i>=0; i--) {
        CheckAllLinesForQueen(queens[i], reg0, 0, quReg);
        quantum_toffoli(reg0, reg1+i, reg1+i+1, quReg);
        CheckAllLinesForQueen(queens[i], reg0, 0, quReg);
    }
    
    quantum_sigma_x(reg1, quReg);

    return depth+1;
}

int CheckLimit(int OutReg, int order, quantum_reg *quReg) {
    
    int depth=0;
    int i;
    int reg0 = OutReg+1;
    int reg1 = OutReg+2;
    int reg2 = OutReg+3;
    
    //quantum_print_qureg(*quReg);
    
    quantum_sigma_x(reg2, quReg);
    
    for (i = 0; i< nb_queens; i++) {
        if (order == 4) {
            quantum_sigma_x(queens[i][2], quReg);
            quantum_toffoli(queens[i][2], reg2+i, reg2+i+1, quReg);
        } else if (order == 5) {
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
        } else if (order == 6) {
            quantum_toffoli(queens[i][2], queens[i][1], reg0, quReg);
            quantum_sigma_x(reg0, quReg);
            quantum_toffoli(reg0, reg2+i, reg2+i+1, quReg);
            quantum_sigma_x(reg0, quReg);
            quantum_toffoli(queens[i][2], queens[i][1], reg0, quReg);
        }
        
    }
    depth = reg2+i - OutReg;
    
    quantum_cnot(reg2+i, OutReg, quReg);
    //quantum_print_qureg(*quReg);
    
    for (i = nb_queens-1; i>=0; i--) {
        if (order == 4) {
            quantum_toffoli(queens[i][2], reg2+i, reg2+i+1, quReg);
            quantum_sigma_x(queens[i][2], quReg);
        } else if (order == 5) {
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
        } else if (order == 6) {
            quantum_toffoli(queens[i][2], queens[i][1], reg0, quReg);
            quantum_sigma_x(reg0, quReg);
            quantum_toffoli(reg0, reg2+i, reg2+i+1, quReg);
            quantum_sigma_x(reg0, quReg);
            quantum_toffoli(queens[i][2], queens[i][1], reg0, quReg);

        }
        
    }
    
    quantum_sigma_x(reg2, quReg);
    
    //quantum_print_qureg(*quReg);
    
    return depth+1;
}

void Oracle(quantum_reg *quReg)
{
    int reg0 = quRAM;
    
    int maxDepth = CheckLines(reg0, quReg);
    int reg1 = quRAM+maxDepth+1;
    int reg2 = quRAM+maxDepth+2;
    int reg3 = quRAM+maxDepth+3;
    
    quantum_cnot(reg0, reg1, quReg);
    CheckLines(reg0, quReg);
    CheckDiagonals(reg0, 1, quReg);
    quantum_toffoli(reg0, reg1, reg2, quReg);
    CheckDiagonals(reg0, 1, quReg);
    
    CheckDiagonals(reg0, 2, quReg);
    quantum_toffoli(reg0, reg2, reg3, quReg);
    CheckDiagonals(reg0, 2, quReg);
    
    if (nb_queens < 8) {
        CheckLimit(reg0, nb_queens, quReg);
        quantum_toffoli(reg0, reg3, quControlBit, quReg);
        CheckLimit(reg0, nb_queens, quReg);
        
    } else {
        quantum_cnot(reg3, quControlBit, quReg);
    }
    
    CheckDiagonals(reg0, 2, quReg);
    quantum_toffoli(reg0, reg2, reg3, quReg);
    CheckDiagonals(reg0, 2, quReg);
    
    CheckDiagonals(reg0, 1, quReg);
    quantum_toffoli(reg0, reg1, reg2, quReg);
    CheckDiagonals(reg0, 1, quReg);

    
    CheckLines(reg0, quReg);
    quantum_cnot(reg0, reg1, quReg);
    CheckLines(reg0, quReg);
    
    //quantum_print_qureg(*quReg);

}

void Inversion(quantum_reg *quReg)
{
    int i = 0;
    
    for (int i = 0; i< nb_queens*3; i++)
        quantum_hadamard(i, quReg);
    for (int i = 0; i< nb_queens*3; i++)
        quantum_sigma_x(i, quReg);
    
    quantum_sigma_x(quRAM, quReg);
    
    for (i = 0; i< nb_queens*3; i++) {
        quantum_toffoli(queen0[0] + i, quRAM+i, quRAM+i+1, quReg);
    }

    quantum_cnot(quRAM+i, quControlBit, quReg);
    
    for (i = nb_queens*3 - 1; i >=0; i--) {
        quantum_toffoli(queen0[0] + i, quRAM+i, quRAM+i+1, quReg);
    }
    
    quantum_sigma_x(quRAM, quReg);
    
    for (int i = 0; i< nb_queens*3; i++)
        quantum_sigma_x(i, quReg);
    for (int i = 0; i< nb_queens*3; i++)
        quantum_hadamard(i, quReg);
    
}

void printQueensFromState(unsigned long long state) {
    
    
    int Queens[queenWidth/3] = {state % 8, (state >> 3) % 8, (state >> 6) % 8, (state >> 9) % 8, (state >> 12) % 8, (state >> 15) %8, (state >> 18) %8, (state >> 21) %8};

    for (int i = 0; i< nb_queens; i++) {
        printf("\n|");
        for (int j = 0; j<nb_queens; j++) {
            if (Queens[j] == nb_queens-1-i) {
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
    
    if( argc == 3 ) {
        printf("cheat code activated\n");
        cheat_code_active = 1;
        nb_queens = atoi(argv[2]);
    } else if (argc < 2) {
        printf("not enough argument\n");
        exit(-1);
    } else if (argc == 2) {
        nb_queens = atoi(argv[1]);
    }
        
    

    
    quantum_reg quReg;

    srand((unsigned int)clock()*100000);

    quReg = quantum_new_qureg(0, nb_queens*3+1);
    quantum_addscratch(15, &quReg);
    
    //superpose queens states
    for (int i = 0; i< nb_queens*3; i++)
        quantum_hadamard(i, &quReg);
    
    //initialize control bit
    quantum_sigma_x(quControlBit, &quReg);
    quantum_hadamard(quControlBit, &quReg);
    
    int order=1;
    int autoMode = 0;
    if (!cheat_code_active) {
        switch (nb_queens) {
            case 5:
                order = 43;
                break;
            case 4 :
                order = 34;
                break;
            default :
                autoMode = 1;
                order = 1000;
                break;
        }
    }
    
        double proba = 0.0;
    for (int i = 0; i< order; i++) {
        double intermediate_proba;
        Oracle(&quReg);
        Inversion(&quReg);
        
        if (autoMode) {
            intermediate_proba = quantum_prob(quReg.amplitude[0]);
            printf("AutoPass : %d P = %.15f\n", i, intermediate_proba);
            if ((proba != 0.0) && (intermediate_proba > proba)){

                break;
            } else {
                proba = intermediate_proba;
            }
        }
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

