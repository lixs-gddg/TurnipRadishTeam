#ifndef __tactics_H__
#define __tactics_H__

#include"interact.h"
#include<cmath>
#include<algorithm>
#include<iostream>
#include<list>

typedef struct order_t{
    int fromidx;
    int toidx;
}order;

bool global_init();
double count_distance(int a,int b);
int find_nearest_index(int center,int goal_type);
#endif