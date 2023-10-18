#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {

    ifstream infs (fileName);
    
    if (infs.is_open()){
        
        double a, b, c, d;
        infs >> a >> b >> c >> d;
         
        if(a+b >= INT32_MAX){
            return nullptr;
        } 

        if(a*b >= INT32_MAX){ 
            return nullptr;
        } 


        player.row = (int)c;
        player.col = (int)d;

        maxRow = (int)a;
        maxCol = (int)b;

        if ((maxRow == 0) || (maxCol == 0)){
            return nullptr;
        }

        if ((player.row < 0) || (player.col < 0)){ 
            return nullptr;
        }

        if ((player.row >= maxRow) || (player.col >= maxCol)){
            return nullptr;
        }

        char** mapRay;

        mapRay = createMap(maxRow, maxCol);
        
        int tracker = 0;
        
        char crTmp;

        bool isEject = false;

        for(unsigned int row = 0; row < maxRow; row++){ 

            for (unsigned int col = 0; col < maxCol; col++){

                tracker += 1;

                if ((maxRow * maxCol) < tracker){

                    deleteMap(mapRay, maxRow);
                    return nullptr;

                }

                else{
                    
                    infs >> crTmp; 
                    
                    if (crTmp == TILE_OPEN || crTmp == TILE_PLAYER || crTmp == TILE_TREASURE){
                        
                        if (crTmp == TILE_DOOR || crTmp == TILE_EXIT){

                            isEject = true;

                        }

                        mapRay[row][col] = crTmp;
                    }
                    else if (crTmp == TILE_AMULET || crTmp == TILE_MONSTER || crTmp == TILE_PILLAR){
                        
                        if (crTmp == TILE_DOOR || crTmp == TILE_EXIT){

                            isEject = true;
                            
                        }

                        mapRay[row][col] = crTmp;
                    }
                    else if (crTmp == TILE_DOOR || crTmp == TILE_EXIT){
                        
                        if (crTmp == TILE_DOOR || crTmp == TILE_EXIT){

                            isEject = true;
                            
                        }

                        mapRay[row][col] = crTmp;
                    }
                    else{

                        deleteMap(mapRay, maxRow);
                        return nullptr;

                    }
                }
            }
        }
        
        if (infs >> crTmp){
            deleteMap(mapRay, maxRow);
            return nullptr;
        }

        if (isEject == false){
            deleteMap(mapRay, maxRow);
            return nullptr;
        }
        
        mapRay[player.row][player.col] = TILE_PLAYER; 
        
        return mapRay; 

    }
    else{
        
        return nullptr;
    }

}



