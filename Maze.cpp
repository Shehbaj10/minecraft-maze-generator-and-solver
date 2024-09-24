#include "Maze.h"
#include <random>


Maze::Maze() {
    // Initialize variables and allocate memory for the maze structure.
    }

/*
* CoordinateInput function gets the input for the coordinates (X, Y, Z) from the user.
* Initialize variables and flags for coordinate validation.
* Input X, Y, and Z coordinates and validate them.
* Set the build_x, build_y, and build_z values based on user input.
 */
void Maze::CoordinateInput(int& build_x, int& build_y, int& build_z, mcpp::MinecraftConnection& mc){
    std::string coordInput = "" ;

    std::string coordinates[3];

    int num = 1;
    int a = 0;
    int b = 0;
    int c = 0;

    while (num !=0 ){
        std::cin >> coordinates[0];
        std::cin >> coordinates[1];
        std::cin >> coordinates[2];
        
        for (int i = 0; i < 3; i++){
            coordInput = coordinates[i];

            if(coordInput[0] == '-'){
                coordInput.erase(0, 1);
            }

            int coordLength = coordInput.length();
            int j = 0;
            int checker = 0 ;

            while (coordLength != 0){                
                if (isdigit(coordInput[j])){
                    j++ ;
                    coordLength-=1 ;
                }
                else {
                    coordLength = 0;
                    checker++ ;
                }
            }

            if(i == 0 && checker == 0){
                a = 1;
            }   
            else if(i == 1 && checker == 0) {
                b = 1;
            }   
            else if(i == 2 && checker == 0){
                c = 1;
            }    
            else{
                a = 0;
                b = 0;
                c = 0;
            }
        }

        if ( a == 1 && b == 1 && c == 1){
            if(stoi(coordinates[1]) == mc.getHeight(stoi(coordinates[0]),stoi(coordinates[2])) + 1){
            build_x = stoi(coordinates[0]);
            build_y = stoi(coordinates[1]);
            build_z = stoi(coordinates[2]);
            num = 0;
        }
        else{
            if(mc.getBlock(mcpp::Coordinate(stoi(coordinates[0]), mc.getHeight(stoi(coordinates[0]),stoi(coordinates[2])), stoi(coordinates[2]))) == mcpp::Blocks::ACACIA_WOOD_PLANK){
                if(stoi(coordinates[1]) == mc.getHeight(stoi(coordinates[0]),stoi(coordinates[2])) - 2) {
            build_x = stoi(coordinates[0]);
            build_y = stoi(coordinates[1]);
            build_z = stoi(coordinates[2]);
            num = 0;
            }
            else{
                std::cout << std::endl;
            std::cout << "Input Error! please enter Y-Coordinate above the ground level";
            std::cout << std::endl;
            num = 1;
            }
            }
            else{
                std::cout << std::endl;
            std::cout << "Input Error! please enter Y-Coordinate above the ground level";
            std::cout << std::endl;
            num = 1;
            }
        }
        }
        else {
            std::cout << std::endl;
            std::cout << "Input Error! please enter 3 numerical X, Y and Z Coordinates";
            std::cout << std::endl;
            num = 1;
        }
        }
    }

