#ifndef AGENTS_H
#define AGENTS_H
#include <string>
#include <utility>
using namespace std;

class Agent{
    public:
        Agent(string name , int AggroPoints , int ControlPoints , int MidRangePoints , vector<pair<int , int>> answerVals ) : name(name) , AggroPoints(AggroPoints) , MidRangePoints(MidRangePoints) , ControlPoints(ControlPoints) , answerVals(answerVals) {}
        string getName() const{return name;}
        int getAggro() const {return AggroPoints;}
        int getMid() const {return MidRangePoints;}
        int getControl() const {return ControlPoints;}
        void PrintValueGroup() const {for (pair<int , int> value: answerVals){cout << value.first << " " << value.second << " / ";}}
    private:
        string name;
        int AggroPoints , MidRangePoints , ControlPoints;
        vector <pair <int , int>> answerVals;

};
#endif