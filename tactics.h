#ifndef __tactics_H__
#define __tactics_H__

// #include"interact.h"
#include <limits.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <list>

#define W1 0.1
#define W2 1

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
void check_robort();

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

#endif