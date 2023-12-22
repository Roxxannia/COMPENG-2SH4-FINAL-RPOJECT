#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    public:
        // direction states
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};

        Player(GameMechs* thisGMRef);
        ~Player();
        objPosArrayList* getPlayerPos();
        
        void updatePlayerDir();
        void movePlayer(Food* foodRef);
        
        int checkFoodConsumption(objPos headPos, objPosArrayList* foodBucket);
        void increasePlayerLength();
        bool checkSelfCollision();


    private:
        enum Dir myDir;
        GameMechs* mainGameMechsRef;
        objPosArrayList* playerPosList;
};

#endif