#pragma once


#include "User.h"
#include "Output.h"

#include <string>
#include <iostream>
#include <sstream>

// No Destructor Needed

using namespace std;

class Interface
{
private:

    User currentUser;
    bool isRunning;


    vector<int> fav_recipe_vec;
    vector<int> search_hist_vec;
    void handleAuthentication();

public:
    void start();
    void displayMenu();
    void handleChoice(int choice);
    Interface();
};