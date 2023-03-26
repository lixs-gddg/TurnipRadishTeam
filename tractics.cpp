#include "tactics.h"
#include "interact.h"
#include "calculate.h"
#include "goingto.h"

std::vector<std::vector<int>> wrkplcidx;
std::vector<std::vector<double>> wrkplc_distance;
std::list<order> global_list;
time_t time_begin;
void global_init()
{
    time_begin = time(NULL);
    // fprintf(stderr,"test1\n");
    wrkplcidx.resize(10);
    wrkplc_distance.resize(Interactor::curWrkplcNum, std::vector<double>(Interactor::curWrkplcNum));
    for (int i = 0; i < Interactor::curWrkplcNum; i++)
    {
        wrkplcidx[Interactor::wrkplc[i].type].push_back(i);
        for (int j = 0; j < Interactor::curWrkplcNum; j++)
        {
            if (Interactor::wrkplc[i].type != Interactor::wrkplc[j].type)
                wrkplc_distance[i][j] = cal_distance(Interactor::wrkplc[i].pos, Interactor::wrkplc[j].pos);
            else
                wrkplc_distance[i][j] = 100;
        }
    }
}

void check_wrkplc()
{
    // fprintf(stderr,"test2\n");
    for (int i = 7; i > 0; i--)
    {
        for (int j = 0; j < wrkplcidx[i].size(); j++)
        {
            int curidx = wrkplcidx[i][j];
            if (Interactor::wrkplc[curidx].remProdFrmNum == 1 && Interactor::wrkplc[curidx].MaterialEmpty().size() == 0 &&
                Interactor::wrkplc[curidx].prodState == 0)
            {
                Interactor::wrkplc[curidx].isOrder = false;
                Interactor::wrkplc[curidx].rawMaterial = 0;
            }
            add_order_wrkplc(curidx);
            add_order_global_list(curidx);

            fprintf(stderr, "global list size:%ld\n", global_list.size());
        }
    }
    // fprintf(stderr,"wrkplc 8 size:%ld\n",Interactor::wrkplc[8].orderList.size());
}

void check_robort(bool flag)
{
    // fprintf(stderr,"test3\n");
    for (int i = 0; i < 4; i++)
    {
        if (Interactor::rbt[i].curWrkplcId == Interactor::rbt[i].targetWrkplcId && Interactor::rbt[i].targetWrkplcId >= 0)
        {
            fprintf(stderr, "target:%d GoodsType:%d\n", Interactor::rbt[i].targetWrkplcId, Interactor::rbt[i].carriedGoodsType);
            if (Interactor::rbt[i].carriedGoodsType == 0)
            {
                if (Interactor::wrkplc[Interactor::rbt[i].curWrkplcId].prodState == 1 && flag)
                    Interactor::rbt[i].buy();
                else
                    Interactor::rbt[i].targetWrkplcId = -2;
            }
            else
            {
                Interactor::rbt[i].sell();
            }
        }

        
    }

    // avoid to collide
    for(int i = 0; i < Constant::Robot::RbtNum-1; i++){
        for(int j = i+1; j < Constant::Robot::RbtNum; j++){
            // will collide ?
            if(Interactor::rbt[i].willCollide(j)){
                avoid(i,j);
            }
        }
    }
    // fprintf(stderr,"wrkplc 8 size:%ld\n",Interactor::wrkplc[8].orderList.size());
}