/*
* This function gets the dimensions (length and width) of the maze from the user.
* Initialize variables and flags for dimension validation.
* Input maze dimensions and validate them.
* Set Maze_Length and Maze_Width based on user input.
*/
void Maze::getNumericInput(int& Maze_Length, int& Maze_Width){
    std::string coordInput = " ";

    std::string dimensions[2];

    int num = 1;
    int a = 0;
    int b = 0;

    while (num !=0 ){
        std::cin >> dimensions[0];
        std::cin >> dimensions[1];

        for (int i = 0; i < 2; i++){
            coordInput = dimensions[i];

            int coordLength = coordInput.length();
            int j = 0;
            int checker = 0 ;

            while (coordLength != 0){                
                if (isdigit(coordInput[j])){
                    j++ ;
                    coordLength-=1 ;
                }
                else {
                    coordLength = 0;
                    checker++ ;
                }
            }


            if (checker == 0){
                if(i == 0){
                    a = true;
                }   
                else if(i == 1) {
                    b = true;
                }   
            }
            else {
                if(i == 0){
                    a = false;
                }   
                else if(i == 1) {
                    b = false;
                }   
            }
        }

        if ( a == 1 && b == 1 && stoi(dimensions[0]) >= 3 && stoi(dimensions[1]) >= 3 && stoi(dimensions[0]) % 2 != 0 && stoi(dimensions[1]) % 2 != 0){
            Maze_Length = stoi(dimensions[0]);
            Maze_Width = stoi(dimensions[1]);
            num = 0;
        }
        else {
            std::cout << std::endl;
            std::cout << "Input Error! the input needs to be positive odd numerical and atleast 3";
            std::cout << std::endl;
            num = 1;
        }
        }
    }

bool Maze::isValid(int x, int z, int Maze_Length, int Maze_Width) {
    return x >= 0 && x < Maze_Length && z >= 0 && z < Maze_Width;
}

void Maze::dfs(int x, int z, char** Maze_Structure, bool** visited,int Maze_Width,int Maze_Length,char toFind ) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    visited[x][z] = true;

    for (int i = 0; i < 4; ++i) {
        int newX = x + dx[i];
        int newZ = z + dy[i];
        if (this->isValid(newX, newZ, Maze_Length, Maze_Width) && Maze_Structure[newX][newZ] == toFind && !visited[newX][newZ]) {
            this->dfs(newX, newZ, Maze_Structure, visited, Maze_Width, Maze_Length, toFind);
        }
    }
}

