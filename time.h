//
// Created by lenovo on 11/10/2021.
//

#ifndef MATRIX_TIME_H
#define MATRIX_TIME_H

typedef struct{
    unsigned short Year;
    unsigned short Month;
    unsigned short Day;
    unsigned short Hour;
    unsigned short Minute;
    double Second;
} COMMONTIME;


typedef struct {
    int Days;
    double FracDay;
//    MJDTIME()
//    {
//        Days=0;
//        FracDay=0.0;
//    }

}MJDTIME;

typedef struct{
    unsigned short Week;
    double SecOfWeek;
//    GPSTIME()
//    {
//        Week=0;
//        SecOfWeek=0.0;
//    }

} GPSTIME;

MJDTIME *CommonTime2MjdTime(COMMONTIME * commontime);
COMMONTIME *MjdTime2CommonTime(MJDTIME *mjdtime);
GPSTIME *MjdTime2GpsTime(MJDTIME *mjdtime);
MJDTIME *GpsTime2MjdTime(GPSTIME *mjdtime);

GPSTIME *CommonTime2GpsTime(COMMONTIME * commontime);
COMMONTIME *GpsTime2CommonTime(GPSTIME *mjdtime);

#endif //MATRIX_TIME_H
