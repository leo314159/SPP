//
// Created by lenovo on 11/10/2021.
//
#include <stdlib.h>
#include "time.h"

MJDTIME *CommonTime2MjdTime(COMMONTIME * commontime)
{
    int M=commontime->Month;
    int y,m;
    if (M<=2)
    {
        y=commontime->Year-1;
        m=commontime->Month+12;
    }
    else
    {
        y=commontime->Year;
        m=commontime->Month;
    }
    double UT=commontime->Hour+commontime->Minute/60.0+commontime->Second/3600.0;//h
    double MJD=(int)(365.25*y)+(int)(30.6001*(m+1))+commontime->Day
            +UT/24.0-679019;
    MJDTIME* mjdtime =(MJDTIME *)malloc(sizeof(MJDTIME));
    mjdtime->Days=(int)MJD;
    mjdtime->FracDay=MJD-(int)MJD;
return mjdtime;

}
COMMONTIME *MjdTime2CommonTime(MJDTIME *mjdtime)
{
    int a =(int) (mjdtime->Days+mjdtime->FracDay+0.5);
    int b = a + 1537;
    int c=(int)((b-122.1)/365.25);
    int d =(int) (365.25*c);
    int e =(int)((b-d)/30.6001);
    double D=b-d-(int)(30.6001*e)+mjdtime->Days+mjdtime->FracDay+0.5-a;
    unsigned short M=e-1-12*(int)(e/14.0);
    unsigned short Y=c-4715-(int)((7+M)/10.0);
    //int N=
    COMMONTIME * commontime=(COMMONTIME *)malloc(sizeof(COMMONTIME));
    commontime->Day=D;
    commontime->Month=M;
    commontime->Year=Y;
    //free(commontime);
    return commontime;

}




GPSTIME *MjdTime2GpsTime(MJDTIME *mjdtime)
{
    unsigned short GPSWEEK=(int)((mjdtime->Days+mjdtime->FracDay-44244)/7.0);
    double SECOFWEEK=(mjdtime->Days+mjdtime->FracDay-44244-GPSWEEK*7)*86400;
    GPSTIME* gpstime =(GPSTIME *)malloc(sizeof(GPSTIME));
    gpstime->Week=GPSWEEK;
    gpstime->SecOfWeek=SECOFWEEK;
    return gpstime;
}





MJDTIME *GpsTime2MjdTime(GPSTIME *gpstime)
{
    MJDTIME* mjdtime =(MJDTIME *)malloc(sizeof(MJDTIME));
    double MJD=44244+(gpstime->Week)*7+(gpstime->SecOfWeek)/86400.0;
    mjdtime->Days=(int) MJD;
    mjdtime->FracDay=MJD - (int) MJD;
    return mjdtime;
}