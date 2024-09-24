#include "Agent.h"
#include "DelayCarpet.h"

#include <random>
#include <vector>

Agent::Agent()
{
}

Agent::~Agent()
{
}



void Agent::playerPlacer(mcpp::MinecraftConnection& mc, Env_Builder& env_Builder, bool mode){
    int build_x = env_Builder.getX_Coord();
    int build_y = env_Builder.getY_Coord();
    int build_z = env_Builder.getZ_Coord();
    int Maze_Length = env_Builder.getLength();
    int Maze_Width = env_Builder.getWidth();
    int maxZ = 0;
    int maxX = 0;

    char **mazeStructure;
            mazeStructure = new char*[env_Builder.getLength()];
            for(int i=0; i < env_Builder.getLength(); i++){
                mazeStructure[i] = new char[env_Builder.getWidth()];
            }

    mazeStructure = env_Builder.getEnvStructure();
    std::vector<std::vector<int>> lastCoords;
    std::vector<int> v2;
    if(!mode){
    for (int x = 0; x < Maze_Length; x++) {
        for (int z = 0; z < Maze_Width; z++) {
            if(mazeStructure[x][z] == '.' && x != 0 && z != 0 && x != Maze_Length - 1 && z != Maze_Width - 1){
                v2.push_back(x);
                v2.push_back(z);
                lastCoords.push_back(v2);
            }
        }
    }
    
    
    int min = 0;
    int max = int(lastCoords.size());
    int value = -1;
    
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    value = uniform_dist(engine);
    
    int num = lastCoords[value][0];
    int num2 = lastCoords[value][1];

    mc.setPlayerPosition(mcpp::Coordinate(build_x + num, build_y, build_z + num2));
    }
    else{
        for (int x = 0; x < Maze_Length; x++) {
        for (int z = 0; z < Maze_Width; z++) {
            if(mazeStructure[x][z] == '.' && x != 0 && z != 0 && x != Maze_Length - 1 && z != Maze_Width - 1){
                if(build_x - x > maxX && build_z - z > maxZ){
                    maxX = x;
                    maxZ = z;
                }
                
            }
        }
    }
    mc.setPlayerPosition(mcpp::Coordinate(build_x +maxX, build_y,build_z + maxZ));

    }

    lastCoords.clear();
    v2.clear();

}



/////////////////////////////////////////

bool Agent::rightWallChecker(mcpp::Coordinate rightHandBlock, mcpp::MinecraftConnection& mc, mcpp::Coordinate temp, mcpp::Coordinate temp2){
bool isRightWall = true;
mcpp::Coordinate MOVE_XPLUS(1,0,0);
mcpp::Coordinate MOVE_XMINUS(-1,0,0);
mcpp::Coordinate MOVE_ZPLUS(0,0,1);
mcpp::Coordinate MOVE_ZMINUS(0,0,-1);

    if (temp == MOVE_XPLUS && temp2 == MOVE_ZMINUS){
        rightHandBlock = rightHandBlock + MOVE_ZPLUS;
        mcpp::BlockType blockType = mc.getBlock(rightHandBlock);
        if(blockType == mcpp::Blocks::AIR || blockType == mcpp::Blocks::LIME_CARPET){
            isRightWall = false;
        }
    }
    else if(temp == MOVE_ZMINUS && temp2 == MOVE_XMINUS){
        rightHandBlock = rightHandBlock + MOVE_XPLUS;
        mcpp::BlockType blockType = mc.getBlock(rightHandBlock);
        if(blockType == mcpp::Blocks::AIR || blockType == mcpp::Blocks::LIME_CARPET){
            isRightWall = false;
        }
    }
    else if(temp == MOVE_XMINUS && temp2 == MOVE_ZPLUS){
        rightHandBlock = rightHandBlock + MOVE_ZMINUS;
        mcpp::BlockType blockType = mc.getBlock(rightHandBlock);
        if(blockType == mcpp::Blocks::AIR || blockType == mcpp::Blocks::LIME_CARPET){
            isRightWall = false;
        }
    }
    else if(temp == MOVE_ZPLUS && temp2 == MOVE_XPLUS){
        rightHandBlock = rightHandBlock + MOVE_XMINUS;
        mcpp::BlockType blockType = mc.getBlock(rightHandBlock);
        if(blockType == mcpp::Blocks::AIR || blockType == mcpp::Blocks::LIME_CARPET){
            isRightWall = false;
        }
    }
return isRightWall;
}

