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

// todo : handle lnVelocity[0] == 0 exception
// caculate the intercept of the motion path         y = ax + [b]
double cal_intercept(Interactor::Coord pos,std::vector<double>& lnVelocity){
    // if(lnVelocity[0] != 0) 
    return pos.y - lnVelocity[1]/lnVelocity[0]*pos.x;
}

// caculate the interception point of two motion path exclude line x = a
Interactor::Coord cal_intersection_point(std::vector<double>& alnv,std::vector<double>& blnv,double b1,double b2){
    Interactor::Coord c;
    double i = alnv[1]/alnv[0];
    c.x = (i - blnv[1]/blnv[0]) / (b2-b1);
    c.y = i * c.x + b1;
    return c;
}



Interactor::Coord cal_all_intersection_point(Interactor::Coord a,Interactor::Coord b,std::vector<double>& alnv,std::vector<double>& blnv){
    if(alnv[0] == 0 && blnv[0] == 0)
        return Interactor::Coord{0,0};
    double b1,b2;
    if(alnv[0] == 0){
        b2 = cal_intercept(b,blnv);
        double y = blnv[1]/blnv[0] * a.x + b2;
        return Interactor::Coord{a.x,y};
    }
    if(blnv[0] == 0){
        b1 = cal_intercept(a,alnv);
        double y = alnv[1]/alnv[0] * b.x + b1;
        return Interactor::Coord{b.x,y};
    }
    return cal_intersection_point(alnv,blnv,b1,b2);
}


// judge interction point in motion path ?
bool is_in_motion_path(Interactor::Coord p,Interactor::Coord a,Interactor::Coord b
    ,std::vector<double>& alnv,std::vector<double>& blnv){
        bool res1 = (p.x - a.x) * alnv[0] > 0 && (p.y - a.y) * alnv[1] > 0;
        bool res2 = (p.x - b.x) * blnv[0] > 0 && (p.y - b.y) * blnv[1] > 0;
        return res1 && res2;
}

int judge_rotation_direction(double cur,double tar){
    cur=cur<0?2*M_PI+cur:cur;
    tar=tar<0?2*M_PI+tar:tar;
    return cur<tar?1:-1;
}

double reverse_direction(double dir){
    return dir>0?dir-M_PI:dir+M_PI;
}