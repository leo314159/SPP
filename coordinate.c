//
// Created by lenovo on 11/10/2021.
//

#include "coordinate.h"

XYZ * BLH2XYZ(BLH *blh,double a,double e)
{
    XYZ *xyz=(XYZ*)malloc(sizeof(XYZ));
    double N=a/sqrt(1-e*e*sin(blh->B)*sin(blh->B));
    xyz->x=(N+blh->H)*cos(blh->B)*cos(blh->L);
    xyz->y=(N+blh->H)*cos(blh->B)*sin(blh->L);
    xyz->z=(N*(1-e*e)+blh->H)*sin(blh->B);
    return xyz;
}

BLH * XYZ2BLH(XYZ *xyz,double a,double e)
{

    double X = xyz->x;
    double Y = xyz->y;
    double Z = xyz->z;

    double b = 6356752.3142;
    double ePie2 = 0.00673949674227;
    double xita = atan(Z * a / (sqrt(X * X + Y * Y) * b));
    double xitaSin3 = sin(xita) * sin(xita) * sin(xita);
    double xitaCos3 = cos(xita) * cos(xita) * cos(xita);
    double B = atan((Z + ePie2 * b * xitaSin3) / ((sqrt(X * X + Y * Y) - e*e * a *  xitaCos3)));
    double L = atan(Y/ X);
    double N = a / sqrt(1 - e*e* sin(B) * sin(B)); ;
    double H = sqrt(X * X + Y * Y) / cos(B) - N;

    BLH *blh=(BLH*)malloc(sizeof(BLH));

    blh->B=B;
    blh->L=L;
    blh->H=H;
    return blh;
}

