#include <iostream>
#include <cstring>
#include <fstream>
#include "interact.h"
#include "tactics.h"
#include "calculate.h"

// current frame sequence
int Interactor::curFrame;
// current money
int Interactor::curMoney;
// workplace num of current frame
int Interactor::curWrkplcNum;
// robot object
Interactor::Robot Interactor::rbt[Constant::Robot::RbtNum];
// workplace object
Interactor::Workplace Interactor::wrkplc[Constant::Workplace::MaxWrkplcNum];

// read a frame
bool Interactor::readFrame(){

    scanf("%d %d\n",&curFrame,&curMoney);   
    scanf("%d\n",&curWrkplcNum);

    for(int i = 0; i < curWrkplcNum; i++){
        scanf("%d %lf %lf %d %d %d\n",
        &wrkplc[i].type,&wrkplc[i].pos.x,&wrkplc[i].pos.y,&wrkplc[i].remProdFrmNum,&wrkplc[i].rawMaterial,&wrkplc[i].prodState);
    }

    for(int i = 0; i < Constant::Robot::RbtNum; i++){
        scanf("%d %d %lf %lf %lf %lf %lf %lf %lf %lf\n",
        &rbt[i].curWrkplcId,&rbt[i].carriedGoodsType,&rbt[i].TVC,&rbt[i].CVC,
        &rbt[i].angVelocity,&rbt[i].lnVelocity[0],&rbt[i].lnVelocity[1],&rbt[i].direction,&rbt[i].pos.x,&rbt[i].pos.y);
        rbt[i].id = i;
    }

    char end[16];
    scanf("%s",end);
    if(strcmp(end,"OK")) return false;
    return true;
}


void Interactor::Robot::forward(double v){
    if(v < Constant::Robot::MinForwardVelocity ||
        v > Constant::Robot::MaxForwardVelocity)
        fprintf(stderr,"speed out of range: line speed = %lf\n",v);
    printf("forward %d %lf\n",this->id,v);
}

// angular velocity
void Interactor::Robot::rotate(double av){
    if(av < Constant::Robot::MinAngularVelocity ||
        av > Constant::Robot::MaxAngularVelocity)
        fprintf(stderr,"angular speed out of range: angular speed = %lf\n",av);
    printf("rotate %d %lf\n",this->id,av);
}

void Interactor::Robot::buy(){
    if(curWrkplcId == -1){
        fprintf(stderr,"robot %d is not in any workplace\n",id);
        return;
    }
    if(Interactor::wrkplc[curWrkplcId].prodState==0){
        return;
    }
    printf("buy %d\n",this->id);
    carriedGoodsType=Interactor::wrkplc[curWrkplcId].type;
    //fprintf(stderr,"test10\n");
    Interactor::wrkplc[curWrkplcId].isGlobalOrder=false;
    Interactor::wrkplc[curWrkplcId].prodState=0;
    //fprintf(stderr,"test11\n");
    if(Interactor::wrkplc[targetWrkplcId].MaterialEmpty().size()==0){
        Interactor::wrkplc[curWrkplcId].isOrder=false;
    }
        
    //fprintf(stderr,"test12\n");
    targetWrkplcId = Interactor::wrkplc[curWrkplcId].orderList.front().toidx;
    //fprintf(stderr,"test13\n");
    fprintf(stderr,"%d %ld\n",curWrkplcId,Interactor::wrkplc[curWrkplcId].orderList.size());
    Interactor::wrkplc[curWrkplcId].orderList.pop_front();
    //fprintf(stderr,"test14\n");
}

void Interactor::Robot::sell(){
    printf("sell %d\n",this->id);
    Interactor::wrkplc[targetWrkplcId].rawMaterial|=(1<<carriedGoodsType);
    // fprintf(stderr,"remain material num:%ld\n",
    //   Interactor::wrkplc[targetWrkplcId].MaterialEmpty().size());
    if(Interactor::wrkplc[targetWrkplcId].MaterialEmpty().size()==0 && Interactor::wrkplc[targetWrkplcId].remProdFrmNum==-1){
        Interactor::wrkplc[curWrkplcId].isOrder=false;
        Interactor::wrkplc[curWrkplcId].rawMaterial=0;
    }
    targetWrkplcId = -2;
}

void Interactor::Robot::destroy(){
    printf("destroy %d\n",this->id);
}

bool Interactor::Robot::willCollide(int rbtid)
{
    if(rbtid < 0 || rbtid >= Constant::Robot::RbtNum)
        return false;
    double dis = cal_distance(pos,Interactor::rbt[rbtid].pos);
    if(dis > Constant::Robot::RbtRadius * 4)
        return false;
    if(lnVelocity[0] == 0 && Interactor::rbt[rbtid].lnVelocity[0] == 0)
        return false;
    Interactor::Coord p = cal_all_intersection_point(pos,Interactor::rbt[rbtid].pos,lnVelocity,Interactor::rbt[rbtid].lnVelocity);
    return is_in_motion_path(p,pos,Interactor::rbt[rbtid].pos,lnVelocity,Interactor::rbt[rbtid].lnVelocity);
}

void Interactor::Workplace::addOrder(const order& o){
    orderList.push_back(o);
}

std::vector<int> Interactor::Workplace::MaterialEmpty(){
    int res = Constant::Workplace::goodsMap[type] - rawMaterial;
    std::vector<int> ans;
    for(int i = 1;i <= 7;i++){
        if(res & (1 << i))
            ans.push_back(i);
    }
    return ans;
}
