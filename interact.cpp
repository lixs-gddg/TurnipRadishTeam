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
    scanf("%s\n",end);


    if(strcmp(end,"OK")) return false;
    return true;
}