/*
* getMazeStructure Function
* Initialize variables for reading the maze structure and validation.
* Read characters ('x' for walls, '.' for paths) and validate the maze.
*/
void Maze::getMazeStructure(char** Maze_Structure, int Maze_Length, int Maze_Width){
    char readChar;
    int num = 1;
    int checker = 0;
    int exitX = 0;
    int exitZ = 0;
    
    
    while(num != 0){
    checker = 0;
    for (int row = 0; row < Maze_Length; row++) 
    {
        for (int col = 0; col < Maze_Width; col++) 
        {
            std::cin >> readChar;
            if(readChar == 'x' || readChar == '.'){
            Maze_Structure[row][col] = readChar;
            }
            else{
                Maze_Structure[row][col] = readChar;
                checker++;
            }
        }
    }    
    int numTotalX = 0;
    int numTotalDot = 0;
    int countX = 0;
    int countDot = 0;

        if (checker == 0)
        {
        checker = 0;

        for (int i = 0; i < Maze_Length; i++) 
        {
            if (Maze_Structure[i][0] == '.'){
                exitX = i;
                exitZ = 0;
                checker++;
            }
        }
        for (int i = 0; i < Maze_Length; i++) 
        {
            if (Maze_Structure[i][Maze_Width - 1] == '.'){
                exitX = i;
                exitZ = Maze_Width - 1;
                checker++;
            }
        }
        for (int i = 0; i < Maze_Width; i++) 
        {
            if (Maze_Structure[0][i] == '.'){
                exitX = 0;
                exitZ = i;
                checker++;
            }
        }
        for (int i = 0; i < Maze_Width; i++) 
        {
            if (Maze_Structure[Maze_Length - 1][i] == '.'){
                exitX = Maze_Length - 1;
                exitZ = i;
                checker++;
            }
        }

        if (checker != 1){
            std::cout << std::endl;
            std::cout << "Error! pls enter a maze with exactly 1 exit";
            std::cout << std::endl;
            num = 1;
            checker = 0;
        }
        else{
            checker = 0;
            bool ender = false;
            for (int i = 0; i < Maze_Length - 1; i++) 
            {
                for (int j = 0; j < Maze_Width - 1; j++) 
                {
                    if (Maze_Structure[i][j] == '.'){
                    checker++;
                    }
                    if (Maze_Structure[i][j+1] == '.'){
                    checker++;
                    }
                    if (Maze_Structure[i+1][j] == '.'){
                    checker++;
                    }
                    if (Maze_Structure[i+1][j+1] == '.'){
                    checker++;
                    }
                    if(checker == 4){
                        ender = true;
                    }
                    checker = 0;
                }
            }
            if(ender){
            std::cout << std::endl;
            std::cout << "Error! pls enter a maze with path of width 1";
            std::cout << std::endl;
            num = 1;
            }
            else
            {

    char toFind = 'x';

    bool **visited;
    visited = new bool*[Maze_Length];
    for(int i=0; i < Maze_Length; i++){
        visited[i] = new bool[Maze_Width];
        }

    int startX, startY;

    startX = 0;
    startY = 0;

    for (int i = 0; i < Maze_Length; ++i) {
        for (int j = 0; j < Maze_Width; ++j) {
            visited[i][j] = false;
        }
    }

    this->dfs(startX, startY, Maze_Structure, visited, Maze_Width, Maze_Length, toFind);

    
    for (int i = 0; i < Maze_Length; ++i) {
        for (int j = 0; j < Maze_Width; ++j) {
            if (visited[i][j] && Maze_Structure[i][j] == toFind) {
                countX++;
            }
        }
    }

for (int i = 0; i < Maze_Length; i++) {
        for (int j = 0; j < Maze_Width; j++) {
            if (Maze_Structure[i][j] == 'x') {
                numTotalX++;
            }
        }
    }


    if(countX - numTotalX != 0){
        std::cout << std::endl;
        std::cout << "Error! pls enter a perfect maze without loop";
        std::cout << std::endl;
    }
    else{

                char toFind = '.';
                startX = exitX;
    startY = exitZ;

    for (int i = 0; i < Maze_Length; ++i) {
        for (int j = 0; j < Maze_Width; ++j) {
            visited[i][j] = false;
        }
    }

    this->dfs(startX, startY, Maze_Structure, visited, Maze_Width, Maze_Length, toFind);

    
    for (int i = 0; i < Maze_Length; ++i) {
        for (int j = 0; j < Maze_Width; ++j) {
            if (visited[i][j] && Maze_Structure[i][j] == toFind) {
                countDot++;
            }
        }
    }

    for (int i = 0; i < Maze_Length; i++) {
        for (int j = 0; j < Maze_Width; j++) {
            if (Maze_Structure[i][j] == '.') {
                numTotalDot++;
            }
        }
    }

    if(countDot - numTotalDot != 0){
        std::cout << std::endl;
        std::cout << "Error! pls enter a perfect maze without walls blocking the pathway";
        std::cout << std::endl;
    }
    else{
    num = 0;
    }


    }
            } 
        }
            
        }
        else {
            std::cout << std::endl;
            std::cout << "Error! pls enter characters either x for wall or . for path";
            std::cout << std::endl;
            num = 1;
            checker = 0;
        }

        

    
     }
}

void Maze::printMazeStructure(char** Maze_Structure, int Maze_Length, int Maze_Width){
    for (int row = 0; row < Maze_Length; row++) 
    {
        for (int col = 0; col < Maze_Width; col++) 
        {
            std::cout << Maze_Structure[row][col];
            }
            std::cout << std::endl;
            }
}

