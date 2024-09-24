#ifndef WORLDCLEANER
#define WORLDCLEANER

#include <iostream>
#include <chrono>

void delay(int milliseconds) {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto end_time = start_time + std::chrono::milliseconds(milliseconds);
        
        while (std::chrono::high_resolution_clock::now() < end_time) {
            // Busy-wait loop
        }
    }

void unFlattenTerrain(int build_x, int build_y , int build_z , int Maze_Length, int Maze_Width, mcpp::MinecraftConnection& mc, int** Terrain_Structure, int** Terrain_BlockType, int*** topStructure, int*** topBlockType) {
    int newHeight = 0;
    int blockType = 0;
    for (int x = build_x; x < build_x + Maze_Length; x++) {
        for (int z = build_z ; z < build_z + Maze_Width; z++) {
                for (int y = 0; y < int(sizeof(topStructure[x - build_x][z - build_z])); y++) {
                newHeight = topStructure[y][x - build_x][z - build_z];
                blockType = topBlockType[y][x - build_x][z - build_z];
                    delay(50);
                    mc.setBlock(mcpp::Coordinate(x, newHeight, z), blockType);
                }
                newHeight = Terrain_Structure[x - build_x][z - build_z];
                blockType = Terrain_BlockType[x - build_x][z - build_z];
                
                if(newHeight < build_y){
                for (int y = newHeight + 1; y < build_y; y++) {
                    delay(50);
                        mc.setBlock(mcpp::Coordinate(x, y, z), mcpp::Blocks::AIR);
                    }
                }
                
        }
    }
    
}

void clearMaze(int build_x, int build_y , int build_z , int Maze_Length, int Maze_Width, mcpp::MinecraftConnection& mc) {
    for (int x = 0; x < Maze_Length; x++) {
        for (int z = 0; z < Maze_Width; z++) {
            for (int y = 0; y < 3; y++) {
                delay(50);
                mc.setBlock(mcpp::Coordinate(build_x + x, build_y + y, build_z + z), mcpp::Blocks::AIR);
            }
        }
    }
}

#endif //MENU_UTILS_H
