#ifndef WORKOUT_H
#define WORKOUT_H

#include <vector>
#include <string>
#include "User.h"  // Assuming you have a User class to access user scores

using namespace std;

// Exercise struct to represent an individual exercise
struct Exercise {
    int index;
    string name;
    string primaryMuscles;
    vector<string> instructions;
    string level; // Difficulty level (e.g., "beginner", "intermediate", "expert")
};

class workout {
public:
    // Constructor
    workout();

    // Method to reset the body part categories (used if you need to reset the state)
    void reset();

    // Method to create a workout based on the user score
    void createWorkout();

    // Helper function to select a random exercise for a given body part and level
    string getRandomExercise(const vector<string>& bodyPartList, const string& level, const string& file_name);

    // Method to search the CSV file for exercises matching the body part and level
    bool search_csv(const string& file_name, const string& search_primaryMuscles, const string& search_level);

    // Method to find a workout by body part and level
    void findWorkout(const string& bodyPart, const string& level, const string& file_name);

private:
    vector<string> upperBody;   // List of upper body muscles (e.g., biceps, chest, shoulders)
    vector<string> coreAndBack; // List of core and back muscles (e.g., abdominals, lower back)
    vector<string> lowerBody;   // List of lower body muscles (e.g., calves, hamstrings, quadriceps)

    vector<Exercise> exercises; // List of exercises loaded from the CSV file
    User entity;
};

#endif // WORKOUT_H
