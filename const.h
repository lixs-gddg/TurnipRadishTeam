#ifndef __CONST_H__
#define __CONST_H__
#include <cmath>

class Constant{
public:
    class Map{
    public:
        static const int row = 100,col = 100;
        static const int height = 50, width = 50;
    };

    class Robot{
    public:
        // robot num
        static const int RbtNum = 4;
        static const double MaxForwardVelocity = 6;
        static const double MinForwardVelocity = -2;
        static const double MaxAngularVelocity = M_PI;
        static const double MinAngularVelocity = -M_PI;
    };

    class Workplace{
    public:
        // workplace max num
        static const int MaxWrkplcNum = 50;
    };
    
    


};

#endif