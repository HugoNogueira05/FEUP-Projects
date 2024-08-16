#include <iostream>
#include <fstream>
#include <string>
#include "parseDoc.cpp"
using namespace std;

// The idea is to use questions to get a playstyle as well as some key agents needed, then we can exclude and evaluate which score is higher


// Auxiliary Function definition
int detectPlaystyle(int playstyle = 0);
void convert(string& word);


int main(){
    vector<Agent> dataVec ;
    int playstyleVal = 0 , minAggroScore = 0 , minControlScore = 0 , minMidScore = 0;
    playstyleVal = detectPlaystyle();
    //Define the base values to finally create the comp
    //This could be implemented in an auxiliary function if needed
    switch (playstyleVal){
        case 12:
            minControlScore = 10;
            minAggroScore = 15;
            break;
        case 13:
            minMidScore = 10;
        case 10:
            minAggroScore = 15;
            break;
        case 21:
            minAggroScore = 10;
            minControlScore = 15;
            break;
        case 23:
            minMidScore = 10;
        case 20:
            minControlScore = 15;
            break;
        case 31:
            minAggroScore = 10;
            minMidScore = 15;
            break;
        case 32:
            minControlScore = 10;
        case 30:
            minMidScore = 15;
            break;
        default:
            cout << "There appears to be an error when calculating your playstyle please try again.\n";
            return 0;
    }
    cout << minAggroScore << " " << minControlScore << " " << minMidScore << endl;
    dataVec = parseFile("agents.txt");
    for (Agent agente : dataVec){
        cout << agente.getName() << endl;
    }

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
 * @param playstyle This variable is used kinda as a flag, it saves the user from having the answer all the questions all over again if
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

