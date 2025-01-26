#pragma once

#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class workout {
public:
    // Constructor
    workout();

    // Reset function
    void reset();

    // Find workout function (searches for workouts in the CSV based on primaryMuscles and level)
    void findWorkout(const string& bodyPart, const string& level);

    // Create workout function (generate workout based on user score)
    void createWorkout();

private:
    // Example body parts
    vector<string> upperBody;
    vector<string> coreAndBack;
    vector<string> lowerBody;

    // Helper function to search through CSV file
    bool search_csv(const string& file_name, const string& search_primaryMuscles, const string& search_level);

    // Store user workout details, assuming the class User has this functionality.
    User entity;
    
    // Helper function for random selection
    string getRandomExercise(const vector<string>& bodyPartList, const string& level, const string& file_name);
};
