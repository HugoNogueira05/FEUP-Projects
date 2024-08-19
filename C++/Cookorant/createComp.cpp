#include <vector>
#include <utility>
#include<bits/stdc++.h>
#include <string>
#include "agents.h"
using namespace std;

struct restrictions{
    int minAggroScore = 0, minControlScore = 0, minMidScore = 0;
};


//the idea is to evaluate possible scores, to make this tool usable for all types of comps and metas / updates the data will be read form the file agents.txt in the file parseDoc.cpp
//and from the file questions.txt in this file

// The comp will be calculated by scores, at this time the focus is to get the question values from the class agent that has been previously populated using the parseDoc
// We then get all of the scores placed in a vector of tuples where we have the pair <Agent , score> and then we apply the restriction of playstyle providing 3 possible comps.

//Future idea : Implement bonus for good agent combos

bool sortSecondElement(const pair <Agent , int> a , const pair <Agent , int> b){
    return a.second > b.second;
}


string createComp(vector<Agent> agentVec , struct restrictions  , vector<bool> answers){
    vector<pair<Agent , int>> scoreVec;
    vector<pair<int , int>> valueGroup;
    if (agentVec.size() == 0 ){
        return "There was an error reading the agents.txt file , make sure the file name is correct and the data inside it is up to date";
    }
    else if (answers.size() == 0){
        return "There was an error reading the questions.txt file , make sure the file name is correct and the data inside it is up to date";
    }
    for (Agent unit : agentVec){
        int sum = 0;
        valueGroup = unit.getValueGroup();
        for (unsigned int iter = 0 ; iter < answers.size() && iter < valueGroup.size() ; iter++){
            if (answers[iter] == 1){
                sum += valueGroup[iter].first;
            }
            else{
                sum += valueGroup[iter].second;
            }
        }
        scoreVec.push_back({unit , sum});
    }
    sort(scoreVec.begin() , scoreVec.end() , sortSecondElement);
    string result = "";
    int totalScore = 0;
    for (unsigned int temp = 0 ; temp < 5 ; temp++){
        result += scoreVec[temp].first.getName();
        result += " ";
        totalScore += scoreVec[temp].second;
    }
    return result + "Total Score: " + to_string(totalScore);
    }




