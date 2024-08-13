#ifndef AGENTS_H;
#define AGENTS_H;
#include <string>
using namespace std;

class Agent{
    public:
        Agent(string name , int AggroPoints , int ControlPoints , int MidRangeoints) : name(name) , AggroPoints(AggroPoints) , MidRangePoints(MidRangePoints) , ControlPoints(ControlPoints) {}
        string getName() const{return name;}
        int getAggro() const {return AggroPoints;}
        int getMid() const {return MidRangePoints;}
        int getControl() const {return ControlPoints;}
    private:
        string name;
        int AggroPoints , MidRangePoints , ControlPoints;
};
#endif