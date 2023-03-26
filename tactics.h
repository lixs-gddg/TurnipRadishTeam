#ifndef __tactics_H__
#define __tactics_H__

// #include"interact.h"
#include <limits.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <list>
#include <time.h>

#define W1 0.8
#define W2 1.5
#define W3 2
#define W4 1
typedef struct order_t
{
    int fromidx;
    int toidx;
} order;

// init the wrkplcidx and wrkplc_distance
void global_init();

// check the status of the wrkplc and decision
void check_wrkplc();

// check the status of the robort and decision
void check_robort(bool flag);

// call robort to take global_order
void call_robort();

// find the highest priorty wrkplc;
int find_usable_wrkplc(int centeridx, int goal_type);

// find 8 or 9 type wrkplc to sell
int find_sell_wrkplc(int centeridx, int goal_type);

// calculate the priority of the wrkplc
double cal_priority(int distance, int size);

// add order to wrkplc
bool add_order_wrkplc(int centeridx);

// add order to global_list
bool add_order_global_list(int centeridx);

void do_tactics();

double cal_robot_priority(double robot_to_distance,double wrkplc_distance,int type,double angle);

bool exchange_order(int rbtidx);

#endif