#include "calculate.h"
#include <iostream>
#include "const.h"

double cal_distance(Interactor::Coord a,Interactor::Coord b){
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

double cal_angle(double a,double b){
    return fabs(a-b)>M_PI ? 2*M_PI-fabs(a-b):fabs(a-b);
}

double cal_direction(Interactor::Coord a,Interactor::Coord b){
    return atan((b.y-a.y)/(b.x-a.x));
}