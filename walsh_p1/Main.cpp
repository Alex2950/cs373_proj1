#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <stdlib.h>
#include<string>
using namespace std;


int main(int argc, char *argv[]){
    if(argc != 3){
        cout<<"NOT VAILD ARGUMENTS"<<endl;
        return 1;
    }
    string inputName = argv[1]; //file name
    string inputSymbols = argv[2]; 
    vector<vector<string> > matrix; //holds all transitions
    unordered_set<string> acceptedStates; 
    queue<string> itrStates;
    ifstream inFS;
    inFS.open(inputName);
    if(!inFS.is_open())cerr<<"error: "<<inputName<<" could not be found"<<endl;
    while(!inFS.eof()){
        string line = "";
        getline(inFS, line);
        stringstream s(line);
        string word;
        s>>word;
        if(word == "state"){
            s>>word;
            string q = word;
            if(s>>word){
                if(word == "accept")acceptedStates.insert(q);
                if(word == "start"){
                    itrStates.push(q);
                }
            }
            if(s>>word){
                if(word == "accept")acceptedStates.insert(q);
                if(word == "start"){
                    itrStates.push(q);
                }
            }

        }
        else if(word == "transition"){
            vector<string> row;
            for(int i = 0; i<3;i++){
                s>>word;
                row.push_back(word);
            }
            matrix.push_back(row);

        }
        else{
             cerr<<"Unrecognized Term or file cannot be found"<<endl;
             return 1;
        }
    }
    inFS.close();
    //-------------------------READING IN THE STRING--------------------------
    for(int i = 0;i<inputSymbols.length();i++){
        string stringSymbol = "";
        stringSymbol+=inputSymbols[i];
        int qSize = itrStates.size();
        for(int k = 0;k<qSize;k++){
             string currState = itrStates.front();
            for(int j = 0;j<matrix.size();j++){
                if(matrix.at(j).at(0) == currState && matrix.at(j).at(1) == (stringSymbol)){
                    itrStates.push(matrix.at(j).at(2));
                }
            }
            itrStates.pop();
        }
        
    }
    //-------------------Compare to accepted states set-----------------------
    vector<string> failedList;
    vector<string> acceptList;
    while(!itrStates.empty()){
        string currQ = itrStates.front();
        if (acceptedStates.find(currQ) != acceptedStates.end())acceptList.push_back(currQ);     
        else failedList.push_back(currQ);
        itrStates.pop();
    }
    if(acceptList.empty()){
        cout<<"reject";
        for(int i = 0;i<failedList.size();i++){
            cout<<" "<<failedList.at(i);
        }
        cout<<endl;
    }
    else{
        cout<<"accept";
        for(int i = 0;i<acceptList.size();i++){
            cout<<" "<<acceptList.at(i);
        }
        cout<<endl;
    }
    return 0;
}
//REJECT also if no path and string isn't done
//Done building the matrix, acceptedStates, and first iteration of itrStates

/*
current issue is queue seems to be empty
*/