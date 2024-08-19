#include <iostream>
#include <fstream>
#include <string>
#include <string_view> 
#include "createComp.cpp"
#include "parseDoc.cpp"
using namespace std;

// The idea is to use questions to get a playstyle as well as some key agents needed, then we can exclude and evaluate which score is higher
// Missing : implement the main restrictions inside the createComp function


// Auxiliary Function definition
int detectPlaystyle(int playstyle = 0);
void convert(string& word);
vector<bool> specificParam(string fileName);


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
            scores.minControlScore = 10;
            scores.minAggroScore = 15;
            break;
        case 13:
            scores.minMidScore = 10;
        case 10:
            scores.minAggroScore = 15;
            break;
        case 21:
            scores.minAggroScore = 10;
            scores.minControlScore = 15;
            break;
        case 23:
            scores.minMidScore = 10;
        case 20:
            scores.minControlScore = 15;
            break;
        case 31:
            scores.minAggroScore = 10;
            scores.minMidScore = 15;
            break;
        case 32:
            scores.minControlScore = 10;
        case 30:
            scores.minMidScore = 15;
            break;
        default:
            cout << "There appears to be an error when calculating your playstyle please try again.\n";
            return 0;
    }
    dataVec = parseFile("agents.txt");
    answersVec = specificParam("questions.txt");
    string temp = createComp(dataVec , scores , answersVec);
    cout << temp << endl;
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

vector<bool> specificParam(string fileName){
    vector<bool> answers;
    ifstream input(fileName);
    string line , number , answer;
    while (getline(input , line)){
        string c = line.substr(0 , 1);
        if (c == "A" || c == " "){
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