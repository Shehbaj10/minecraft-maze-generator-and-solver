#include "env.h"

Env::Env(){
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
Env::Env(int length, int width) {
    this->length = length;
    this->width = width;
    envStructure = new char*[length];
    for(int i =0; i < length; i++){
        envStructure[i] = new char[width];
    }
}
Env::~Env(){
    for(int i=0; i < this->length; i++){
        delete[] this->envStructure[i];
    }
    delete[] this->envStructure;
}

void Env::setMazeSize(int length, int width) {
    this->length = length;
    this->width = width;
}
int Env::getLength() {
    return this->length;
}
int Env::getWidth() {
    return this->width;
}
void Env::setEnvElement(char** envStructure){
    this->envStructure = envStructure;
}

void Env::setTerrain(int** terrain_Height){
    this->terrain_Height = terrain_Height;
}

void Env::setTerrainBlock(int** terrain_Block){
    this->terrain_Block = terrain_Block;
}

void Env::setTopTerrain(int*** terrain_Height){
    this->topTerrain_Height = terrain_Height;
}

void Env::setTopTerrainBlock(int*** terrain_Block){
    this->topTerrain_Block = terrain_Block;
}

char** Env::getEnvStructure(){
    return this->envStructure;
}

int** Env::getTerrain(){
    return this->terrain_Height;
}

int** Env::getTerrainBlock(){
    return this->terrain_Block;
}

int*** Env::getTopTerrain(){
    return this->topTerrain_Height;
}

int*** Env::getTopTerrainBlock(){
    return this->topTerrain_Block;
}

char Env::getEnvElement(int row, int col){
    return this->envStructure[row][col];
}
void Env::setCoordinates(int xCoord, int yCoord, int zCoord){
    this->xCoord = xCoord;
    this->yCoord = yCoord;
    this->zCoord = zCoord;
}

// void Env::playerSolvePos(int player_X, int player_Y, int player_Z){
//     this->player_X = player_X;
//     this->player_Y = player_Y;
//     this->player_Z = player_Z;
// }

int Env::getX_Coord(){
    return this->xCoord;
}
int Env::getY_Coord(){
    return this->yCoord;
}
int Env::getZ_Coord(){
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
