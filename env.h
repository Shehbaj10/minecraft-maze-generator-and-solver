#ifndef ENV
#define ENV
class Env {
    public:
    //constructors/de-constructors
    Env();
    Env(int length, int width);
    ~Env();
    //methods
    void setMazeSize(int, int);
    int getLength();
    int getWidth();
    void setEnvElement(char**);
    void setTerrain(int**);
    void setTerrainBlock(int**);
    void setTopTerrain(int***);
    void setTopTerrainBlock(int***);
    char getEnvElement(int, int);
    char** getEnvStructure();
    int** getTerrain();
    int** getTerrainBlock();
    int*** getTopTerrain();
    int*** getTopTerrainBlock();
    void setCoordinates(int, int, int);
    int getX_Coord();
    int getY_Coord();
    int getZ_Coord();

    // void playerSolvePos(int, int, int);
    // int getPlayer_X();
    // int getPlayer_Y();
    // int getPlayer_Z();
    

    private:
    //Fields
    int length;
    int width;
    char **envStructure;
    int **terrain_Height;
    int **terrain_Block;
    int ***topTerrain_Height;
    int ***topTerrain_Block;
    int xCoord;
    int yCoord;
    int zCoord;
    // int player_X;
    // int player_Y;
    // int player_Z;


};
#endif //ENV