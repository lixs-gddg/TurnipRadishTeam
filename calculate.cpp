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

bool is_collide_in_motion_path(Interactor::Coord ap,Interactor::Coord bp,std::vector<double>& alnv,std::vector<double>& blnv){
    double a = pow(alnv[0]-blnv[0],2)+pow(alnv[1]-blnv[1],2);
    double b = 2*(alnv[0]-blnv[0])*(ap.x-bp.x)+2*(alnv[1]-blnv[1])*(ap.y-bp.y);
    double c = pow(ap.x-bp.x,2)+pow(ap.y-bp.y,2)-4*pow(Constant::Robot::RbtRadius,2);
    double delta = pow(b,2) - 4 * a * c;
    if(delta < 0)
        return false;
    double t1 = -b + sqrt(delta);
    double t2 = -b - sqrt(delta);
    if(t1 < 0 && t2 < 0)
        return false;
    return true;
    
}

int judge_rotation_direction(double cur,double tar){
    cur=cur<0?2*M_PI+cur:cur;
    tar=tar<0?2*M_PI+tar:tar;
    return cur<tar?1:-1;
}

double reverse_direction(double dir){
    return dir>0?dir-M_PI:dir+M_PI;
}

double cal_average_direction(double a,double b){
    double ans=(a+b)/2;
    if(cal_angle(ans,a)>M_PI/2){
        ans=reverse_direction(ans);
    }
    return ans;
}