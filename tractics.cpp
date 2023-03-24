#include"tactics.h"
#include"interact.h"
#include"calculate.h"
#include"goingto.h"

std::vector<std::vector<int>> wrkplcidx;
std::vector<std::vector<double>> wrkplc_distance;
std::list<order> global_list;
bool global_init()
{
    //fprintf(stderr,"test1\n");
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
                wrkplc_distance[i][j]=100;
        }
    }
    /*for(int i=1;i<10;i++)
    {
        fprintf(stderr,"type:%d index:",i);
        for(int j=0;j<wrkplcidx[i].size();j++)
        {
            fprintf(stderr,"%d ",wrkplcidx[i][j]);
        }
        fprintf(stderr,"\n");
    }
    fprintf(stderr,"distance:\n");
    for(int i=0;i<Interactor::curWrkplcNum;i++)
    {
        for(int j=0;j<Interactor::curWrkplcNum;j++)
        {
            fprintf(stderr,"%6lf ",wrkplc_distance[i][j]);
        }
        fprintf(stderr,"\n");
    }*/
    return true;
}

double priorty_cal(double distance,int size)
{
    //0.1 means weight.
    //fprintf(stderr,"test2\n");
    return 0.1*distance+size;
}

int find_useable_wrkplc(int center,int goal_type)
{
    //fprintf(stderr,"test3\n");
    if(wrkplcidx[goal_type].size()==0) return -2;
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

int find_sell_wrkplc(int center)
{
    //fprintf(stderr,"test4\n");
    if(wrkplcidx[8].size()+wrkplcidx[9].size()==0) return -2;
    int result;
    if(wrkplcidx[8].size()>0) result=wrkplcidx[8][0];
    else result=wrkplcidx[9][0];
    double min_dis=wrkplc_distance[center][result];
    double temp_dis;
    for(int i=8;i<10;i++)
    {
        for(int j=0;j<wrkplcidx[i].size();j++)
        {
            temp_dis=wrkplc_distance[center][wrkplcidx[i][j]];
            if(temp_dis<min_dis)
            {
                min_dis=temp_dis;
                result=wrkplcidx[i][j];
            }
        }
    }
    return result;
}

void check_robot()
{
    //fprintf(stderr,"test5\n");
    for(int i=0;i<4;i++)
    {
        if(Interactor::rbt[i].curWrkplcId==Interactor::rbt[i].targetWrkplcId && Interactor::rbt[i].targetWrkplcId>=0)
        {
            if(Interactor::rbt[i].carriedGoodsType==0)
            {
                if(Interactor::wrkplc[Interactor::rbt[i].curWrkplcId].prodState==1)
                    Interactor::rbt[i].buy();
                else
                    Interactor::rbt[i].targetWrkplcId=-2;
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
    //fprintf(stderr,"test6\n");
    std::vector<int> Material_type;
    for(int i=7;i>3;i--)
    {
        for(int j=0;j<wrkplcidx[i].size();j++)
        {
            if(Interactor::wrkplc[wrkplcidx[i][j]].orderList.size()>0 && Interactor::wrkplc[wrkplcidx[i][j]].prodState==1 && Interactor::wrkplc[wrkplcidx[i][j]].isGlobalOrder==false)
            {
                if(i<7)
                {
                    std::list<order>::iterator it = global_list.begin();
                    while(it!=global_list.end())
                    {
                        if(Interactor::wrkplc[it->fromidx].type < Interactor::wrkplc[wrkplcidx[i][j]].type) break;
                        it++;
                    }
                    if(it!=global_list.end()) it=global_list.insert(it,Interactor::wrkplc[wrkplcidx[i][j]].orderList.front());
                    else global_list.push_back(Interactor::wrkplc[wrkplcidx[i][j]].orderList.front());
                }
                else
                {
                    order ins;
                    ins.fromidx=wrkplcidx[i][j];
                    ins.toidx=find_sell_wrkplc(ins.fromidx);
                    global_list.push_front(ins);
                }
                Interactor::wrkplc[wrkplcidx[i][j]].isGlobalOrder=true; 
            }
            if(Interactor::wrkplc[wrkplcidx[i][j]].isOrder==true) continue;
            Material_type=Interactor::wrkplc[wrkplcidx[i][j]].MaterialEmpty();
            for(int k=0;k<Material_type.size();k++)
            {
                int target_idx=find_useable_wrkplc(wrkplcidx[i][j],Material_type[k]);
                order temp;
                temp.fromidx=target_idx;
                temp.toidx=wrkplcidx[i][j];
                Interactor::wrkplc[target_idx].addOrder(temp);
            }
            Interactor::wrkplc[wrkplcidx[i][j]].isOrder=true;
        }
    }
    for(int i=3;i>0;i--)
    {
        for(int j=0;j<wrkplcidx[i].size();j++)
        {
            if(Interactor::wrkplc[wrkplcidx[i][j]].orderList.size()>0 && Interactor::wrkplc[wrkplcidx[i][j]].prodState==1 && Interactor::wrkplc[wrkplcidx[i][j]].isGlobalOrder==false)
            {
                std::list<order>::iterator it = global_list.begin();
                while(it!=global_list.end())
                {
                    if(Interactor::wrkplc[it->fromidx].type < Interactor::wrkplc[wrkplcidx[i][j]].type) break;
                    it++;
                }
                if(it!=global_list.end()) it=global_list.insert(it,Interactor::wrkplc[wrkplcidx[i][j]].orderList.front());
                else global_list.push_back(Interactor::wrkplc[wrkplcidx[i][j]].orderList.front());
                Interactor::wrkplc[wrkplcidx[i][j]].isGlobalOrder=true;
            }
        }
    }
    // fprintf(stderr,"curFrame:%d\n",Interactor::curFrame);
    // for(int i=0;i<Interactor::curWrkplcNum;i++)
    // {
    //     fprintf(stderr,"wrkplc%d size:%ld :",i,Interactor::wrkplc[i].orderList.size());
    //     for(auto it=Interactor::wrkplc[i].orderList.begin();it!=Interactor::wrkplc[i].orderList.end();it++)
    //     {
    //         fprintf(stderr,"%d->%d ",it->fromidx,it->toidx);
    //     }
    //     fprintf(stderr,"\n");
    // }
}

void call_robot()
{
    //fprintf(stderr,"test7\n");
    if(global_list.size()==0) return;
    for(int i=0;i<4;i++)
    {
        if(Interactor::rbt[i].targetWrkplcId==-2 && global_list.size()>0)
        {
            bool flag=true;
            std::list<order>::iterator it=global_list.begin();
            while(it!=global_list.end())
            {
                if(cal_distance(Interactor::rbt[i].pos,Interactor::wrkplc[it->fromidx].pos)<100)
                {
                    Interactor::rbt[i].targetWrkplcId=it->fromidx;
                    it=global_list.erase(it);
                    flag=false;
                    break;
                }
                it++;
            }
            if(flag)
            {
                it=global_list.begin();
                Interactor::rbt[i].targetWrkplcId=it->fromidx;
                it=global_list.erase(it);
            }
        }
    }
}

void do_tactics()
{
    
    check_robot();
    check_wrkplc();
    call_robot();
    //fprintf(stderr,"test8\n");
    for(int i=0;i<4;i++)
    {
        goingto(Interactor::rbt[i].id,Interactor::rbt[i].targetWrkplcId);
        //fprintf(stderr,"robot%d to:%d\n",i,Interactor::rbt[i].targetWrkplcId);
    }
    fprintf(stderr,"curframe:%d global_list size:%ld\n",Interactor::curFrame,global_list.size());
}

// void sprintorder()
// {
//     fprintf(stderr,"global_list size:%ld\n",global_list.size());
//     for(std::list<order>::iterator it=global_list.begin();it!=global_list.end();it++)
//     {
//         fprintf(stderr,"order:%d -> %d type: |%d|-> |%d|\n",it->fromidx,it->toidx,Interactor::wrkplc[it->fromidx].type,Interactor::wrkplc[it->toidx].type);
//     }
// }