void call_robort()
{
    // fprintf(stderr,"test4\n");
    for (int i = 0; i < 4; i++)
    {
        if (Interactor::rbt[i].targetWrkplcId == -2 && global_list.size() > 0)
        {
            auto it = global_list.begin();
            auto temp = it;
            double min_priority = cal_robot_priority(cal_distance(Interactor::rbt[i].pos,Interactor::wrkplc[it->fromidx].pos),wrkplc_distance[it->fromidx][it->toidx],Interactor::wrkplc[it->fromidx].type);
            while (it != global_list.end())
            {
                if (cal_robot_priority(cal_distance(Interactor::rbt[i].pos,Interactor::wrkplc[it->fromidx].pos),wrkplc_distance[it->fromidx][it->toidx],Interactor::wrkplc[it->fromidx].type)<min_priority)
                {
                    temp = it;
                }
                it++;
            }
            if (temp != global_list.end())
            {
                Interactor::rbt[i].targetWrkplcId = temp->fromidx;
                // Interactor::wrkplc[temp->fromidx].isGlobalOrder=false;
                it = global_list.erase(temp);
                exchange_order(i);
            }
        }
    }
    // fprintf(stderr,"wrkplc 8 size:%ld\n",Interactor::wrkplc[8].orderList.size());
}

int find_usable_wrkplc(int centeridx, int goal_type)
{
    // fprintf(stderr,"test5\n");
    if (centeridx < 0 || centeridx >= Interactor::curWrkplcNum || goal_type <= 0 || goal_type > 7 || wrkplcidx[goal_type].size() == 0)
        return -2;
    int result = wrkplcidx[goal_type][0];
    int curidx = result;
    double min_pri = wrkplc_distance[centeridx][result];
    double temp_pri;
    for (int i = 0; i < wrkplcidx[goal_type].size(); i++)
    {
        curidx = wrkplcidx[goal_type][i];
        temp_pri = cal_priority(wrkplc_distance[centeridx][curidx], Interactor::wrkplc[curidx].orderList.size());
        if (temp_pri < min_pri)
        {
            min_pri = temp_pri;
            result = curidx;
        }
    }
    // fprintf(stderr,"wrkplc 8 size:%ld\n",Interactor::wrkplc[8].orderList.size());
    return result;
}

int find_sell_wrkplc(int centeridx, int goal_type)
{
    // fprintf(stderr,"test6\n");
    if (wrkplcidx[goal_type].size() == 0)
        return -2;
    int result = wrkplcidx[goal_type][0];
    double min_dis = wrkplc_distance[centeridx][result];
    double temp_dis;
    for (int i = 1; i < wrkplcidx[goal_type].size(); i++)
    {
        temp_dis = wrkplc_distance[centeridx][wrkplcidx[goal_type][i]];
        if (temp_dis < min_dis)
        {
            temp_dis = min_dis;
            result = wrkplcidx[goal_type][i];
        }
    }
    // fprintf(stderr,"wrkplc 8 size:%ld\n",Interactor::wrkplc[8].orderList.size());
    return result;
}

double cal_priority(int distance, int size)
{
    return W1 * distance + W2 * size;
}

bool add_order_wrkplc(int centeridx)
{
    // fprintf(stderr,"test7\n");
    if (centeridx < 0 || centeridx >= Interactor::curWrkplcNum)
        return false;
    if (Interactor::wrkplc[centeridx].isOrder == true)
        return false;
    if (Interactor::wrkplc[centeridx].orderList.size() == 0 && Interactor::wrkplc[centeridx].type != 7 && wrkplcidx[7].size() >= 2)
        return false;
    if (Interactor::wrkplc[centeridx].type < 4 || Interactor::wrkplc[centeridx].type > 7)
        return false;
    std::vector<int> material = Interactor::wrkplc[centeridx].MaterialEmpty();
    for (int i = 0; i < material.size(); i++)
    {
        order order_add;
        order_add.toidx = centeridx;
        order_add.fromidx = find_usable_wrkplc(centeridx, material[i]);
        if (order_add.fromidx < 0 || order_add.fromidx >= Interactor::curWrkplcNum)
            continue;
        Interactor::wrkplc[order_add.fromidx].addOrder(order_add);
        fprintf(stderr, "wrk:%d order:%d -> %d type %d -> %d\n", order_add.fromidx, order_add.fromidx, order_add.toidx, Interactor::wrkplc[order_add.fromidx].type, Interactor::wrkplc[order_add.toidx].type);
    }
    Interactor::wrkplc[centeridx].isOrder = true;
    // fprintf(stderr,"wrkplc 8 size:%ld\n",Interactor::wrkplc[8].orderList.size());
    return true;
}

