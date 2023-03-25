#ifndef __CALCULATE_H__
#define __CALCULATE_H__
#include "interact.h"
//a and b refer to two different coordinates.
//calculate the distance between a and b.
double cal_distance(Interactor::Coord a,Interactor::Coord b);
//a and b refer to two different directions.
//calculate the angle between a and b.
double cal_angle(double a,double b);
// a and b refer to two different coordinates.
// calculate the direction of a->b
double cal_direction(Interactor::Coord a, Interactor::Coord b);
// cur refer to current direction, tar refer to target direction
// return true means ccw,flase means cw
int judge_rotation_direction(double cur,double tar);
// dir refer to a direction,
// return the reverse direction
double reverse_direction(double dir);
#endif