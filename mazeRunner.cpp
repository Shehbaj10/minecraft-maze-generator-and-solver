#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "mazebuilder.h"
#include "Maze.h"
#include "Agent.h"
#include "env.h"
#include "WorldCleaner.h"
#include <random>
#include "buildFile.h"
#include <vector>

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main,
    ST_GetMaze,
    ST_BuildMaze,
    ST_SolveMaze,
    ST_Creators,
    ST_Exit
};

int main(int argc, char** argv){

    #define Option_One 49  //ascii value of 1
    #define Option_Two 50  //ascii value of 2
    #define Option_Three 51  //ascii value of 3
    #define Option_Four 52  //ascii value of 4
    #define Option_Five 53  //ascii value of 5
    std::string strArgv;
    std::string enhanceArgv;
    if(argc == 2){
        strArgv = argv[1];
        
    }
    if(argc == 2){
        enhanceArgv = argv[2];
    }
    bool mode = false;

    if(strArgv == "-testmode"){
        mode = true;
    }
    else{
        mode = false;
    }
    int enhancementNum = -1;

    if(enhanceArgv == "-enhancement1"){
        enhancementNum = 1;
    }
    else if(enhanceArgv == "-enhancement2"){
        enhancementNum = 2;
    }
    else{
        enhancementNum = 0;
    }
    
    // bool mode = NORMAL_MODE;
    //read Mode
    printStartText();

    mcpp::MinecraftConnection mc; 
    mc.doCommand("time set day"); 

    Env env;
    Env_Builder env_Builder;
    Maze maze;
    Agent agent;
    bool built = false;
    bool placed = false;

    

    States curState = ST_Main;

    //State machine for menu 

    while(curState != ST_Exit)
    {
        if(curState == ST_Main)
        {
            while(curState == ST_Main)
            {
                printMainMenu();
                int Get_Menu_Num = getOptionInput();

                if(Get_Menu_Num == Option_One)
                {
                    curState = ST_GetMaze;
                }
                else if(Get_Menu_Num == Option_Two)
                { 
                    curState = ST_BuildMaze;
                }
                else if(Get_Menu_Num == Option_Three)
                {
                    curState = ST_SolveMaze;
                }
                else if(Get_Menu_Num == Option_Four)
                {
                    curState = ST_Creators;
                }
                else if(Get_Menu_Num == Option_Five)
                {
                    curState = ST_Exit;
                }
                else
                {
                    printMainInputError();
                }
            }
        }
        else if(curState == ST_GetMaze)
        {
            while(curState == ST_GetMaze)
            {
                printGenerateMazeMenu();
                int Get_Maze_Num = getOptionInput();
                
                if (Get_Maze_Num == Option_One)
                {
                    maze.readMazeTerminal(env,mc);
                    curState = ST_Main;
                }
                else if(Get_Maze_Num == Option_Two)
                {
                    if(enhancementNum != 1){
                        maze.makeRandomMaze(env,mc,mode);
                    }
                    else{
                        maze.makeRandomMaze(env,mc,mode);
                    }
                    curState = ST_Main;
                }
                else if(Get_Maze_Num == Option_Three)
                {
                    curState = ST_Main;
                }
                else 
                {
                    printMazeInputError();
                }   
            }
        }
        else if(curState == ST_BuildMaze)
        {
            if(env.getLength() != 0){
                mazeMaker(env,mc,env_Builder);
                built = true;
            }
            else{
                std::cout << "Maze not defined! Generate maze before Building." << std::endl;
            }
            
            curState = ST_Main;
        }
        else if(curState == ST_SolveMaze)
        {
            while(curState == ST_SolveMaze)
            {   
                printSolveMazeMenu();
                int Get_Solve_Num = getOptionInput();

                if (Get_Solve_Num == Option_One)
                {
                    if(env_Builder.getLength() != 0){
                    agent.playerPlacer(mc,env_Builder,mode);
                    placed = true;
                }
                else{
                    std::cout << "Generate and build a maze first." << std::endl;
                }
                }
                else if(Get_Solve_Num == Option_Two)
                {
                    if(placed){
                        if(enhancementNum != 2){
                        agent.mazeSolver(mc);
                        }
                        else{
                            agent.mazeSolver(mc);
                        }
                    }
                    else{
                        std::cout << "Initialize player using Solve manually." << std::endl;
                    }
                }
                else if(Get_Solve_Num == Option_Three)
                {
                    curState = ST_Main;
                } 
                else 
                {
                    printSolveInputError();
                }
            }
        }
        else if(curState == ST_Creators)
        {
            printTeamInfo();
            curState = ST_Main;
        }
    }

    if(env.getLength() != 0 && built){
        clearMaze(env_Builder.getX_Coord(), env_Builder.getY_Coord(), env_Builder.getZ_Coord(), env_Builder.getLength(), env_Builder.getWidth(), mc);
        unFlattenTerrain(env_Builder.getX_Coord(), env_Builder.getY_Coord() , env_Builder.getZ_Coord() , env_Builder.getLength(), env_Builder.getWidth(), mc, env_Builder.getTerrain(), env_Builder.getTerrainBlock(),env_Builder.getTopTerrain(), env_Builder.getTopTerrainBlock());
    }

    printExitMassage();

    return EXIT_SUCCESS;
}