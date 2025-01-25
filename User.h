#pragma once

#include <string>
#include <vector>

using namespace std;

// Already Added

class User{
public:
    User* logIn();
    User* signUp();
    
    void readCSV();
    void updateCSV();

    string getUserName() {return userName;}
    string getUserPassword() {return password;}
    int getScore() {return score;}
    double getHeight() {return height;}
    double getWeight() {return weight;}
    int getGoal(){return goal;}
    bool userExist(const string&, const string& password = "");

    User();
    User(string&, string&);
    ~User();

private:
    string userName = "";
    string password = "";
    double height, weight;
    int score, goal;
};