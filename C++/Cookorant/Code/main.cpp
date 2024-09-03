#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include "createComp.hpp"
#include "parseDoc.hpp"
using namespace std;

// The idea is to use questions to get a playstyle as well as some key agents needed, then we can exclude and evaluate which score is higher


// Auxiliary Function definition
int detectPlaystyle(int playstyle = 0);
void convert(string& word);
vector<bool> specificParam(string fileName);
bool createScores(vector<Agent>& agentVec, vector<bool> answers);


// It will follow this process : main() -> Read agents file -> read questions -> associate questions with agents -> get the top 10 agents -> possible combinations with those 10
// -> evaluate teams top score -> print out team 


int main(){
    vector<Agent> dataVec;
    vector<bool> answersVec;
    int playstyleVal = 0; 
    playstyleVal = detectPlaystyle();
    struct restrictions scores;
    //Define the base values to finally create the comp
    //This could be implemented in an auxiliary function if needed
    switch (playstyleVal){
        case 12: 
            scores.minControlScore = 13;
            scores.minAggroScore = 16;
            break;
        case 13:
            scores.minMidScore = 13;
        case 10:
            scores.minAggroScore = 16;
            break;
        case 21:
            scores.minAggroScore = 13;
            scores.minControlScore = 16;
            break;
        case 23:
            scores.minMidScore = 13;
        case 20:
            scores.minControlScore = 16;
            break;
        case 31:
            scores.minAggroScore = 13;
            scores.minMidScore = 16;
            break;
        case 32:
            scores.minControlScore = 13;
        case 30:
            scores.minMidScore = 16;
            break;
        default:
            cout << "There appears to be an error when calculating your playstyle please try again.\n";
            return 0;
    }
    dataVec = parseFile("agents.txt"); // Read the agents file
    answersVec = specificParam("questions.txt"); // Read the questions file
    bool scoreValid = createScores(dataVec, answersVec); //Check if the files were read correctly
    if (!scoreValid) {
        return 0;
    }

    // Get the top 10 scoring agents to improve performance (This can be changed if needed)
    vector<Agent> filteredAgents;
    for (unsigned int iter = 0; iter < 10; iter++) {
        
        filteredAgents.push_back(dataVec[iter]);

    }

    // All possible combinations with the top 10 set above
    vector<vector<Agent>> possibleCombinations = possibleComps(filteredAgents);
    string temp = createComp( possibleCombinations , scores); // Get the top 2 combinations
    cout << temp << endl;
	cout << "Press any key to exit" << endl;
    cin >> temp;
    return 0;
    
}

// Auxiliary functions
/**
 * @brief Function used to convert a string to uppercase
 * 
 * @param word string passed as a reference to make the code more readable and easier to write
 */
void convert(string& word){
    for (char& c : word){
        c = toupper(c);
    }
}

/**
 * @brief As the name suggests this function is used to determine the main playstyle the player wants their comp to lean into, 
 * using integers we can filter the playstyle and the substyle.
 * 
 * 
 * @param playstyle This variable is used kind of as a flag, it saves the user from having the answer all the questions all over again if
 * he messes up whyle answering
 * 
 * @return int This value is used to save the playstyle he wanted to build.
 */