bool add_order_global_list(int centeridx)
{
    // fprintf(stderr,"test8\n");
    if (centeridx < 0 || centeridx >= Interactor::curWrkplcNum)
        return false;
    if (Interactor::wrkplc[centeridx].isGlobalOrder == true)
        return false;
    if (Interactor::wrkplc[centeridx].prodState == 0)
        return false;
    order order_add;
    if (Interactor::wrkplc[centeridx].type == 7)
    {
        order_add.fromidx = centeridx;
        order_add.toidx = find_sell_wrkplc(centeridx, 8);
        if (order_add.toidx == -2)
            order_add.toidx = find_sell_wrkplc(centeridx, 9);
        if (order_add.toidx == -2)
            return false;
        global_list.push_front(order_add);
        Interactor::wrkplc[centeridx].addOrder(order_add);
        Interactor::wrkplc[centeridx].isGlobalOrder = true;
        return true;
    }
    if (Interactor::wrkplc[centeridx].orderList.size() == 0)
        return false;
    order_add = Interactor::wrkplc[centeridx].orderList.front();
    global_list.push_back(order_add);
    Interactor::wrkplc[centeridx].isGlobalOrder = true;
    // fprintf(stderr,"wrkplc 8 size:%ld\n",Interactor::wrkplc[8].orderList.size());
    return true;
}

void do_tactics()
{
    time_t time_now = time(NULL);
    if (difftime(time_begin, time_now) <= 179)
        check_robort(true);
    else
        check_robort(false);
    check_wrkplc();
    call_robort();
    // fprintf(stderr,"test9\n");
    for (int i = 0; i < 4; i++)
    {
        goingto(Interactor::rbt[i].id, Interactor::rbt[i].targetWrkplcId);
        // fprintf(stderr,"wrkplc 8 size:%ld\n",Interactor::wrkplc[8].orderList.size());
    }
    // fprintf(stderr,"curframe:%d \nglobal_order_size:%ld\n",Interactor::curFrame,global_list.size());
    // for(int i=0;i<Interactor::curWrkplcNum;i++)
    // {
    //     fprintf(stderr,"wrkplc:%d order_size:%ld prodstatus:%d ",i,Interactor::wrkplc[i].orderList.size(),Interactor::wrkplc[i].prodState);
    //     if(Interactor::wrkplc[i].isGlobalOrder) fprintf(stderr,"true\n");
    //     else fprintf(stderr,"false\n");
    // }
}

double cal_robot_priority(double robot_to_distance, double wrkplc_distance, int type)
{
    return W1*wrkplc_distance+W2*(7-type)+W3*robot_to_distance;
}

bool exchange_order(int rbtidx)
{
    if(rbtidx<0 || rbtidx>3) return false;
    int tempidx=rbtidx;
    double min_distance=cal_distance(Interactor::rbt[rbtidx].pos,Interactor::wrkplc[Interactor::rbt[rbtidx].targetWrkplcId].pos);
    for(int i=0;i<4;i++)
    {
        if(rbtidx!=i && Interactor::rbt[i].carriedGoodsType==0 && cal_distance(Interactor::rbt[i].pos,Interactor::wrkplc[Interactor::rbt[i].targetWrkplcId].pos)>10)
        {
            double cur_distance=cal_distance(Interactor::rbt[i].pos,Interactor::wrkplc[Interactor::rbt[rbtidx].targetWrkplcId].pos);
            if(cur_distance<min_distance)
            {
                min_distance=cur_distance;
                tempidx=i;
            }
        }
    }
    if(tempidx!=rbtidx)
    {
        int temptarget=Interactor::rbt[tempidx].targetWrkplcId;
        Interactor::rbt[tempidx].targetWrkplcId=Interactor::rbt[rbtidx].targetWrkplcId;
        Interactor::rbt[rbtidx].targetWrkplcId=temptarget;
        return true;
    }
    return false;
}