void Maze::readMazeTerminal(Env& env,mcpp::MinecraftConnection& mc){

    int build_x = 0;
    int build_y = 0;
    int build_z = 0;

    int Maze_Length = 0;
    int Maze_Width = 0;
                    
    std::cout << "Enter the basePoint of maze: " << std::endl;
    this->CoordinateInput(build_x, build_y, build_z,mc);
    env.setCoordinates(build_x, build_y, build_z);

    std::cout << "Enter the length and width of maze: " << std::endl;
    this->getNumericInput(Maze_Length, Maze_Width);
    env.setMazeSize(Maze_Length, Maze_Width);

    std::cout << "Enter the maze structure: " << std::endl;
    char **Maze_Structure;
    Maze_Structure = new char*[Maze_Length];
    for(int i=0; i < Maze_Length; i++){
        Maze_Structure[i] = new char[Maze_Width];
        }
                    
    this->getMazeStructure(Maze_Structure, Maze_Length, Maze_Width);
    env.setEnvElement(Maze_Structure);

    std::cout << "Maze read successfully" << std::endl;
    std::cout << "**Printing Maze**" << std::endl;
    std::cout << "BasePoint: (" << env.getX_Coord() << ", " << env.getY_Coord() << ", " << env.getZ_Coord() << ")" << std::endl;
    std::cout << "Structure: " << std::endl;

    this->printMazeStructure(env.getEnvStructure(), env.getLength(), env.getWidth());
                                    
    std::cout << "**End Printing Maze**" << std::endl;
}


///////////////////////////////////////////////////////
void Maze::newMaze(int Maze_Length, int Maze_Width, char**& mazeStructure) {
    for (int x = 0; x < Maze_Length; x++) {
        for (int z = 0; z < Maze_Width; z++) {
            if(x % 2 != 0 && z % 2 != 0){
                mazeStructure[x][z] = ' ';
            }
            else{
                mazeStructure[x][z] = 'x';
            }
        }
    }
}

void Maze::FirstStep(int Maze_Length, int Maze_Width, char**& Maze_Structure, int& startx, int& startz,  bool mode){
    int min = 1;
    int min2 = 1;
    int max = Maze_Length - 2;
    int max2 = Maze_Width - 2;
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    std::uniform_int_distribution<int> uniform_dist2(min2, max2);
    int value = -1;
    int value2 = -1;
    int exitLoop = 0;

    while(exitLoop == 0){
    value = uniform_dist(engine);
    value2 = uniform_dist2(engine);
    if((value == 1 || value == Maze_Length - 2 || value2 == 1 || value2 == Maze_Width - 2) && value % 2 != 0 && value2 % 2 != 0){
        exitLoop = 1;
    }
    }

    int arr[4] = {Maze_Length - 1 - value, value - 0, Maze_Width - 1 - value2, value2 - 0};
    int minimum = arr[0];
    int minimum_index = 0;
    for(int i = 0; i < 4; i++){
        if(arr[i] < minimum){
            minimum = arr[i];
            minimum_index = i;
        }
    }
    
    if(!mode){
    Maze_Structure[value][value2] = '*';
    startx = value;
    startz = value2;

    if(minimum_index == 0){
        Maze_Structure[Maze_Length - 1][value2] = '.';
    }
    else if(minimum_index == 1){
        Maze_Structure[0][value2] = '.';
    }
    else if(minimum_index == 2){
        Maze_Structure[value][Maze_Width - 1] = '.';
    }
    else if(minimum_index == 3){
        Maze_Structure[value][0] = '.';
    }
    }
    else{
    Maze_Structure[1][1] = '*';
    startx = 1;
    startz = 1;
    Maze_Structure[1][0] = '.';
    }
}

