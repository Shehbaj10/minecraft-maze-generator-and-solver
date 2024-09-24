#include "buildFile.h"

Env_Builder::Env_Builder(){
    this->xCoord = 0;
    this->yCoord = 0;
    this->zCoord = 0;
    this->length = 0;
    this->width = 0;
    // this->player_X = 0;
    // this->player_Y = 0;
    // this->player_Z = 0;
    envStructure = new char*[length];
    for(int i =0; i < length; i++){
        envStructure[i] = new char[width];
    }
}
Env_Builder::Env_Builder(int length, int width) {
    this->length = length;
    this->width = width;
    envStructure = new char*[length];
    for(int i =0; i < length; i++){
        envStructure[i] = new char[width];
    }
}
// Env_Builder::~Env_Builder(){
//     for(int i=0; i < this->length; i++){
//         delete[] this->envStructure[i];
//     }
//     delete[] this->envStructure;
// }

void Env_Builder::setMazeSize(int length, int width) {
    this->length = length;
    this->width = width;
}
int Env_Builder::getLength() {
    return this->length;
}
int Env_Builder::getWidth() {
    return this->width;
}
void Env_Builder::setEnvElement(char** envStructure){
    this->envStructure = envStructure;
}

void Env_Builder::setTerrain(int** terrain_Height){
    this->terrain_Height = terrain_Height;
}

void Env_Builder::setTerrainBlock(int** terrain_Block){
    this->terrain_Block = terrain_Block;
}

void Env_Builder::setTopTerrain(int*** terrain_Height){
    this->topTerrain_Height = terrain_Height;
}

void Env_Builder::setTopTerrainBlock(int*** terrain_Block){
    this->topTerrain_Block = terrain_Block;
}

char** Env_Builder::getEnvStructure(){
    return this->envStructure;
}

int** Env_Builder::getTerrain(){
    return this->terrain_Height;
}

int** Env_Builder::getTerrainBlock(){
    return this->terrain_Block;
}

int*** Env_Builder::getTopTerrain(){
    return this->topTerrain_Height;
}

int*** Env_Builder::getTopTerrainBlock(){
    return this->topTerrain_Block;
}

char Env_Builder::getEnvElement(int row, int col){
    return this->envStructure[row][col];
}
void Env_Builder::setCoordinates(int xCoord, int yCoord, int zCoord){
    this->xCoord = xCoord;
    this->yCoord = yCoord;
    this->zCoord = zCoord;
}

// void Env::playerSolvePos(int player_X, int player_Y, int player_Z){
//     this->player_X = player_X;
//     this->player_Y = player_Y;
//     this->player_Z = player_Z;
// }

int Env_Builder::getX_Coord(){
    return this->xCoord;
}
int Env_Builder::getY_Coord(){
    return this->yCoord;
}
int Env_Builder::getZ_Coord(){
    return this->zCoord;
}

// int Env::getPlayer_X(){
//     return this->player_X;
// }
// int Env::getPlayer_Y(){
//     return this->player_Y;
// }
// int Env::getPlayer_Z(){
//     return this->player_Z;
// }
