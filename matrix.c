/*------------------------------------------------------------------------------
* matrix.c : matrix functions
*
*          Copyright (C) 2007-2018 by T.TAKASU, All rights reserved.
*
*
* version : $Revision: 1.2 $ $Date: 2008/07/14 00:05:05 $
* history : 2021/10/08 1.0 new
*           2008/05/09 1.1 fix bug lli flag outage
*           2008/06/16 1.2 separate common functions to rcvcmn.c
*-----------------------------------------------------------------------------*/
#include "matrix.h"

/* initialize a matrix --------------------------------------------------------
* Matrix is initialized to zero matrix
* args   : int row  I  rows of the new matrix
*          int col  I  columns of the new matrix
* return : matrix
*
*-----------------------------------------------------------------------------*/
matrix* MatInit(int row,int col)
{
    matrix *m=(matrix*)malloc(sizeof (matrix));
    double *p = ( double*)malloc(sizeof(double) * row * col);
    m->p=p;
    m->row=row;
    m->col=col;
    for(int i=0;i<row;i++)
        for(int j=0;j<row;j++)
        {
            p[i+j*row]=0.0;
        }
    return m;
}


/* generate a matrix --------------------------------------------------------
* generate matrix from array
* args   : int row  I  rows of the new matrix
*          int col  I  columns of the new matrix
* return : matrix
*
*-----------------------------------------------------------------------------*/
matrix* MatGen(double ** a)
{

    matrix* m = (matrix*)malloc(sizeof(matrix));
    
    m->row = sizeof(a) / sizeof(a[0]);
    m->col = sizeof(a[0]) / sizeof(double);
    double* p = (double*)malloc(sizeof(double) * m->row * m->col);
    m->p = p;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < row; j++)
        {
            p[i + j * row] = a[i][j];
        }
    return m;
}







/* free a matrix --------------------------------------------------------
* Free up the space occupied by the matrix
* args   : matrix *m  IO   matrix which will be deleted
* return : void
*
*-----------------------------------------------------------------------------*/
void MatFree(matrix *m)
{
    free(m->p);
}

/* input a matrix --------------------------------------------------------
* Input the matrix from keyboard
* args   : void
* return : matrix
*
*-----------------------------------------------------------------------------*/
matrix *MatInput()
{
    int row,col;
    printf("Row:");
    scanf("%d",&row);
    printf("Col:");
    scanf("%d",&col);
    matrix *m=MatInit(row,col);

    printf("Matrix:");
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
        {
            scanf("%lf",&m->p[i*row+j]);
        }

    return m;
}

/* output a matrix --------------------------------------------------------
* Output the matrix to window
* args   : matrix *m  IO   matrix which will be output
* return : void
*
*-----------------------------------------------------------------------------*/
void MatOutput(matrix *m)
{
    for(int i=0;i<m->row;i++) {
        for (int j = 0; j < m->col; j++) {
            printf("%lf", m->p[i * m->row + j]);
        }
        printf("\n");
    }
}

/* matrix addition--------------------------------------------------------
* Output the matrix to window
* args   : matrix *a  IO   matrix which will be added
*          matrix *b  IO   matrix which will be added
* return : matrix addition result
*
*-----------------------------------------------------------------------------*/
matrix *MatAdd(matrix *a, matrix *b)
{

    if(a->row==b->row &&a->col==b->row)
    {
        matrix *m=MatInit(a->row,a->col);
        for (int i = 0;i<a->row;i++)
            for (int j = 0;j<a->col;j++)
            {
                m->p[i*a->row+j]=a->p[i*a->row+j]+b->p[i*a->row+j];
            }
        return m;
    }
    else printf("MatAdd Error: rows or cols are not equal\n");

}


/*matrix subtraction--------------------------------------------------------
* Output the matrix to window
* args   : matrix *a  IO   matrix
*          matrix *b  IO   matrix
* return : matrix subtraction result
*
*-----------------------------------------------------------------------------*/
matrix *MatSub(matrix *a, matrix *b)
{
    if(a->row==b->row &&a->col==b->row)
    {
        matrix *m=MatInit(a->row,b->col);
        for (int i = 0;i<a->row;i++)
            for (int j = 0;j<a->col;j++)
            {
                m->p[i*a->row+j]=a->p[i*a->row+j]-b->p[i*a->row+j];
            }
        return m;
    }
    else printf("MatDel Error: rows or cols are not equal\n");

}


