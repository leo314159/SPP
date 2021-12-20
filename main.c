#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "coordinate.h"
#include "time.h"

int main() {

    printf("input1:\n");
    matrix *input1=MatInput();
    printf("input2:\n");
    matrix *input2=MatInput();
    printf("output input1:\n");
    MatOutput(input1);
    printf("output input2:\n");
    MatOutput(input2);
    printf("MatAdd input1 input2:\n");
    MatOutput(MatAdd(input1,input2));
    printf("MatSub input1 input2:\n");
    MatOutput(MatSub(input1,input2));
    printf("MatMal input1 input2:\n");
    MatOutput(MatMal(input1,input2));
    printf("MatTrans input1:\n");
    MatOutput(MatTrans(input1));
    printf("MatInv input1:\n");
    MatOutput(MatInv(input1));
    double x= MatDet(input1);
    printf("\ndet of input1:%f",x);
    MatFree(input1);
    MatFree(input2);



    double a=6378137.0,e=sqrt(0.0066943799013);
    BLH * blh=(BLH *)malloc(sizeof(BLH));
    blh->B= 30*D2R;
    blh->L= 114*D2R;
    blh->H= 200;

    XYZ * xyz= BLH2XYZ(blh,a,e);
    printf("X:%f,Y:%f,Z:%f\n",xyz->x,xyz->y,xyz->z);
    blh=XYZ2BLH(xyz,a,e);
    printf("B:%f,L:%f,H:%f\n",R2D*blh->B,R2D*blh->L,blh->H);
    free(blh);
    free(xyz);

    MJDTIME *mjdtime=(MJDTIME *)malloc(sizeof(MJDTIME));
    mjdtime->Days= 2454399;
    mjdtime->FracDay=0.896;
    COMMONTIME * commontime;//=(COMMONTIME *)malloc(sizeof(COMMONTIME));
    commontime= MjdTime2CommonTime(mjdtime);
    free(mjdtime);
    free(commontime);

//    COMMONTIME * commontime=(MJDTIME *)malloc(sizeof(MJDTIME));
//    commontime->Year=2007;
//    commontime->Month   =10;
//    commontime->Day=26;
//    commontime->Hour=9;
//    commontime->Minute=30;
//    commontime->Second=0;
//    MJDTIME *mjdtime= CommonTime2MjdTime(commontime);
//    free(mjdtime);
//    free(commontime);
//
//    MJDTIME * mjdtime=(MJDTIME *)malloc(sizeof(MJDTIME));
//    //GPSTIME * gpstime=(GPSTIME *)malloc(sizeof(GPSTIME));
//    mjdtime->Days= 2454399;
//    mjdtime->FracDay=0.896;
//    GPSTIME *gpstime= MjdTime2GpsTime(mjdtime);
//    mjdtime= GpsTime2MjdTime(gpstime);
//    free(gpstime);
//    free(mjdtime);

    return 0;

}
