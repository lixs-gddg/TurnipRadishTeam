#ifndef __INTERACT_H__
#define __INTERACT_H__

#include "const.h"
#include "tactics.h"
#include <vector>
#include <list>

class Interactor{
public:
    Interactor(){}
    ~Interactor(){}
    static bool readFrame();

    class Coord{
    public:
        Coord(){}
        Coord(double x,double y);

        double x,y;
    };


    class Robot{
    public:
        Robot(){}

        Robot(int id);

        // velocity
        void forward(double v);

        // angular velocity
        void rotate(double av);

        void buy();

        void sell();

        void destroy();
    // private:
        // robot id
        int id;
        // postion coordinate
        Coord pos;
        // the direction which this robot is facing
        double direction;
        // line velocity
        std::vector<double> lnVelocity = std::vector<double>(2);
        // angular velocity
        double angVelocity;
        // id of workplace which this robot is in
        int curWrkplcId;
        // type of carried goods
        int carriedGoodsType;
        // Time Value Coefficient
        double TVC;
        // Collision Value Coefficient
        double CVC;
        // target workplace
        int targetWrkplcId = -2;
    };

    class Workplace{
    public:
        Workplace(){}

        int type;
        // workplace postion
        Coord pos;
        // remained production frame num
        int remProdFrmNum;
        // raw material displayed in bits
        int rawMaterial;
        // product state in 0 or 1
        int prodState;

        bool isOrder = false;

        std::list<order> orderList;

        void addOrder(const order& o);

        std::vector<int> MaterialEmpty();
    };

    // current frame sequence
    static int curFrame;
    // current money
    static int curMoney;
    // workplace num of current frame
    static int curWrkplcNum;
    // robot object
    static Robot rbt[Constant::Robot::RbtNum];
    // workplace object
    static Workplace wrkplc[Constant::Workplace::MaxWrkplcNum];

};

#endif