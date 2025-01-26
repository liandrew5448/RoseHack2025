#include "Output.h"

#include <unistd.h>
#include <iostream>

void Output::returnToMenu() {
    cout << endl << "Press any key to return to the main menu..." << endl;
    system("read");
}

void Output::clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void Output::waitingScreen() {
    usleep(3000000);
}