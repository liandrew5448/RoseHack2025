#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

User::User()
{
    userName = "";
    password = "";
}

User::User(string &userName, string &password)
{
    this->userName = userName;
    this->password = password;
}

// Destructor Implementation
User::~User(){}

// Public Methods
bool User::userExist(const string &name, const string &password)
{
    ifstream file("users.csv");

    if (!file.is_open())
    {
        cerr << "Error: Could not open the file 'users.csv'." << endl;
        return false;
    }

    string line, existingUserName, existingPassword;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, existingUserName, ',');
        getline(ss, existingPassword, ',');

        if (existingUserName == name && existingPassword == password)
            return true;
    }

    return false;
}

User *User::signUp()
{
    cout << "What's your user name (please input letters/special characters/numbers without space): ";
    cin >> userName;
    cout << "What's your password (please input letters/special characters/numbers without space): ";
    cin >> password;

    // Check if the user already exists
    if (userExist(userName))
    {
        int user_input;
        cout << "This user name is already being used. Input 1 for sign up and 2 for log in: ";
        cin >> user_input;

        while (cin.fail() || (user_input != 1 && user_input != 2))
        {
            cout << "Your input is invalid. Please input again: ";
            cin >> user_input;
        }

        if (user_input == 1){ signUp(); }
        else if (user_input == 2) {logIn();}
    }

    //get height and weight
    cout << "What is your weight in pounds:\n";
    cin >> weight;
    while (cin.fail()){
        cout << "invalid input, please try agian: ";
        cin >> weight;
        if (weight > 400 || weight < 50){
            cout << "Is this your real weight? You really need to workout...";
        }
    }

    cout << "How tall are you in feet:\n";
    cin >> height;
    while (cin.fail()){
        cout << "invalid input, please try agian: ";
        cin >> height;
    }

    // get score
    cout << "What is your exercise goal level? Please select one of the following options:\n";
    cout << "1. Beginner\n";
    cout << "2. Intermediate\n";
    cout << "3. Expert\n";
    cout << "Enter your choice (1/2/3): \n" << endl;
    int levelChoice;
    cin >> levelChoice;
    while (cin.fail()){
        cout << "invalid input, please try agian: ";
        cin >> levelChoice;
        if (levelChoice == 1){
            score = 0;
        }else if(levelChoice == 2){
            score = 100;
        }else if(levelChoice == 3){
            score = 200;
        }
    }
    cout <<"Your starting score is: " << score << "!\n";
    cout << "Think of an ideal score as your goal! \n Enter: ";
    cin >> goal;

    // write the new user to the csv file
    ofstream file("users.csv", ios::app);
    file << userName << "," << password << "," 
         << score << "," << height << "," 
         << weight << "\n";
    file.close();

    cout << "Sign-up successful!" << endl;
    User *new_user = new User(userName, password);
    return new_user;
}

User *User::logIn()
{
    cout << "What's your user name (please input letters/special characters/numbers without space): ";
    cin >> userName;
    cout << "What's your password (please input letters/special characters/numbers without space): ";
    cin >> password;

    if (userExist(userName, password))
    {
        cout << endl
             << "\nLogin successful! Welcome back, " << userName << "." << endl;
        readCSV();
        User *new_user = new User(userName, password);
        return new_user;
    }
    else
    {
        int user_input;
        cout << "Invalid username or password, please try again. Input 1 for sign up and 2 for log in: ";
        cin >> user_input;

        while (cin.fail() || (user_input != 1 && user_input != 2))
        {
            cout << "Your input is invalid. Please input again: ";
            cin >> user_input;
        }
        if (user_input == 1)
        {
            signUp();
        }
        else if (user_input == 2)
        {
            logIn();
        }
    }
    cout << "Error: Unable to log in." << endl;
    return nullptr;
}


void User::readCSV()
{
    ifstream inputFile("users.csv");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open CSV file for reading." << endl;
        return;
    }

    string line, token;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        vector<string> row;

        // Split the line into tokens based on the comma delimiter
        while (getline(ss, token, ',')) {
            row.push_back(token);
        }

        // Check if the row corresponds to the current user
        if (row.size() >= 6 && row[0] == userName) {
            try {
                // Assign score, height, and weight
                score = stoi(row[2]);
                height = stof(row[3]);
                weight = stof(row[4]);
                goal = stof(row[5]);
            } catch (const invalid_argument& e) {
                cerr << "Error: Invalid data format for user: " << userName << endl;
                continue;
            } catch (const out_of_range& e) {
                cerr << "Error: Data out of range for user: " << userName << endl;
                continue;
            }
        }
    }

    inputFile.close();
}

void User::updateCSV() {
    string fileName = "users.csv";
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open CSV file for reading." << endl;
        return;
    }

    vector<vector<string>> data;  // Store the entire CSV content
    string line, token;

    // Read the CSV file
    while (getline(inputFile, line)) {
        stringstream ss(line);
        vector<string> row;

        // Parse each row into tokens
        while (getline(ss, token, ',')) {
            row.push_back(token);
        }

        // Update the user's information if the username matches
        if (row.size() >= 5 && row[0] == userName) {
            row[2] = to_string(score);  // Update score
            row[3] = to_string(height); // Update height
            row[4] = to_string(weight); // Update weight
            row[5] = to_string(goal);
        }

        data.push_back(row);  // Add the row (modified or unmodified) to the data vector
    }

    inputFile.close();  // Close the input file

    // Write the updated data back to the CSV file
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open CSV file for writing." << endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outputFile << row[i];
            if (i < row.size() - 1) outputFile << ',';  // Add comma except for the last column
        }
        outputFile << '\n';
    }

    outputFile.close();  // Close the output file
    cout << "CSV file updated successfully." << endl;
}