/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {

    if (input == MOVE_RIGHT){   
        nextCol ++;
    }else if (input == MOVE_LEFT){
        nextCol --;
    }else if (input == MOVE_UP){   
        nextRow --;
    }else if (input == MOVE_DOWN){
        nextRow ++;
    }else{
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    
    char** newMap = new char*[maxRow];

    for(unsigned int i = 0; i < maxRow; i++){
        
        newMap[i] = new char[maxCol];

        for(int j = 0; j < maxCol; j++){

            newMap[i][j] = TILE_OPEN;

        }

	}

    return newMap;
}



/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {

    for (int i = 0; i < maxRow; i++){

        delete[] map[i]; 

    }

    delete[] map;
    maxRow = 0;

    map = nullptr;
    
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {

    if (map == nullptr){
        
        return nullptr;
    }
    if (maxRow > 537000000 || maxCol > 537000000){
        return nullptr;
    }
    if ( maxCol < 1 || maxRow < 1){
        return nullptr;
    }

    char** newMap = createMap(maxRow*2, maxCol*2); 
    for (int row = 0; row < maxRow; row++){
        for (int col = 0; col < maxCol; col++){

            if (map[row][col] == TILE_PLAYER){
                newMap[row][col] = map[row][col];
                newMap[row + (maxRow)][col] = '-';
                newMap[row + (maxRow)][col + (maxCol)] = '-';
                newMap[row][col + (maxCol)] = '-';
            }
            
            else{
                newMap[row][col] = map[row][col];
                newMap[row + (maxRow)][col] = map[row][col];
                newMap[row + (maxRow)][col + (maxCol)] = map[row][col];
                newMap[row][col + (maxCol)] = map[row][col];
            }
        }
    }

    int fake  = maxRow;
    deleteMap(map, fake);
    maxRow *= 2;
    maxCol *= 2;

    return newMap;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    
    int tempRow = player.row;
    int tempCol = player.col;

    if ( nextRow >= maxRow || nextCol >= maxCol || nextRow < 0 || nextCol < 0){ 
        return STATUS_STAY;
    }

    else if ( (map[nextRow][nextCol] == '|') || (map[nextRow][nextCol] == TILE_PILLAR) || (map[nextRow][nextCol] == TILE_MONSTER) ){ 
        return STATUS_STAY;
    }

    else if( (map[nextRow][nextCol] == TILE_EXIT) && (player.treasure <= 0) ){
        return STATUS_STAY;
    }

    else{ 
        map[player.row][player.col] = TILE_OPEN; 
        player.row = nextRow; 
        player.col = nextCol;

        if (map[nextRow][nextCol] == TILE_AMULET){ 
            map[nextRow][nextCol] = TILE_PLAYER;
            return STATUS_AMULET;
            
        }
        else if(map[nextRow][nextCol] == TILE_TREASURE){ 
            map[nextRow][nextCol] = TILE_PLAYER;
            player.treasure++;
            return STATUS_TREASURE;
        }
        else if (map[nextRow][nextCol] == TILE_DOOR){ 
            map[nextRow][nextCol] = TILE_PLAYER; 
            return STATUS_LEAVE;
        }
        else if (map[nextRow][nextCol] == TILE_EXIT){ 
            if (player.treasure > 0){
                map[nextRow][nextCol] = TILE_PLAYER;
                return STATUS_ESCAPE;
            }
            else{
                
                map[tempRow][tempCol] = TILE_PLAYER; 
                return STATUS_STAY;
            }
        }
        else{ 
            map[nextRow][nextCol] = TILE_PLAYER;
            return STATUS_MOVE;
        }

    }
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    bool unpassObj = false; 
    
    for (int i = player.row - 1; i >= 0; i--){ 
        
        if (map[i][player.col] == TILE_PILLAR || map[i][player.col] == '|'){
            unpassObj = true;
            break; 
        }
        
        else if (map[i][player.col] == TILE_MONSTER){ 
            
            map[i][player.col] = TILE_OPEN;
            map[i + 1][player.col] = TILE_MONSTER; 
        }

    }

    for (int i = player.row + 1; i < maxRow; i++){ 
        if (map[i][player.col] == TILE_PILLAR || map[i][player.col] == '|'){
            unpassObj = true;
            break; 
        }

        else if (map[i][player.col] == TILE_MONSTER){ 
            
            map[i][player.col] = TILE_OPEN;
            map[i - 1][player.col] = TILE_MONSTER; 
        }
    }

    
    for (int i = player.col - 1; i >= 0; i--){ 
        if (map[player.row][i] == TILE_PILLAR || map[player.row][i] == '|'){
            unpassObj = true;
            break; 
        }


        else if (map[player.row][i] == TILE_MONSTER){ 
            
            map[player.row][i] = TILE_OPEN;
            map[player.row][i + 1] = TILE_MONSTER; 
        }
    }


    for (int i = player.col + 1; i < maxCol; i++){ 
        if (map[player.row][i] == TILE_PILLAR || map[player.row][i] == '|'){
            unpassObj = true;
            break; 
        }

        else if (map[player.row][i] == TILE_MONSTER){ 
            
            map[player.row][i] = TILE_OPEN;
            map[player.row][i - 1] = TILE_MONSTER; 

        }
    }



    if (map[player.row][player.col] == TILE_MONSTER){
        return true;
    }
    else{
        return false;
    }


}
