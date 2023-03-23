#ifndef __tactics_H__
#define __tactics_H__

#include"interact.h"
#include"calculate.h"
#include<limits.h>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<list>

typedef struct order_t{
    int fromidx;
    int toidx;
}order;

bool global_init();
double priorty_cal(double distance,int size);
int find_useable_wrkplc(int center,int goal_type);
void check_robot();
void check_wrkplc();
#endif