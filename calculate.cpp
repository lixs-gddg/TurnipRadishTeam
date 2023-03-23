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
    double ans=atan((b.y-a.y)/(b.x-a.x));
    if(b.x>a.x){
        return ans;
    }else{
        if(ans>0) return ans-M_PI;
        return ans+M_PI;
    }
}

int judge_rotation_direction(double cur,double tar){
    cur=cur<0?2*M_PI+cur:cur;
    tar=tar<0?2*M_PI+tar:tar;
    return cur<tar?1:-1;
}