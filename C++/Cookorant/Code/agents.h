#ifndef AGENTS_H
#define AGENTS_H
#include <string>
#include <utility>
#include <vector>
using namespace std;

//Class agent that holds the name, the points of the agent and the answers of the specific questions
class Agent{
    public:
    //Constructor
        Agent(string name , int AggroPoints , int ControlPoints , int MidRangePoints , vector<pair<int , int>> answerVals ) : name(name) , AggroPoints(AggroPoints) , MidRangePoints(MidRangePoints) , ControlPoints(ControlPoints) , answerVals(answerVals) {}
        //Getters
        string getName() const{return name;}
        int getAggro() const {return AggroPoints;}
        int getMid() const {return MidRangePoints;}
        int getControl() const {return ControlPoints;}
        vector<pair<int , int>> getValueGroup() const{return answerVals;}
        int getScore() const {return score;}
        void PrintValueGroup() const {for (pair<int , int> value: answerVals){cout << value.first << " " << value.second << " / ";}}
       
        //Setters
        void setScore( int val) { score = val;}

        //Operator overloading
         bool operator<(const Agent other) const {
        return this->AggroPoints < other.getAggro();
         }

    private:
        string name;
        int AggroPoints , MidRangePoints , ControlPoints , score = 0;
        vector <pair <int , int>> answerVals;

};
#endif