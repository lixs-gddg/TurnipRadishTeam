#ifndef __CALCULATE_H__
#define __CALCULATE_H__
#include"interact.h"
//a and b refer to two different coordinates.
//calculate the distance between a and b.
double cal_distance(Interactor::Coord a,Interactor::Coord b);
//a and b refer to two different directions.
//calculate the angle between a and b.
double cal_angle(double a,double b);

#endif