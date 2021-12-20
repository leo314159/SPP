//
// Created by lenovo on 11/10/2021.
//

#ifndef MATRIX_COORDINATE_H
#define MATRIX_COORDINATE_H
#include <stdlib.h>
#include <math.h>
#define PI          3.14159265358979323846  /* pi */
#define D2R         (PI/180.0)          /* deg to rad */
#define R2D         (180.0/PI)          /* rad to deg */


typedef struct {

    double x;
    double y;
    double z;
}XYZ;



typedef struct {
    double B;
    double L;
    double H;
}BLH;

XYZ * BLH2XYZ(BLH *blh,double a,double e);
BLH * XYZ2BLH(XYZ *xyz,double a,double e);


#endif //MATRIX_COORDINATE_H