bool Agent::frontWallChecker(mcpp::Coordinate frontBlock, mcpp::MinecraftConnection& mc, mcpp::Coordinate temp, mcpp::Coordinate temp2){
bool isfrontWall = true;
mcpp::Coordinate MOVE_XPLUS(1,0,0);
mcpp::Coordinate MOVE_XMINUS(-1,0,0);
mcpp::Coordinate MOVE_ZPLUS(0,0,1);
mcpp::Coordinate MOVE_ZMINUS(0,0,-1);

    if (temp == MOVE_XPLUS && temp2 == MOVE_ZMINUS){
        frontBlock = frontBlock + MOVE_XPLUS;
        mcpp::BlockType blockType = mc.getBlock(frontBlock);
        if(blockType == mcpp::Blocks::AIR || blockType == mcpp::Blocks::LIME_CARPET){
            isfrontWall = false;
        }
    }
    else if(temp == MOVE_ZMINUS && temp2 == MOVE_XMINUS){
        frontBlock = frontBlock + MOVE_ZMINUS;
        mcpp::BlockType blockType = mc.getBlock(frontBlock);
        if(blockType == mcpp::Blocks::AIR || blockType == mcpp::Blocks::LIME_CARPET){
            isfrontWall = false;
        }
    }
    else if(temp == MOVE_XMINUS && temp2 == MOVE_ZPLUS){
        frontBlock = frontBlock + MOVE_XMINUS;
        mcpp::BlockType blockType = mc.getBlock(frontBlock);
        if(blockType == mcpp::Blocks::AIR || blockType == mcpp::Blocks::LIME_CARPET){
            isfrontWall = false;
        }
    }
    else if(temp == MOVE_ZPLUS && temp2 == MOVE_XPLUS){
        frontBlock = frontBlock + MOVE_ZPLUS;
        mcpp::BlockType blockType = mc.getBlock(frontBlock);
        if(blockType == mcpp::Blocks::AIR || blockType == mcpp::Blocks::LIME_CARPET){
            isfrontWall = false;
        }
    }

return isfrontWall;
}

void Agent::turnRight(mcpp::Coordinate& temp, mcpp::Coordinate& temp2){
mcpp::Coordinate MOVE_XPLUS(1,0,0);
mcpp::Coordinate MOVE_XMINUS(-1,0,0);
mcpp::Coordinate MOVE_ZPLUS(0,0,1);
mcpp::Coordinate MOVE_ZMINUS(0,0,-1);

    if (temp == MOVE_XPLUS && temp2 == MOVE_ZMINUS){
        temp = MOVE_ZPLUS;
        temp2 = MOVE_XPLUS;
    }
    else if(temp == MOVE_ZMINUS && temp2 == MOVE_XMINUS){
        temp = MOVE_XPLUS;
        temp2 = MOVE_ZMINUS;
    }
    else if(temp == MOVE_XMINUS && temp2 == MOVE_ZPLUS){
        temp = MOVE_ZMINUS;
        temp2 = MOVE_XMINUS;
    }
    else if(temp == MOVE_ZPLUS && temp2 == MOVE_XPLUS){
        temp = MOVE_XMINUS;
        temp2 = MOVE_ZPLUS;
    }
}

void Agent::turnLeft(mcpp::Coordinate& temp, mcpp::Coordinate& temp2){
mcpp::Coordinate MOVE_XPLUS(1,0,0);
mcpp::Coordinate MOVE_XMINUS(-1,0,0);
mcpp::Coordinate MOVE_ZPLUS(0,0,1);
mcpp::Coordinate MOVE_ZMINUS(0,0,-1);

    if (temp == MOVE_XPLUS && temp2 == MOVE_ZMINUS){
        temp = MOVE_ZMINUS;
        temp2 = MOVE_XMINUS;
    }
    else if(temp == MOVE_ZMINUS && temp2 == MOVE_XMINUS){
        temp = MOVE_XMINUS;
        temp2 = MOVE_ZPLUS;
    }
    else if(temp == MOVE_XMINUS && temp2 == MOVE_ZPLUS){
        temp = MOVE_ZPLUS;
        temp2 = MOVE_XPLUS;
    }
    else if(temp == MOVE_ZPLUS && temp2 == MOVE_XPLUS){
        temp = MOVE_XPLUS;
        temp2 = MOVE_ZMINUS;
    }
    
}