/* multiply a matrix --------------------------------------------------------
* Output the matrix to window
* args   : matrix *a  IO   matrix
*          matrix *b  IO   matrix
* return : matrix multiplication result
*
*-----------------------------------------------------------------------------*/
matrix *MatMal(matrix *a, matrix *b)
{
    matrix *m=MatInit(a->row,b->col);
    if(a->col==b->row)
    {
        for (int i = 0;i<m->row;i++)
            for (int j = 0;j<m->col;j++)
            {
                double temp =0;
                for (int k=0;k<a->col;k++)
                    temp=temp+a->p[i*a->row+k]*b->p[k*b->row+j];
                m->p[i*m->row+j]=temp;
            }
        return m;
    }
    else printf("MatMul Error: a.row is not equal to b.col\n");
}


/* transpose a matrix --------------------------------------------------------
* transpose a matrix
* args   : matrix *a  I   matrix
* return : matrix transpose result
*
*-----------------------------------------------------------------------------*/
matrix *MatTrans(matrix *a)
{
    matrix *m=MatInit(a->col,a->row);
    for (int i = 0;i<m->row;i++)
        for (int j = 0;j<m->col;j++)
        {
            m->p[i*m->row+j]=a->p[j*a->row+i];
        }
    return m;
}
/* determination of a matrix --------------------------------------------------------
* determination of a matrix
* args   : matrix *a  I   matrix
* return : double  determination result
*
*-----------------------------------------------------------------------------*/
double MatDet(matrix *a)
{

    if(a->row != a->col) printf("MatInv Error: row is not equal to col \n");
    else {
        int n = a->row;
        double res=1.0;
        matrix *copy=MatInit(n, n);

        for(int x=0; x < a->row; x++)
            for(int y=0; y < a->col; y++)
                copy->p[x * a->row + y]=a->p[x * a->row + y];

        matrix *output=MatInit(n, n);//output
        matrix *L=MatInit(n,n);//L
        matrix *U=MatInit(n,n);//U
        matrix *r=MatInit(n,n);//r

        int i,j,k;
        double s,t;

        for(j=0;j<n;j++)
            copy->p[0 * n + j]=copy->p[0 * n + j];  //计算U矩阵的第一行

        for(i=1;i<n;i++)
            copy->p[i * n + 0]= copy->p[i * n + 0] / copy->p[0 * n + 0];   //计算L矩阵的第1列

        for(k=1;k<n;k++)
        {
            for(j=k;j<n;j++)
            {
                s=0.0;
                for (i=0;i<k;i++)
                    s= s + copy->p[k * n + i] * copy->p[i * n + j];   //累加
                copy->p[k * n + j]= copy->p[k * n + j] - s; //计算U矩阵的其他元素
            }
            for(i=k+1;i<n;i++)
            {
                t=0.0;
                for(j=0;j<k;j++)
                    t= t + copy->p[i * n + j] * copy->p[j * n + k];   //累加
                copy->p[i * n + k]= (copy->p[i * n + k] - t) / copy->p[k * n + k];    //计算L矩阵的其他元素
            }
        }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
            {
                if(i>j)
                {
                    L->p[i*n+j]=copy->p[i * n + j];
                    U->p[i*n+j]=0.0;
                }//如果i>j，说明行大于列，计算矩阵的下三角部分，得出L的值，U的//为0
                else
                {
                    U->p[i*n+j]=copy->p[i * n + j];
                    if(i==j)
                        L->p[i*n+j]=1.0;  //否则如果i<j，说明行小于列，计算矩阵的上三角部分，得出U的//值，L的为0
                    else
                        L->p[i*n+j]=0.0;
                }
            }

        for (i=0;i<n;i++)
            {res*=U->p[i*n+i]; }
        return  res;
        }



}


