/*------------------------------------------------------------------------------
* matrix.h : matrix types and function prototypes
*
*          Copyright (C) 2007-2015 by T.TAKASU, All rights reserved.
*
*
* version : $Revision: 1.1 $ $Date: 2008/07/17 21:48:06 $
* history : 2007/01/13 1.0  rtklib ver.1.0.0
*
*-----------------------------------------------------------------------------*/
#ifndef SPP_MATRIX_H
#define SPP_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct /* matrix type */
{
    int row;   /* rows of the matrix */
    int col;   /* columns of the matrix */
    double* p;  /* matrix data  */       //利用一维数组来模拟二维数组

}matrix;

/* matrix operation function ------------------------------------------------------------*/
matrix *MatInit(int row,int col);
matrix *MatInput();
void MatOutput(matrix *a);
void MatFree(matrix *a);

matrix *MatAdd(matrix *a, matrix *b);
matrix *MatSub(matrix *a, matrix *b);
matrix *MatMal(matrix *a, matrix *b);
matrix *MatTrans(matrix *a);

double MatDet(matrix *a);
matrix *MatInv(matrix *a);

#endif //SPP_MATRIX_H