int detectPlaystyle(int playstyle){
    string answer = "";
    if (playstyle == 0){
        cout << " What style do you want to lean into?\n   [1] Aggressive\n   [2] Control\n   [3] MidRange\n";
        cin >> answer;
        convert(answer);
        if (answer == "AGGRESSIVE" || answer == "AGGRO" || answer == "1"){
            playstyle = 10;
        }
        else if  (answer == "CONTROL" || answer == "2"){
            playstyle = 20;
        }
        else if (answer == "MIDRANGE" || answer == "MID" || answer == "3"){
            playstyle = 30;
        }
        else{
            cout << "Please use one of the numbers or the name provided" << endl;
            return detectPlaystyle();
        }
    }
    cout <<  "Do you want to lean into a sub-style?\n  Y/N" << endl;
    cin >> answer;
    convert(answer);
    if (answer == "Y" || answer == "YES"){
        cout << "What sub-style do you want to lean into?\n";
        switch(playstyle){
        case 10:
            cout << "   [1] Control\n   [2] MidRange\n";
            cin >> answer;
            convert(answer);
            if (answer == "1" || answer == "CONTROL"){
                playstyle = 12;
            }
            else if (answer == "2" || answer == "MID" || answer == "MIDRANGE"){
                playstyle = 13;
            }
            else{
                cout << "Please choose one of the available options\n";
                return detectPlaystyle(playstyle);
            }
            break;
        case 20:
            cout << "   [1] Aggressive\n   [2] MidRange\n";
            cin >> answer;
            convert(answer);
            if (answer == "1" || answer == "AGGRO" || answer == "AGGRESSIVE"){
                playstyle = 21;
            }
            else if (answer == "2" || answer == "MID" || answer == "MIDRANGE"){
                playstyle = 23;
            }
            else{
                cout << "Please choose one of the available options\n";
                return detectPlaystyle(playstyle);
            }
            break;
        case 30:
            cout << "   [1] Aggressive\n   [2]Control\n";
            cin >> answer;
            convert(answer);
            if (answer == "1" || answer == "AGGRO" || answer == "AGGRESSIVE"){
                playstyle = 31;
            }
            else if (answer == "2" || answer == "CONTROL"){
                playstyle = 32;
            }
            else{
                cout << "Please choose one of the available options\n";
                return detectPlaystyle(playstyle);
            }
            break;
        default:
            return detectPlaystyle();
        }
    }
    else if (answer != "N" && answer != "NO"){
        cout << "Please answer with Y or N\n";
        return detectPlaystyle(playstyle);
    }
    return playstyle;
}

/**
 * @brief Function used to get the answers from the user for the specific questions and populate a bool vector with the answers
 * 
 * @param fileName string containing the name of the file to read the questions from
 * @return vector<bool> Vecgtor containing the answers to the questions
 */

vector<bool> specificParam(string fileName){
    vector<bool> answers;
    ifstream input(fileName);
    string line , number , answer;
    while (getline(input , line)){
        string c = line.substr(0 , 1);
        if (c == "A" || c == " " || c == "/"){
            continue;
        }
        else{
            cout << line << endl;
            cin >> answer;
            if (answer == "yes" || answer == "Yes" || answer == "y" || answer == "Y"){
                answers.push_back(true);
            }
            else if(answer == "no" || answer == "No" || answer == "N" || answer == "n"){
                answers.push_back(false);
            }
            else{
                cout <<" please answer with Yes or No" << endl;
                return specificParam(fileName);
            }
        }
    }
    return answers;
}


/**
 * @brief Function used to create the scores for each agent based on the answers given by the user
 * 
 * 
 * @param agentVec Vector containing all the agents read from agents.txt
 * @param answers Vector containing all the answers to the questions (Created in the specificParam function)
 * @return true The function was able to create the scores
 * @return false There was an error reading the files
 */
bool createScores(vector<Agent>& agentVec, vector<bool> answers) {
    vector<pair<int, int>> valueGroup;
    if (agentVec.size() == 0) {
        cout << "There was an error reading the agents.txt file , make sure the file name is correct and the data inside it is up to date";
        return false;
    }
    else if (answers.size() == 0) {
        cout << "There was an error reading the questions.txt file , make sure the file name is correct and the data inside it is up to date";
        return false;
    }
    cout << "Calculating scores" << endl;
    for (Agent& unit : agentVec) {
        int sum = 0;
        valueGroup = unit.getValueGroup();
        for (unsigned int iter = 0; iter < answers.size() && iter < valueGroup.size(); iter++) {
            if (answers[iter] == 1) {
                sum += valueGroup[iter].first;
            }
            else {
                sum += valueGroup[iter].second;
            }
        }
        unit.setScore(sum);
    }
    cout << "Finished calculating scores" << endl;
    sort(agentVec.begin(), agentVec.end(), sortByScore);
    return true;
}