void Maze::PathChecker(int Maze_Length, int Maze_Width, char**& mazeStructure, int**& valid, std::vector<std::vector<int>>& lastCoords, int& number){
    
    int loop = 1;

    for (int g = 0; g < 2; g++) {
        for (int h = 0; h < 2; h++) {
            valid[g][h] = 0;
        }
        }
    
    while(loop != 0){
    int currLoc_x = 0;
    int currLoc_z = 0;
    int nextLoc_x = 0;
    int nextLoc_z = 0;
    int dont1 = 0;
    int dont2 = 0;
    int dont3 = 0;
    int dont4 = 0;
    int proceed = 0;
    int checker = 0;
    for (int x = 0; x < Maze_Length; x++) {
        for (int z = 0; z < Maze_Width; z++) {
            if(mazeStructure[x][z] == '*'){
                currLoc_x = x;
                currLoc_z = z;
            }
        }
    }


    if(mazeStructure[currLoc_x + 1][currLoc_z] == 'x'){
        if(currLoc_x + 1 == 0 || currLoc_x + 1 == Maze_Length - 1 || currLoc_z == 0 || currLoc_z == Maze_Width - 1){
            dont1 = 1;
        }
        else {
            checker++;
        }
    }
    if(mazeStructure[currLoc_x - 1][currLoc_z] == 'x'){
        if(currLoc_x - 1 == 0 || currLoc_x - 1 == Maze_Length - 1 || currLoc_z == 0 || currLoc_z == Maze_Width - 1){
            dont2 = 1;
        }
        else {
            checker++;
        }
    }
    if(mazeStructure[currLoc_x][currLoc_z + 1] == 'x'){
        if(currLoc_x == 0 || currLoc_x == Maze_Length - 1 || currLoc_z + 1 == 0 || currLoc_z + 1 == Maze_Width - 1){
            dont3 = 1;
        }
        else {
            checker++;
        }
    }
    if(mazeStructure[currLoc_x][currLoc_z - 1] == 'x'){
        if(currLoc_x == 0 || currLoc_x == Maze_Length - 1 || currLoc_z - 1 == 0 || currLoc_z - 1 == Maze_Width - 1){
            dont4 = 1;
        }
        else {
            checker++;
        }
    }


    if(checker != 0){
        if(mazeStructure[currLoc_x + 1][currLoc_z] == 'x' && dont1 == 0){ // down
            nextLoc_x = currLoc_x + 1;
            nextLoc_z = currLoc_z;
            if(mazeStructure[nextLoc_x + 1][nextLoc_z] == ' '){
                proceed++;
            }

            if(proceed == 1){
                valid[1][1]++;
                }
            proceed = 0;
        }
        if(mazeStructure[currLoc_x - 1][currLoc_z] == 'x'  && dont2 == 0){ // up
            nextLoc_x = currLoc_x - 1;
            nextLoc_z = currLoc_z;

            if(mazeStructure[nextLoc_x - 1][nextLoc_z] == ' '){
                proceed++;
            }


            if(proceed == 1){
                valid[0][0]++;
                }
            proceed = 0;
        }

        if(mazeStructure[currLoc_x][currLoc_z + 1] == 'x'  && dont3 == 0){//right
            nextLoc_x = currLoc_x;
            nextLoc_z = currLoc_z + 1;

            if(mazeStructure[nextLoc_x][nextLoc_z + 1] == ' '){
                proceed++;
            }

            if(proceed == 1){
                valid[0][1]++;
                }
            proceed = 0;
        }

        if(mazeStructure[currLoc_x][currLoc_z - 1] == 'x'  && dont4 == 0){//left
            nextLoc_x = currLoc_x;
            nextLoc_z = currLoc_z - 1;

            if(mazeStructure[nextLoc_x][nextLoc_z - 1] == ' '){
                proceed++;
            }

            if(proceed == 1){
                valid[1][0]++;
                }
            proceed = 0;
        }


    
    }
    for (int x = 0; x < 2; x++) {
        for (int z = 0; z < 2; z++) {
            if(valid[x][z] == 1){
                number++;
            }
        }
    }
    
    int outerSize = int(lastCoords.size());
    int innerSize = int(lastCoords[outerSize-1].size());

    if(number == 0 && outerSize != 0){
        mazeStructure[currLoc_x][currLoc_z] = '.';
        mazeStructure[lastCoords[outerSize - 1][innerSize - 2]][lastCoords[outerSize - 1][innerSize - 1]] = '*';
        lastCoords.pop_back();
        loop = 1;
    }
    else{
        loop = 0;
    }
    
}


}

