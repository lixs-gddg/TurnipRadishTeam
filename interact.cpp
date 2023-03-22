#include <iostream>
#include <cstring>
#include <fstream>
#include "interact.h"

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
    printf("buy %d\n",this->id);
}

void Interactor::Robot::sell(){
    printf("sell %d\n",this->id);
}

void Interactor::Robot::destroy(){
    printf("destroy %d\n",this->id);
}

void Interactor::Robot::goingto(int Wp_id){
    
}