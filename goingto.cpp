#include "goingto.h"
#include "calculate.h"
#include "interact.h"
#define PI M_PI
void goingto(int robotId,int workplaceId){
    if(workplaceId<0||workplaceId>Interactor::curWrkplcNum||robotId<0||robotId>3) return;
    double direction=cal_direction(Interactor::rbt[robotId].pos,Interactor::wrkplc[workplaceId].pos);
    double angle=cal_angle(direction,Interactor::rbt[robotId].direction);
    double distance=cal_distance(Interactor::rbt[robotId].pos,Interactor::wrkplc[workplaceId].pos);
    double v=sqrt(pow(Interactor::rbt[robotId].lnVelocity[0],2)+pow(Interactor::rbt[robotId].lnVelocity[1],2));
    double w=Interactor::rbt[robotId].angVelocity;
    double a=Interactor::rbt[robotId].carriedGoodsType? accerlate_va:accerlate_vb;
    double b=Interactor::rbt[robotId].carriedGoodsType? accerlate_aa:accerlate_ab;
    int rotationDir=judge_rotation_direction(Interactor::rbt[robotId].direction,direction);
    if(angle>PI/2){
        Interactor::rbt[robotId].rotate(rotationDir*PI);
        Interactor::rbt[robotId].forward(-2);
    }else{
        if(fabs(w)<1e-4&&angle>1e-4){
            Interactor::rbt[robotId].rotate(rotationDir * sqrt(angle*b));
        }else if(angle<pow(w,2)/(2*b)&&w*rotationDir>0){
            Interactor::rbt[robotId].rotate(0);
        }else {
            Interactor::rbt[robotId].rotate(rotationDir*PI);
        }
        if(distance<1)
            Interactor::rbt[robotId].forward(2);
        else if(angle>PI/4){
            Interactor::rbt[robotId].forward(2);
            Interactor::rbt[robotId].rotate(rotationDir*PI);
        }
            
        else Interactor::rbt[robotId].forward(6);
    }
    
}

void avoid(int id1,int id2){
    double dir=cal_direction(Interactor::rbt[id1].pos,Interactor::rbt[id2].pos);
    double average_dir=cal_average_direction(Interactor::rbt[id1].direction,reverse_direction(Interactor::rbt[id2].direction));
    int rotationDir=judge_rotation_direction(dir,average_dir);
    Interactor::rbt[id1].rotate(rotationDir*PI/1.25);
    Interactor::rbt[id1].forward(3);
}