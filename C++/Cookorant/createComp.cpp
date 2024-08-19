#include <vector>
#include <utility>
#include<bits/stdc++.h>
#include <string>
#include <algorithm>
#include "agents.h"
using namespace std;

struct restrictions{
    int minAggroScore = 0, minControlScore = 0, minMidScore = 0;

    // Overload the > operator
    bool operator>(const restrictions& other) const {
        if(minAggroScore > other.minAggroScore && minControlScore > other.minControlScore && minMidScore > other.minMidScore){
            return true;
        }
        return false;
    }
};

//the idea is to evaluate possible scores, to make this tool usable for all types of comps and metas / updates the data will be read form the file agents.txt in the file parseDoc.cpp
//and from the file questions.txt in this file

// The comp will be calculated by scores, at this time the focus is to get the question values from the class agent that has been previously populated using the parseDoc
// We then get all of the scores placed in a vector of tuples where we have the pair <Agent , score> and then we apply the restriction of playstyle providing 3 possible comps.

//Future idea : Implement bonus for good agent combos

//Change of approach if we try to use the previous method it will be extremelly inneficient
//First we calculate all possible combinations of agents that fit the main criteria
//Then we check all those different options for the top 3 highest scores

bool sortSecondElement(const pair <Agent , int> a , const pair <Agent , int> b){
    return a.second > b.second;
}
bool sortSetElements (const pair<set<Agent> , int> a , const pair<set<Agent> , int> b){
    return a.second > b.second;
}

string createComp(vector<Agent> agentVec , vector<set<Agent>> possibleComps, vector<bool> answers , restrictions mainRestriction){
    vector<pair<int , int>> valueGroup;
    if (agentVec.size() == 0 ){
        return "There was an error reading the agents.txt file , make sure the file name is correct and the data inside it is up to date";
    }
    else if (answers.size() == 0){
        return "There was an error reading the questions.txt file , make sure the file name is correct and the data inside it is up to date";
    }
    cout << "Calculating scores" << endl;
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
        unit.setScore(sum);
    }
    cout << "Finished calculating scores" << endl;
    string result = "";
    restrictions restrictionScore;
    int compScore;
    unsigned int iter = 0;
    cout << "Evaluating main scores" << endl; 
    while(iter != possibleComps.size()){
            restrictionScore.minAggroScore = 0;
            restrictionScore.minControlScore = 0; 
            restrictionScore.minMidScore = 0;
            for (Agent unit : possibleComps[iter]){
                restrictionScore.minAggroScore += unit.getAggro();
                restrictionScore.minControlScore += unit.getControl();
                restrictionScore.minMidScore += unit.getMid();
            }
            if (!(restrictionScore > mainRestriction)){
                possibleComps.erase(possibleComps.begin() + iter);
            }
            else{
                iter++;
            }
    }
    vector<pair<set<Agent> , int>> compScoreVec;
    cout << "Evaluating secondary scores" << endl;
    for(set<Agent> comp : possibleComps){
        compScore = 0;
        for (Agent unit : comp){
            compScore += unit.getScore();
        }
        compScoreVec.push_back({comp , compScore});
    }
    sort(compScoreVec.begin() , compScoreVec.end() , sortSetElements);
    for(Agent unit : compScoreVec[0].first){
        result += unit.getName();
        result += " ";
    }
    result += "\n";
    for(Agent unit : compScoreVec[1].first){
        result += unit.getName();
        result += " ";
    }
    return result;
}

// the idea is to create a vector containing vectors o lenght 5 that has all possible combinations of agents without the order mattering
//This could be done using a vector of sets instead of a vector of vectors
//Given that at the time of making this script there are 24 agents , we can get a total of 42 thousand + combinations, which means this approach is highly inneficient;
//However, i cannot think of another one that would we significantly better.


// Function to generate the next combination
bool next_combination(vector<int>& indices, int n, int k) {
    int i = k - 1;
    while (i >= 0 && indices[i] == n - k + i) {
        i--;
    }
    if (i < 0) {
        return false;
    }
    indices[i]++;
    for (int j = i + 1; j < k; j++) {
        indices[j] = indices[j - 1] + 1;
    }
    return true;
}

vector<set<Agent>> possibleComps(restrictions mainValues, vector<Agent> agentsVec) {
    cout << "Calculating all possible comps\n";
    vector<set<Agent>> allPossibleComps;
    int n = agentsVec.size();
    int k = 5; // Number of agents to choose
    vector<int> indices(k);
    for (int i = 0; i < k; i++) {
        indices[i] = i;
    }

    do {
        set<Agent> temp;
        for (int i = 0; i < k; i++) {
            temp.insert(agentsVec[indices[i]]);
        }
        allPossibleComps.push_back(temp);
    } while (next_combination(indices, n, k));

    cout << "Finished calculating all possible comps\n";
    return allPossibleComps;
}