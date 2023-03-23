#include"tactics.h"

std::vector<std::vector<int>> wrkplcidx;

bool global_init()
{
    wrkplcidx.resize(10);
    for(int i=0;i<Interactor::curWrkplcNum;i++)
    {
        wrkplcidx[Interactor::wrkplc[i].type].push_back(i);
    }
    return true;
}

double count_distance(int a,int b)
{
    double ax=Interactor::wrkplc[a].pos.x;
    double ay=Interactor::wrkplc[a].pos.y;
    double bx=Interactor::wrkplc[b].pos.x;
    double by=Interactor::wrkplc[b].pos.y;
    return pow(ax-bx,2)+pow(ay-by,2);
}

int find_nearest_index(int center,int goal_type)
{
    int result=wrkplcidx[goal_type][0];
    //fprintf(stderr,"goaltype:%d result_type:%d\n",goal_type,Interactor::wrkplc[result].type);
    double mindistance=count_distance(center,wrkplcidx[goal_type][0]);
    for(int i=1;i<wrkplcidx[goal_type].size();i++)
    {
        double temp=count_distance(center,wrkplcidx[goal_type][i]);
        if(temp<mindistance)
        {
            mindistance=temp;
            result=wrkplcidx[goal_type][i];
        }
    }
    return result;
}