/* Matrix inversion --------------------------------------------------------
* Matrix inversion
* args   : matrix *a  I   matrix
* return : matrix transpose result
*
*-----------------------------------------------------------------------------*/
matrix *MatInv(matrix *a)
{
   if(a->row != a->col) printf("MatInv Error: row is not equal to col \n");

   else
    {
        int n=a->row;
        matrix *copy=MatInit(n, n);

       for(int x=0; x < a->row; x++)
           for(int y=0; y < a->col; y++)
               copy->p[x * a->row + y]=a->p[x * a->row + y];

        matrix *output=MatInit(n, n);//output
        matrix *L=MatInit(n,n);//L
        matrix *U=MatInit(n,n);//U
        matrix *r=MatInit(n,n);//r
        matrix *u=MatInit(n,n);//u

        matrix *test=MatInit(n,n);

        int i,j,k;
        double s,t;
        double det=1.0;

        for(j=0;j<n;j++)
            copy->p[0 * n + j]=copy->p[0 * n + j];  //计算U矩阵的第一行

        for(i=1;i<n;i++)
            copy->p[i * n + 0]= copy->p[i * n + 0] / copy->p[0 * n + 0];   //计算L矩阵的第1列
        for(k=1;k<n;k++)
        {
            for(j=k;j<n;j++)
            {
                s=0.0;
                for (i=0;i<k;i++)
                    s= s + copy->p[k * n + i] * copy->p[i * n + j];   //累加
                copy->p[k * n + j]= copy->p[k * n + j] - s; //计算U矩阵的其他元素
            }
            for(i=k+1;i<n;i++)
            {
                t=0.0;
                for(j=0;j<k;j++)
                    t= t + copy->p[i * n + j] * copy->p[j * n + k];   //累加
                copy->p[i * n + k]= (copy->p[i * n + k] - t) / copy->p[k * n + k];    //计算L矩阵的其他元素
            }
        }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
            {
                if(i>j)
                {
                    L->p[i*n+j]=copy->p[i * n + j];
                    U->p[i*n+j]=0.0;
                }//如果i>j，说明行大于列，计算矩阵的下三角部分，得出L的值，U的//为0
                else
                {
                    U->p[i*n+j]=copy->p[i * n + j];
                    if(i==j)
                        L->p[i*n+j]=1.0;  //否则如果i<j，说明行小于列，计算矩阵的上三角部分，得出U的//值，L的为0
                    else
                        L->p[i*n+j]=0.0;
                }
            }



        for (i=0;i<n;i++)
        {det*=U->p[i*n+i]; }

    if(abs(det)<1e-10)
    {

        printf("MatInv Error: matrix is not inversible \n");

    }


        /////////////////////求L和U矩阵的逆
        for (i=0;i<n;i++) /*求矩阵U的逆 */
        {
            u->p[i*n+i]=1.0/(U->p[i*n+i]);//对角元素的值，直接取倒数
            //printf("\n%lf\n",u->p[i*n+i]);
            for (k=i-1;k>=0;k--)
            {
                s=0.0;
                for (j=k+1;j<=i;j++)
                    s=s+(U->p[k*n+j])*(u->p[j*n+i]);
                u->p[k*n+i]=-s/(U->p[k*n+k]);//迭代计算，按列倒序依次得到每一个值，
            }
        }
        for (i=0;i<n;i++) //求矩阵L的逆
        {
            r->p[i*n+i]=1.0; //对角元素的值，直接取倒数，这里为1
            for (k=i+1;k<n;k++)
            {
                for (j=i;j<=k-1;j++)
                    r->p[k*n+i]=(r->p[k*n+i])-(L->p[k*n+j])*(r->p[j*n+i]);   //迭代计算，按列顺序依次得到每一个值
            }
        }

        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            { output->p[i * n + j]=0.0;}
        }


        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                for(k=0;k<n;k++)
                {
                    output->p[i * n + j]+= u->p[i * n + k] * r->p[k * n + j];
                }
            }
        }

        MatFree(L);
        MatFree(U);
        MatFree(r);
        MatFree(u);

        return output;

    }

}