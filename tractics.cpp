#include"tactics.h"

std::vector<std::vector<int>> wrkplcidx;
std::vector<std::vector<double>> wrkplc_distance;

bool global_init()
{
    wrkplcidx.resize(10);
    wrkplc_distance.resize(Interactor::curWrkplcNum,std::vector<double> (Interactor::curWrkplcNum));
    for(int i=0;i<Interactor::curWrkplcNum;i++)
    {
        wrkplcidx[Interactor::wrkplc[i].type].push_back(i);
        for(int j=0;j<Interactor::curWrkplcNum;j++)
        {
            if(Interactor::wrkplc[i].type!=Interactor::wrkplc[j].type)
                wrkplc_distance[i][j]=cal_distance(Interactor::wrkplc[i].pos,Interactor::wrkplc[j].pos);
            else
                wrkplc_distance[i][j]=3000;
        }
    }
    return true;
}

double priorty_cal(double distance,int size)
{
    return 0.1*distance+size;
}

int find_useable_wrkplc(int center,int goal_type)
{
    if(wrkplcidx[goal_type].size()==0) return -1;
    int result=wrkplcidx[goal_type][0];
    double min_priorty=priorty_cal(wrkplc_distance[center][result],Interactor::wrkplc[result].orderList.size());
    double temp_priorty;
    for(int i=0;i<wrkplcidx[goal_type].size();i++)
    {
        temp_priorty=priorty_cal(wrkplc_distance[center][wrkplcidx[goal_type][i]],Interactor::wrkplc[wrkplcidx[goal_type][i]].orderList.size());
        if(temp_priorty<min_priorty)
        {
            result=wrkplcidx[goal_type][i];
            min_priorty=temp_priorty;
        }
    }
    return result;
}

void check_robot()
{
    for(int i=0;i<4;i++)
    {
        if(Interactor::rbt[i].curWrkplcId==Interactor::rbt[i].targetWrkplcId)
        {
            if(Interactor::rbt[i].carriedGoodsType==0)
            {
                Interactor::rbt[i].buy();
            }
            else
            {
                Interactor::rbt[i].sell();
            }
        }
    }
}

void check_wrkplc()
{
    std::vector<int> Material_type;
    for(int i=7;i>0;i++)
    {
        for(int j=0;j<wrkplcidx[7].size();j++)
        {
            
        }
    }
}