void Maze::PathMaker(int Maze_Length, int Maze_Width, char**& mazeStructure, int**& valid, std::vector<std::vector<int>>& lastCoords, bool mode) {
    int num = 0;
    std::vector<int> v2;
    int currLoc_x = 0;
    int currLoc_z = 0;
    int value = -1;
    int count = 0;
    for (int x = 0; x < 2; x++) {
        for (int z = 0; z < 2; z++) {
            if(valid[x][z] == 1){
                num++;
            }
        }
    }

    if(num != 0 && num != 1){
    int min = 1;
    int max = num;
    
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    value = uniform_dist(engine);
    }
    else {
        value = 1;
    }
    
    
    
    
    for (int x = 0; x < Maze_Length; x++) {
        for (int z = 0; z < Maze_Width; z++) {
            if(mazeStructure[x][z] == '*'){
                currLoc_x = x;
                currLoc_z = z;
                mazeStructure[x][z] = '.';
            }
        }
    }

    if(num != 1 && lastCoords[0][0] != currLoc_x && lastCoords[0][1] != currLoc_z){
    v2.push_back(currLoc_x);
    v2.push_back(currLoc_z);
    lastCoords.push_back(v2);
    }
    if(!mode){
    for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
            if(valid[a][b] == 1){
                valid[a][b] = 0;
                count++;
                if(count == value){
                    if(a == 0 && b == 0){ // up
                        mazeStructure[currLoc_x - 1][currLoc_z] = '*';
                            if(mazeStructure[currLoc_x - 2][currLoc_z] == ' '){
                                mazeStructure[currLoc_x - 1][currLoc_z] = '.';
                                mazeStructure[currLoc_x - 2][currLoc_z] = '*';
                            }
                        }
                    
                    else if(a == 0 && b == 1){ // right 
                        mazeStructure[currLoc_x][currLoc_z + 1] = '*';
                        if(mazeStructure[currLoc_x][currLoc_z + 2] == ' '){
                                mazeStructure[currLoc_x][currLoc_z + 1] = '.';
                                mazeStructure[currLoc_x][currLoc_z + 2] = '*';
                            }
                    }
                    else if(a == 1 && b == 1){  // down
                        mazeStructure[currLoc_x + 1][currLoc_z] = '*'; 
                        if(mazeStructure[currLoc_x + 2][currLoc_z] == ' '){
                                mazeStructure[currLoc_x + 1][currLoc_z] = '.';
                                mazeStructure[currLoc_x + 2][currLoc_z] = '*';
                    }
                    }
                    else if(a == 1 && b == 0){ // left
                        mazeStructure[currLoc_x][currLoc_z - 1] = '*';
                        if(mazeStructure[currLoc_x][currLoc_z - 2] == ' '){
                                mazeStructure[currLoc_x][currLoc_z - 1] = '.';
                                mazeStructure[currLoc_x][currLoc_z - 2] = '*';
                            }
                    }
                    
                }        
            }
        }
    }
    }
    else {
        for (int a = 0; a < 1; a++) {
        for (int b = 0; b < 2; b++) {
            if(valid[a][b] == 1){
                valid[a][b] = 0;
                count++;
                value = 1;
                if(count == value){
                    if(a == 0 && b == 0){ // up
                        mazeStructure[currLoc_x - 1][currLoc_z] = '*';
                            if(mazeStructure[currLoc_x - 2][currLoc_z] == ' '){
                                mazeStructure[currLoc_x - 1][currLoc_z] = '.';
                                mazeStructure[currLoc_x - 2][currLoc_z] = '*';
                            }
                        }
                    
                    else if(a == 0 && b == 1){ // right 
                        mazeStructure[currLoc_x][currLoc_z + 1] = '*';
                        if(mazeStructure[currLoc_x][currLoc_z + 2] == ' '){
                                mazeStructure[currLoc_x][currLoc_z + 1] = '.';
                                mazeStructure[currLoc_x][currLoc_z + 2] = '*';
                            }
                    }
                }        
            }
        }
    }
    for (int a = 1; a < 2; a++) {
        for (int b = 1; b >= 0; b--) {
            if(valid[a][b] == 1){
                valid[a][b] = 0;
                count++;
                value = 1;
                if(count == value){
                    if(a == 1 && b == 1){  // down
                        mazeStructure[currLoc_x + 1][currLoc_z] = '*'; 
                        if(mazeStructure[currLoc_x + 2][currLoc_z] == ' '){
                                mazeStructure[currLoc_x + 1][currLoc_z] = '.';
                                mazeStructure[currLoc_x + 2][currLoc_z] = '*';
                    }
                    }
                    else if(a == 1 && b == 0){ // left
                        mazeStructure[currLoc_x][currLoc_z - 1] = '*';
                        if(mazeStructure[currLoc_x][currLoc_z - 2] == ' '){
                                mazeStructure[currLoc_x][currLoc_z - 1] = '.';
                                mazeStructure[currLoc_x][currLoc_z - 2] = '*';
                            }
                    }
                    
                
                }        
            }
        }
    }

    }
}

