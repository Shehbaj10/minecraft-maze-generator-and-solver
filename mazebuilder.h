#ifndef MAZEBUILDER
#define MAZEBUILDER

#include "env.h"
#include "buildFile.h"
#include "WorldCleaner.h"
#include <iostream>




bool doesMazeExist(int build_x, int build_y , int build_z , int Maze_Length, int Maze_Width, char**& Maze_Structure, mcpp::MinecraftConnection& mc) {

bool mazeExists = false;
    for (int x = build_x ; x < build_x + Maze_Length && !mazeExists; x++) {
        for (int z = build_z ; z < build_z + Maze_Width && !mazeExists; z++) {
            for (int y = build_y; y < build_y + 3; y++) {
                mcpp::BlockType blockType = mc.getBlock(mcpp::Coordinate(x, y, z));

                if (blockType == mcpp::Blocks::ACACIA_WOOD_PLANK) {
                    mazeExists = true;
                }
            }
        }
    }

    return mazeExists;
}

void flattenTerrain(int build_x, int build_y , int build_z , int Maze_Length, int Maze_Width, mcpp::MinecraftConnection& mc, int**& Terrain_Structure, int**& Terrain_BlockType, int***& topStructure, int***& topBlockType) {
    int newHeight = 0;
    
    for (int x = build_x; x < build_x + Maze_Length; x++) {
        for (int z = build_z ; z < build_z + Maze_Width; z++) {
                    
                        newHeight = mc.getHeight(x, z);
                        if(newHeight >= build_y){
                            for (int y = build_y; y <= newHeight; y++) {
                        topStructure[y - build_y][x - build_x][z - build_z] = y;
                        int topBlock = mc.getBlock(mcpp::Coordinate(x, y, z)).id;
                        topBlockType[y - build_y][x - build_x][z - build_z] = topBlock;
                        delay(50);
                        mc.setBlock(mcpp::Coordinate(x, y, z), mcpp::Blocks::AIR);
                            }
                    }
                
                newHeight = mc.getHeight(x, z);
                Terrain_Structure[x - build_x][z - build_z] = newHeight;
                int blockType = mc.getBlock(mcpp::Coordinate(x, newHeight, z)).id;
                Terrain_BlockType[x - build_x][z - build_z] = blockType;
                if(newHeight < build_y){
                    for (int y = newHeight; y <= build_y - 1; y++) {
                        delay(50);
                        mc.setBlock(mcpp::Coordinate(x, y, z), blockType);
                    }
                }
                
        }
    }
}



void teleportPlayer(int build_x, int build_y , int build_z , mcpp::MinecraftConnection& mc) {
    int newY = build_y + 10;
    mc.setPlayerPosition(mcpp::Coordinate(build_x, newY, build_z));
}

void buildWalls(int build_x, int build_y , int build_z , int Maze_Length, int Maze_Width, char** Maze_Structure , mcpp::MinecraftConnection& mc) {
    for (int x = 0; x < Maze_Length; x++) {
        for (int z = 0; z < Maze_Width; z++) {
            if (Maze_Structure[x][z] == 'x') {
                for (int y = 0; y < 3; y++) {
                    delay(50);
                    mc.setBlock(mcpp::Coordinate(build_x + x, build_y + y, build_z + z), mcpp::Blocks::ACACIA_WOOD_PLANK);
                }
            }
            else if(Maze_Structure[x][z] == '.'){
                for (int y = 0; y < 3; y++) {
                    mc.setBlock(mcpp::Coordinate(build_x + x, build_y + y, build_z + z), mcpp::Blocks::AIR);
                }
            }
        }
    }
}

void mazeMaker(Env& env, mcpp::MinecraftConnection& mc, Env_Builder& env_Builder) {
    int xCoord = env.getX_Coord(); 
            int yCoord = env.getY_Coord();
            int zCoord = env.getZ_Coord();
            int x_len = env.getLength();
            int z_len = env.getWidth();
            char **Maze_Structure = env.getEnvStructure();

            int **Terrain_Structure;
            Terrain_Structure = new int*[x_len];
            for(int i=0; i < x_len; i++){
                Terrain_Structure[i] = new int[z_len];
            }
    
            int **Terrain_BlockType;
            Terrain_BlockType = new int*[x_len];
            for(int i=0; i < x_len; i++){
                Terrain_BlockType[i] = new int[z_len];
            }

            int ***topStructure;
            topStructure = new int**[100];
            for(int i=0; i < 100; i++){
                topStructure[i] = new int*[x_len];
                for(int j=0; j < x_len; j++){
                    topStructure[i][j] = new int[z_len];
                }
            }

            int ***topBlockType;
            topBlockType = new int**[100];
            for(int i=0; i < 100; i++){
                topBlockType[i] = new int*[x_len];
                for(int j=0; j < x_len; j++){
                    topBlockType[i][j] = new int[z_len];
                }
            }



            bool mazeChecker = doesMazeExist(xCoord, yCoord , zCoord, x_len, z_len, Maze_Structure, mc);
            
            if (mazeChecker)
            {
                clearMaze(env_Builder.getX_Coord(), env_Builder.getY_Coord(), env_Builder.getZ_Coord(), env_Builder.getLength(), env_Builder.getWidth(), mc);
                unFlattenTerrain(env_Builder.getX_Coord(), env_Builder.getY_Coord() , env_Builder.getZ_Coord() , env_Builder.getLength(), env_Builder.getWidth(), mc, env_Builder.getTerrain(), env_Builder.getTerrainBlock(),env_Builder.getTopTerrain(), env_Builder.getTopTerrainBlock());

            }

    teleportPlayer(xCoord, yCoord , zCoord, mc);
    flattenTerrain(xCoord, yCoord , zCoord, x_len, z_len, mc, Terrain_Structure, Terrain_BlockType, topStructure, topBlockType);
    env.setTerrain(Terrain_Structure);
    env.setTerrainBlock(Terrain_BlockType);
    env.setTopTerrain(topStructure);
    env.setTopTerrainBlock(topBlockType);
    buildWalls(xCoord, yCoord , zCoord, x_len, z_len, Maze_Structure, mc);
    env_Builder.setCoordinates(xCoord, yCoord, zCoord);
    env_Builder.setMazeSize(env.getLength(), env.getWidth());
    env_Builder.setEnvElement(Maze_Structure);
    env_Builder.setTerrain(Terrain_Structure);
    env_Builder.setTerrainBlock(Terrain_BlockType);
    env_Builder.setTopTerrain(topStructure);
    env_Builder.setTopTerrainBlock(topBlockType);

}

#endif //MAZEBUILDER