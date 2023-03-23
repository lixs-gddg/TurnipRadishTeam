#ifndef __tactics_H__
#define __tactics_H__

// #include"interact.h"
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

// check if robots are able to do buy or sell;
void check_robot();

// check if workplaces are able to provide goods and send the order to global list; 
void check_wrkplc();

// call available robots to take orders from global_list;
void call_robot();

// tactics
void  do_tactics();
#endif