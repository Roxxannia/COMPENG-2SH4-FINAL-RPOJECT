#ifndef FOOD_H
#define FOOD_H
// provides srand() and rand()
#include <cstdlib> 
// provides time
#include <time.h> 

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h" 

using namespace std;

class Food
{
    private:
        objPos foodPos; 
        GameMechs* mainGameMechsRef;

        int **myFood; //heap data members

        // bonus 
        objPosArrayList* foodBucket;


    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* playerPos);
        void getFoodPos(objPos &returnPos);
        // void updateFood();

        // bonus
        objPosArrayList *getFoodBucket();
      
};


#endif