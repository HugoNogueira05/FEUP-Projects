#include <vector>
#include <utility>
#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include "agents.h"
using namespace std;


// Struct to hold the main restrictions for the creation of the team
struct restrictions{
    int minAggroScore = 0, minControlScore = 0, minMidScore = 0;

    // Overload the > operator
    bool operator>(const restrictions& other) const {
        if(minAggroScore >= other.minAggroScore && minControlScore >= other.minControlScore && minMidScore >= other.minMidScore){
            return true;
        }
        return false;
    }
};

// The idea is to evaluate possible scores, to make this tool usable for all types of comps and metas/updates the data will be read form the file agents.txt in the file parseDoc.hpp
//and from the file questions.txt in this file

// The comp will be calculated by scores, at this time the focus is to get the question values from the class agent that has been previously populated using the parseDoc
// We then get all of the scores placed in a vector of tuples where we have the pair <Agent , score> and then we apply the restriction of playstyle providing 2 possible comps.

//Future idea : Implement bonus for good agent combos

//Change of approach if we try to use the previous method it will be extremelly inneficient
//First we calculate all possible combinations of agents that fit the main criteria
//Then we check all those different options for the top 2 highest scores


//Function to sort focusing on the second element of the pair -> Used on the sort() function
inline bool sortSecondElement(const pair <Agent , int> a , const pair <Agent , int> b){
    return a.second > b.second;
}

//Function to sort focusing on the second element of the pair but inside a set -> Used on the sort() function
inline bool sortSetElements (const pair<vector<Agent> , int> a , const pair<vector<Agent> , int> b){
    return a.second > b.second;
}

//Function to sort the agents by score -> Used on the sort() function
inline const bool sortByScore(const Agent a , const Agent b) {
    return a.getScore() > b.getScore();
}

/**
 * @brief Function made to return the top 2 Agent combinations that fit the restrictions
 * 
 * @param possibleComps Vector containing all possible combinations of agents
 * @param mainRestriction Struct containing the main restrictions for the team
 * @return string String containing the top 2 Agent combinations that fit the restrictions
 */
inline string createComp(vector<vector<Agent>> possibleComps, restrictions mainRestriction) {
    string result = "";
    restrictions restrictionScore;
    int compScore;
    cout << "Evaluating main scores" << endl; 
    int counter = 0;

    // Delete the combinations that do not fit the main restrictions
    auto it = possibleComps.begin();
    while (it != possibleComps.end()) {
        restrictionScore.minAggroScore = 0;
        restrictionScore.minControlScore = 0;
        restrictionScore.minMidScore = 0;

        for (const Agent& unit : *it) {
            restrictionScore.minAggroScore += unit.getAggro();
            restrictionScore.minControlScore += unit.getControl();
            restrictionScore.minMidScore += unit.getMid();
        }

        if (mainRestriction.minAggroScore > restrictionScore.minAggroScore || mainRestriction.minControlScore > restrictionScore.minControlScore || mainRestriction.minMidScore > restrictionScore.minMidScore){
            it = possibleComps.erase(it);
        }
        else {
            it++;
        }
    }

    vector<pair<vector<Agent>, int>> compScoreVec;
    cout << "Evaluating secondary scores" << endl;
    // Calculate the score for each combination
    for (const vector<Agent>& comp : possibleComps) {
        if (comp.size() < 5) {
            continue;
        }
        compScore = 0;
        for (const Agent& unit : comp) {
            compScore += unit.getScore();
        }
        compScoreVec.push_back({ comp, compScore });
    }

    // Sort the combinations by score
    sort(compScoreVec.begin(), compScoreVec.end(), sortSetElements);

    // Return the top 2 combinations
    if (compScoreVec.size() > 0) {
        for (const Agent& unit : compScoreVec[0].first) {
            result += unit.getName();
            result += " ";
        }
        result += "\n";
    }
    if (compScoreVec.size() > 1) {
        for (const Agent& unit : compScoreVec[1].first) {
            result += unit.getName();
            result += " ";
        }
    }
    return result;
}

/**
 * @brief Function that returns all possible combinations of agents
 * 
 * @param agentsVec vector containing all agents that will participate in the combinations
 * @return vector<vector<Agent>> returns a vector containing all possible combinations of agents
 */
inline vector<vector<Agent>> possibleComps(vector<Agent> agentsVec) {
    cout << "Calculating all possible comps\n";
    vector<vector<Agent>> allPossibleComps;

    // Vector to store binary representation for combinations
    vector<bool> select(5, true);  // First 5 elements set to true
    select.resize(10, false);           // Remaining 5 elements set to false

    int combination_count = 0;

    // This approach used a binary representation to calculate all possible combinations
    //using the function prev_permutation() from the algorithm library
    
    // Note that in this case we are using a fixed number of agents (10) to ensure that the program isn't too heavy

    do {
        vector<Agent> comp;
        for (int i = 0; i < 10; i++) {
            if (select[i]) {
                comp.push_back(agentsVec[i]);
            }
        }
        allPossibleComps.push_back(comp);
        comp.clear();
    } while (prev_permutation(select.begin(), select.end()));

    cout << "Finished calculating all possible comps\n";
    return allPossibleComps;
}