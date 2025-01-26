#include "User.h"
#include "workout.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;


// Constructor
workout::workout() {
    upperBody = {"biceps", "chest", "forearms", "shoulders", "triceps"};
    coreAndBack = {"abdominals", "lower back", "traps", "lats", "middle back"};
    lowerBody = {"calves", "glutes", "hamstrings", "quadriceps"};
    srand(time(0));  // Seed the random number generator
}

// Reset function
void workout::reset() {
    upperBody = {"biceps", "chest", "forearms", "shoulders", "triceps"};
    coreAndBack = {"abdominals", "lower back", "traps", "lats", "middle back"};
    lowerBody = {"calves", "glutes", "hamstrings", "quadriceps"};
}

// Helper function for random exercise selection
string workout::getRandomExercise(const vector<string>& bodyPartList, const string& level, const string& file_name) {
    // Randomly select a body part from the list
    int randomIndex = rand() % bodyPartList.size();
    string bodyPart = bodyPartList[randomIndex];
    
    // Call findWorkout and search for exercises matching the body part and level
    findWorkout(bodyPart, level);  // You may want to capture the result and do something with it
    
    return bodyPart;
}

// Find workout function (searches for workouts in the CSV based on primaryMuscles and level)
void workout::findWorkout(const string& bodyPart, const string& level) {
    string file_name = "exercises.csv";  // CSV file name
    bool found = search_csv(file_name, bodyPart, level);
    
    if (!found) {
        cout << "No workout found for body part: " << bodyPart << " and level: " << level << endl;
    }
}

// Create workout function (generate workout based on user score)
void workout::createWorkout() {
    int score = entity.getScore();  // Assume getScore() gets the score
    
    // Extract the hundreds digit to determine how many exercises per region
    int hundredsDigit = (score / 100) + 1;  // Integer division by 100 to get the hundreds digit
    
    // For a score of 230, hundredsDigit will be 3 (3 exercises per region)
    cout << "Selecting " << hundredsDigit << " exercises for each body region based on score of " << score << endl;
    
    // Randomly select exercises for each body part category
    for (int i = 0; i < hundredsDigit; ++i) {
        // Select an exercise for upper body
        getRandomExercise(upperBody, "intermediate", "exercises.csv");  // "intermediate" is an example level
        // Select an exercise for core and back
        getRandomExercise(coreAndBack, "intermediate", "exercises.csv");
        // Select an exercise for lower body
        getRandomExercise(lowerBody, "intermediate", "exercises.csv");
    }
}

// Helper function to search through CSV file
bool workout::search_csv(const string& search_primaryMuscles, const string& search_level) {
    ifstream file("users.csv");
    string line;

    // Check if the file is open
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    // Read the header line to find the index of each column
    getline(file, line);
    stringstream header_ss(line);
    string header;
    vector<string> headers;

    // Store headers in a vector
    while (getline(header_ss, header, ',')) {
        headers.push_back(header);
    }

    // Get the indices for primaryMuscles, level, name, equipment, instructions
    int primaryMusclesIdx = -1, levelIdx = -1, nameIdx = -1, equipmentIdx = -1, instructionsIdx = -1;

    // Find the indices of the relevant columns
    for (int i = 0; i < headers.size(); ++i) {
        if (headers[i] == "primaryMuscles") {
            primaryMusclesIdx = i;
        } else if (headers[i] == "level") {
            levelIdx = i;
        } else if (headers[i] == "name") {
            nameIdx = i;
        } else if (headers[i] == "equipment") {
            equipmentIdx = i;
        } else if (headers[i] == "instructions") {
            instructionsIdx = i;
        }
    }

    if (primaryMusclesIdx == -1 || levelIdx == -1 || nameIdx == -1 || equipmentIdx == -1 || instructionsIdx == -1) {
        cerr << "One or more required columns not found!" << endl;
        return false;
    }

    // Read the data lines
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> row_data;

        // Split the line into fields
        while (getline(ss, field, ',')) {
            row_data.push_back(field);
        }

        // Check if the search term matches primaryMuscles and level
        if (row_data[primaryMusclesIdx] == search_primaryMuscles && row_data[levelIdx] == search_level) {
            // Print the name, equipment, and instructions
            cout << "Name: " << row_data[nameIdx] << endl;
            cout << "Equipment: " << row_data[equipmentIdx] << endl;
            cout << "Instructions: " << row_data[instructionsIdx] << endl;
            return true; // Terminate after first match (optional: could loop to find all matches)
        }
    }

    cout << "No matching data found." << endl;
    return false;
}
