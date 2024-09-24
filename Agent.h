#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H

#include <iostream>
#include <mcpp/mcpp.h>
#include "buildFile.h"
#include <chrono>


// #define MOVE_XPLUS mcpp::Coordinate(1,0,0)
// #define MOVE_XMINUS mcpp::Coordinate(-1,0,0)
// #define MOVE_ZPLUS mcpp::Coordinate(0,0,1)
// #define MOVE_ZMINUS mcpp::Coordinate(0,0,-1)

// enum solveAlgorithm{
//         RIGHT_HAND_FOLLOW,
//         BREATH_FIRST_SEARCH,
// };

// enum AgentOrientation{
//     X_PLUS,
//     Z_PLUS,
//     X_MINUS,
//     Z_MINUS
// };

class Agent
{

public:
    Agent();
    ~Agent();
    // void delayCarpet(int );
    void playerPlacer(mcpp::MinecraftConnection& , Env_Builder& , bool );
    bool rightWallChecker(mcpp::Coordinate , mcpp::MinecraftConnection& , mcpp::Coordinate , mcpp::Coordinate );
    bool frontWallChecker(mcpp::Coordinate , mcpp::MinecraftConnection& , mcpp::Coordinate , mcpp::Coordinate );
    void turnRight(mcpp::Coordinate& , mcpp::Coordinate& );
    void turnLeft(mcpp::Coordinate& , mcpp::Coordinate& );
    void finalGoalChecker(mcpp::Coordinate , int& , mcpp::MinecraftConnection& );
    bool endPoint(mcpp::Coordinate , mcpp::Coordinate , mcpp::Coordinate , mcpp::MinecraftConnection& );
    void mazeSolver(mcpp::MinecraftConnection& );

private:
    /* data */
    Env_Builder env_Builder;
    bool mode;
    mcpp::Coordinate rightHandBlock;
    mcpp::Coordinate temp;
    mcpp::Coordinate temp2;
    mcpp::Coordinate frontBlock;
    int checker;
    mcpp::Coordinate currWall;
    mcpp::MinecraftConnection mc;

};



#endif //ASSIGN3_AGENT_H