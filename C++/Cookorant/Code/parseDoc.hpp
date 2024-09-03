#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "agents.h"
using namespace std;


//Function to convert a string to an integer -> Only works for strings that are integers
// In retrospective I could have just used Stoi but I didn't remember at the time and now it's done

inline int stringToInt(string str){
    int sum = 0;
    for(char c : str){
        sum = sum + c - 48; // 48 is the decimal for 0 in ascii
        sum = sum * 10 ;
    }
    return sum / 10;
}

/**
 * @brief Function to read the agents file and return a vector of agents
 * 
 * @param fileName string containing the name of the file to be read
 * @return vector<Agent> vector containing all the agents
 */
inline vector<Agent> parseFile(string fileName){
    vector <Agent> agentArr;
    vector <pair<int , int>> valueGroup;
    ifstream input(fileName);
    if (!input.is_open()){
        cout << "File does not exist or is in the wrong directory, please make sure that the file agents.txt is inside the directory called Data\n";
        return agentArr;
    }
    else{
        string line = "";
        while(getline(input, line)){
            valueGroup.clear();
            if (line == "" || line.find("AGENTE")!= string::npos){
                continue;
            }
            else{
                istringstream iss(line);
                string name , otherVal;
                pair<int , int> valuePair;
                int aggro, control , mid; 
                iss >> name;
                iss >> aggro;
                iss >> control;
                iss >> mid;
                while(iss >> otherVal){
                    if(otherVal != "/" && otherVal != "-"){
                        valuePair.first = stringToInt(otherVal);
                        iss >> otherVal;
                        valuePair.second = stringToInt(otherVal);
                        valueGroup.push_back(valuePair);
                    }
                    else{
                        continue;
                    }
                }
                agentArr.push_back(Agent(name , aggro , control , mid, valueGroup));
            }
        }
    }
    input.close();
    return agentArr;
}