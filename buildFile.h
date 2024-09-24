#ifndef ENV_BUILDER
#define ENV_BUILDER
class Env_Builder {
    public:
    //constructors/de-constructors
    Env_Builder();
    Env_Builder(int length, int width);
    // ~Env_Builder();
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
#endif //ENV_BUILDER