void Maze::makeRandomMaze(Env& env,mcpp::MinecraftConnection& mc, bool mode) {
    int build_x = 0;
    int build_y = 0;
    int build_z = 0;

    int Maze_Length = 0;
    int Maze_Width = 0;
    int startx = 0;
    int startz = 0;
    std::cout << "Enter the basePoint of maze: " << std::endl;
    this->CoordinateInput(build_x, build_y, build_z,mc);
    env.setCoordinates(build_x, build_y, build_z);

    std::cout << "Enter the length and width of maze: " << std::endl;
    this->getNumericInput(Maze_Length, Maze_Width);
    env.setMazeSize(Maze_Length, Maze_Width);

    int l = Maze_Length;
    int w = Maze_Width;
    char **Maze_Structure3;
    Maze_Structure3 = new char*[l];
    for(int i=0; i < l; i++){
        Maze_Structure3[i] = new char[w];
        }
             newMaze(l,w,Maze_Structure3);
             
    int **path;
    path = new int*[2];
        for(int i=0; i < 2; i++){
            path[i] = new int[2];
            }
    for(int i=0; i < 2; i++){
                    for(int j=0; j < 2; j++){
            path[i][j] = 0;
            }
            }

    int number = 0;
            this->FirstStep(l,w,Maze_Structure3,startx,startz,mode);
            std::vector<std::vector<int>> lastCoords{{startx,startz}};
            this->PathChecker(l,w,Maze_Structure3,path,lastCoords,number);
            while(number != 0){
                number = 0;
                
            this->PathMaker(l, w, Maze_Structure3,path,lastCoords,mode);
                    
            
            
            this->PathChecker(l,w,Maze_Structure3,path,lastCoords,number);
            
                    }
                    for (int x = 0; x < l; x++) {
            for (int z = 0; z < w; z++) {
                if(Maze_Structure3[x][z] == '*'){
                    Maze_Structure3[x][z] = '.';
                }
            }
        }
        env.setEnvElement(Maze_Structure3);
    std::cout << "Maze generated successfully" << std::endl;
    std::cout << "**Printing Maze**" << std::endl;
    std::cout << "BasePoint: (" << env.getX_Coord() << ", " << env.getY_Coord() << ", " << env.getZ_Coord() << ")" << std::endl;
    std::cout << "Structure: " << std::endl;

    this->printMazeStructure(env.getEnvStructure(), env.getLength(), env.getWidth());
                                    
    std::cout << "**End Printing Maze**" << std::endl;
}


Maze::~Maze()
{
}