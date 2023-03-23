#ifndef __CONST_H__
#define __CONST_H__
#include <cmath>
#include <vector>

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
        static constexpr double MaxForwardVelocity = 6;
        static constexpr double MinForwardVelocity = -2;
        static constexpr double MaxAngularVelocity = M_PI;
        static constexpr double MinAngularVelocity = -M_PI;
    };

    class Workplace{
    public:
        // workplace max num
        static const int MaxWrkplcNum = 50;
        static std::vector<int> goodsMap;

    };
    
    


};

#endif