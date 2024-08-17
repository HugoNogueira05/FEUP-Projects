#include <vector>
#include <utility>
#include <string>
#include "agents.h"
using namespace std;

struct restrictions{
    int minAggroScore = 0, minControlScore = 0, minMidScore = 0;
};


//the idea is to evaluate possible scores, still not sure how to do it , but i will

string createComp(vector<Agent> agentVec , struct restrictions ){
    if (agentVec.size() == 0){
        return "There was an error reading the file , make sure the file name is correct and the data inside it is up to date";
    }
    else{

    }

}

