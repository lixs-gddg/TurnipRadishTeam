#include <iostream>
#include <cstring>
#include <fstream>
#include "interact.h"
#include "tactics.h"

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
    printf("buy %d\n",this->id);
    // if(Interactor::wrkplc[curWrkplcId].orderList.size()<=0) 
    // {
    //     targetWrkplcId =-2;
    //     return;
    // }
    Interactor::wrkplc[curWrkplcId].isGlobalOrder=false;
    if(Interactor::wrkplc[targetWrkplcId].MaterialEmpty().size()==0)
        Interactor::wrkplc[curWrkplcId].isOrder=false;
    targetWrkplcId = Interactor::wrkplc[curWrkplcId].orderList.front().toidx;
    Interactor::wrkplc[curWrkplcId].orderList.pop_front();
}

void Interactor::Robot::sell(){
    printf("sell %d\n",this->id);
    Interactor::wrkplc[targetWrkplcId].rawMaterial|=(1<<carriedGoodsType);
    fprintf(stderr,"remain material num:%ld\n",
        Interactor::wrkplc[targetWrkplcId].MaterialEmpty().size());
    if(Interactor::wrkplc[targetWrkplcId].MaterialEmpty().size()==0 && Interactor::wrkplc[targetWrkplcId].prodState==0){
        Interactor::wrkplc[curWrkplcId].isOrder=false;
        Interactor::wrkplc[curWrkplcId].rawMaterial=0;
        // fprintf(stderr,"wrokplace id:%d type:%d can give order again!yyyyyyeeeeaaaahhhhh!!!\n\n",
        // targetWrkplcId,Interactor::wrkplc[targetWrkplcId].type);
    }
    targetWrkplcId = -2;
}

void Interactor::Robot::destroy(){
    printf("destroy %d\n",this->id);
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