void Agent::finalGoalChecker(mcpp::Coordinate currWall, int& checker, mcpp::MinecraftConnection& mc){
mcpp::BlockType blockType = mc.getBlock(currWall); 
    if(blockType == mcpp::Blocks::ACACIA_WOOD_PLANK){}
    else{
        checker++;
    }
}

bool Agent::endPoint(mcpp::Coordinate currWall, mcpp::Coordinate temp, mcpp::Coordinate temp2, mcpp::MinecraftConnection& mc){
mcpp::Coordinate MOVE_XPLUS(1,0,0);
mcpp::Coordinate MOVE_XMINUS(-1,0,0);
mcpp::Coordinate MOVE_ZPLUS(0,0,1);
mcpp::Coordinate MOVE_ZMINUS(0,0,-1);
    int checker = 0;
    bool valid = false;
    if (temp == MOVE_XPLUS && temp2 == MOVE_ZMINUS){
        currWall = currWall + temp;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + temp;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + temp2;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + MOVE_XMINUS;
        this->finalGoalChecker(currWall,checker, mc);

    }
    else if(temp == MOVE_ZMINUS && temp2 == MOVE_XMINUS){
        currWall = currWall + temp;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + temp;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + temp2;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + MOVE_ZPLUS;
        this->finalGoalChecker(currWall,checker, mc);
    }
    else if(temp == MOVE_XMINUS && temp2 == MOVE_ZPLUS){
        currWall = currWall + temp;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + temp;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + temp2;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + MOVE_XPLUS;
        this->finalGoalChecker(currWall,checker, mc);
    }
    else if(temp == MOVE_ZPLUS && temp2 == MOVE_XPLUS){
        currWall = currWall + temp;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + temp;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + temp2;
        this->finalGoalChecker(currWall,checker, mc);

        currWall = currWall + MOVE_ZPLUS;
        this->finalGoalChecker(currWall,checker, mc);
    }
    if(checker == 4){
        valid = true;
    }
    return valid;
}

void Agent::mazeSolver(mcpp::MinecraftConnection& mc){
mcpp::Coordinate MOVE_XPLUS(1,0,0);
mcpp::Coordinate MOVE_XMINUS(-1,0,0);
mcpp::Coordinate MOVE_ZPLUS(0,0,1);
mcpp::Coordinate MOVE_ZMINUS(0,0,-1);

mcpp::Coordinate temp = MOVE_ZPLUS;
mcpp::Coordinate temp2 = MOVE_XPLUS;
mcpp::Coordinate currPos = mc.getPlayerPosition();

int Counter = 0;

while(!this->endPoint(currPos,temp,temp2,mc))
{   
    if(!this->rightWallChecker(currPos, mc, temp,temp2))
    {
    
    this->turnRight(temp,temp2);
    currPos = currPos + temp;
    Counter++;
    delayCarpet(1000);
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
    delayCarpet(1000);
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    std::cout << "Step[" << Counter << "]: (" << currPos.x<< ", " << currPos.y<< ", " << currPos.z<< ")" << std::endl;
        
    }
    else {

    if(!this->frontWallChecker(currPos, mc, temp,temp2)){
    currPos = currPos + temp;
    Counter++;
    delayCarpet(1000);
    mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
    delayCarpet(1000);
    mc.setBlock(currPos, mcpp::Blocks::AIR);
    std::cout << "Step[" << Counter << "]: (" << currPos.x<< ", " << currPos.y<< ", " << currPos.z<< ")" << std::endl;
    }
    else{
        this->turnLeft(temp,temp2);
    }
         
    }

}
currPos = currPos + temp;
Counter++;
delayCarpet(1000);
mc.setBlock(currPos, mcpp::Blocks::LIME_CARPET);
delayCarpet(1000);
mc.setBlock(currPos, mcpp::Blocks::AIR);
std::cout << "Step[" << Counter << "]: (" << currPos.x<< ", " << currPos.y<< ", " << currPos.z<< ")" << std::endl;

}







