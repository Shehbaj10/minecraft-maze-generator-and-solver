#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <vector>
#include <mcpp/mcpp.h>
#include "env.h"

/*
* Maze.h file 
* Defining Maze class  
*/

class Maze {

public:
    //Maze constructor and deconstructor 
    Maze();
    ~Maze();

    //Function to input Coordinates and Minecraft Connection
    void CoordinateInput(int& , int& , int& , mcpp::MinecraftConnection& );
    
    //Function to get numeric input 
    void getNumericInput(int& , int& );
    
    //Function to check if a coordinate is valid
    bool isValid(int , int , int , int );
    
    //Depth-First Search Algorithm for maze generation
    void dfs(int , int , char** , bool** ,int ,int ,char  );
    
    // Function to get the structure of the maze
    void getMazeStructure(char** , int , int );
    
    // Function to print the maze structure    
    void printMazeStructure(char** , int , int );
    
    // Function to read the maze from the terminal
    void readMazeTerminal(Env& ,mcpp::MinecraftConnection& );
    
    // Function to create a new maze
    void newMaze(int, int, char**&);
    
    // Function for the first step in maze creation
    void FirstStep(int, int, char**&, int&, int&, bool);
    
    // Function to check the path in the maze
    void PathChecker(int, int, char**&, int**&, std::vector<std::vector<int>>&, int& );
    
    // Function to create a path in the maze
    void PathMaker(int, int, char**&, int**&, std::vector<std::vector<int>>&, bool );
    
    // Function to create a random maze
    void makeRandomMaze(Env&, mcpp::MinecraftConnection&, bool );

private:
    int build_x;
    int build_y;
    int build_z;
    int x;
    int z;
    bool** visited;
    char toFind;

    int Maze_Length;
    int Maze_Width;
    char** mazeStructure;
    int startx;
    int startz;
    bool mode;
    int** valid;
    std::vector<std::vector<int>> lastCoords;
    int number;
    Env env;
    mcpp::MinecraftConnection mc;

};

#endif //ASSIGN_MAZE_H
