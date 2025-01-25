#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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

        if (user_input == 1)
        {
            signUp();
        }
        else if (user_input == 2)
        {
            logIn();
        }
    }

    // write the new user to the csv file
    ofstream file("users.csv", ios::app);
    file << userName << "," << password << "," << "," << "\n";
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
        readVecCSV();
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



void User::readVecCSV()
{
    ifstream inputFile("users.csv");
    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open CSV file for reading." << endl;
        return;
    }
    string line, token;
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        vector<string> row;
        while (getline(ss, token, ','))
        {
            row.push_back(token);
        }

        // Check if the row corresponds to the current user
        if (row.size() >= 4 && row[0] == userName)
        {
            // Parse searching history vector
            stringstream searchHistStream(row[2]);
            while (getline(searchHistStream, token, ';'))
            {
                searchingHistory_vec.push_back(stoi(token));
            }

            // Parse favorite recipe vector
            stringstream favStream(row[3]);
            while (getline(favStream, token, ';'))
            {
                favoriteRecipe_vec.push_back(stoi(token));
            }
        }
    }
    inputFile.close();
}

void User::writeVecCSV(vector<int> &vec)
{
    ifstream inputFile("users.csv");
    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open CSV file for reading." << endl;
        return;
    }
    vector<string> lines;
    string line;
    while (getline(inputFile, line))
    {
        lines.push_back(line);
    }
    inputFile.close();

    // Prepare to write updated data
    ofstream outputFile("users.csv");
    if (!outputFile.is_open())
    {
        cerr << "Error: Could not open CSV file for writing." << endl;
        return;
    }
    for (size_t i = 0; i < lines.size(); ++i)
    {
        stringstream ss(lines[i]);
        string token;
        vector<string> columns;

        // Split the line into columns
        while (getline(ss, token, ','))
        {
            columns.push_back(token);
        }

        // Ensure the line has at least 4 columns
        if (columns.size() < 4)
        {
            while (columns.size() < 4)
            {
                columns.push_back(""); // Fill missing columns with empty strings
            }
        }

        if (vec == searchingHistory_vec)
        {
            // Update the third column if the vector has a corresponding value
            if (i < vec.size())
            {
                columns[2] = to_string(vec[i]);
            }
        }
        else if (vec == favoriteRecipe_vec)
        {
            if (i < vec.size())
            {
                columns[3] = to_string(vec[i]);
            }
        }

        // Reassemble the line
        string updatedLine = columns[0];
        for (size_t j = 1; j < columns.size(); ++j)
        {
            updatedLine += "," + columns[j];
        }

        // Write the updated line to the output file
        outputFile << updatedLine << endl;
    }

    outputFile.close();
}

void User::printRecipe(const vector<int> &vec, const vector<Recipe *> &book)
{
    if (vec.empty())
    {
        cout << "\nStart searching your favorite recipes!" << endl;
        return;
    }
    for (size_t i = 0; i < vec.size(); ++i)
    {
        Recipe *recipe_ptr = book[vec[i]];
        recipe_ptr->viewRecipe();
    }
}