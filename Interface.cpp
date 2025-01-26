#include "Interface.h"

using namespace std;

Interface::Interface()
{
    isRunning = true; // Menu starts in a running state
}

void Interface::start()
{
    handleAuthentication();

    cout << "\n------------Welcome to I will be BUFFEDDDDD------------" << endl;

    Output::waitingScreen();
    Output::clearScreen();

    while (isRunning)
    {
        displayMenu();

        cout << endl;
        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        handleChoice(choice);
    }
}

void Interface::displayMenu()
{
    Output::clearScreen();
    cout << "\nChoose what action you would like to take: "
         << "\n\t1. Create new weekly workout plan."
         << "\n\t2. Check in for today's work out."
         << "\n\t3. View my current weekly workout plan."
         << "\n\t4. Check my current score."
         << "\n\t5. Workout dictionary."
         << "\n\t6. Exit.\n";
}

void Interface::handleChoice(int choice)
{
    switch (choice)
    {
    case 1:
        Output::clearScreen();
        // Create new weekly workout plan."
        break;
    case 2:
        Output::clearScreen();
        // check in
        break;
    case 3:
        Output::clearScreen();
        // view current plan

        break;
    case 4:
        Output::clearScreen();
        // check score
        cout << "\nYoure current score is: " << currentUser.getScore() << endl;
        break;
    case 5:
        Output::clearScreen();
        // Workout dictionary.
        
        break;
    case 6:
        Output::clearScreen();
        cout << "\nExiting Program" << endl;
        isRunning = false;
        break;
    default:
        cout << "invalid choice (switch case branch)";
        break;
    }
}

void Interface::handleAuthentication()
{
    User *userPtr = nullptr;

    cout << "Would you like to sign up for a new account or log in? (1 for sign up, 2 for log in): ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        userPtr = currentUser.signUp();
    }
    else if (choice == 2)
    {
        userPtr = currentUser.logIn();
    }

    if (userPtr != nullptr)
    {
        // Use the user object
        currentUser = *userPtr; // Copy the user object to currentUser
        delete userPtr;         // Clean up dynamically allocated memory
    }
}
