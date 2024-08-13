#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "agents.h"
using namespace std;

int main(){
    Agent agentArr[];
    ifstream input("/Data/agentes.txt");
    if (!input){
        cout << 'File does not exist or is in the wrong directory, please make sure that the file "agents.txt" is inside the directory called "Data"\n';~
        return 0;
    }
    else{
        string line;
        while(getline(input, line)){
            if (line == "" || line.find("Agente")!= npos){
                continue;
            }
            else{
                istringstream iss(line);
                string name;
                int aggro, control , mid;
                cin >> name;
                cin >> aggro;
                cin >> control;
                cin >> mid;
                agentArr.pushback(Agent(name , aggro , mid , control));
            }
        }
    }
    return 0;
}
