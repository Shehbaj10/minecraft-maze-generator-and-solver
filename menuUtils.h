#ifndef MENU_UTILS_H
#define MENU_UTILS_H

#include <iostream>

void printStartText(void){

    std::cout << std::endl;
    std::cout << "Welcome to MineCraft MazeRunner!" << std::endl;
    std::cout << "--------------------------------" << std::endl;

}

void printMainMenu(void){

    std::cout << std::endl;
    std::cout << "------------- MAIN MENU -------------" << std::endl;
    std::cout << "1) Generate Maze" << std::endl;
    std::cout << "2) Build Maze in MineCraft" << std::endl;
    std::cout << "3) Solve Maze" << std::endl;
    std::cout << "4) Show Team Information" << std::endl;
    std::cout << "5) Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;

}

void printGenerateMazeMenu(void){

    std::cout << std::endl;
    std::cout << "------------- GENERATE MAZE -------------" << std::endl;
    std::cout << "1) Read Maze from terminal" << std::endl;
    std::cout << "2) Generate Random Maze" << std::endl;
    std::cout << "3) Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;

}

void printSolveMazeMenu(void){

    std::cout << std::endl;
    std::cout << "------------- SOLVE MAZE -------------" << std::endl;
    std::cout << "1) Solve Manually" << std::endl;
    std::cout << "2) Show Escape Route" << std::endl;
    std::cout << "3) Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;

}


void printTeamInfo(void){

    std::cout << std::endl;
    std::cout << "Team members:" << std::endl;
    std::cout << "\t [1] Shehbaj Singh Khakh (s3980305@student.rmit.edu.au)" << std::endl;
    std::cout << "\t [2] Dev Bakshi (s3954804@student.rmit.edu.au)" << std::endl;
    std::cout << "\t [3] Tanisha (s3975655@student.rmit.edu.au)" << std::endl;
    std::cout << "\t [4] Ritika (s3966976@student.rmit.edu.au)" << std::endl;
    std::cout << std::endl;

}

void printExitMassage(void){

    std::cout << std::endl;
    std::cout << "The End!" << std::endl;
    std::cout << std::endl;

}

void printMainInputError(void){

    std::cout << "Input Error: Enter a number between 1 and 5 ...." << std::endl;
}

void printMazeInputError(void){

    std::cout << "Input Error: Enter a number between 1 and 3 ...." << std::endl;
}

void printSolveInputError(void){

    std::cout << "Input Error: Enter a number between 1 and 3 ...." << std::endl;
}

int getOptionInput(void){

    
std::string stringInput = " ";
char charInput = ' ';
int numInput = 0;
std::cin >> stringInput;
if(stringInput.length() != 1){
    numInput = 0;
}
else{
    charInput = stringInput[0];
    numInput = int(charInput);
}
return numInput;
}

#endif //MENU_UTILS_H