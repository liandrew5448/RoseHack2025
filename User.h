#pragma once

#include <string>
#include <vector>

using namespace std;

// Already Added

class User{
public:
    User* logIn();
    User* signUp();
    
    void readVecCSV();
    void writeVecCSV(vector<int>&);

    string getUserName() {return userName;}
    string getUserPassword() {return password;}
    bool userExist(const string&, const string& password = "");

    User();
    User(string&, string&);
    ~User();

private:
    string userName = "";
    string password = "";
    double height, weight;
    int score;
};