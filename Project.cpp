#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "Food.h"
#include <time.h>

using namespace std;

#define DELAY_CONST 100000

//Global scope
GameMechs* myGM;
Player* myPlayer;
Food* myFood;
// objPosArrayList* playerPosition;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{
    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // making board size
    myGM = new GameMechs(DIMX, DIMY); 
    myPlayer = new Player(myGM);

    // food generation
    myFood = new Food(myGM);

    // objPos playPos;
    // objPos foodPos;
    // myPlayer->getPlayerPos();
    //bonus fixing
    // myFood->generateFood(playPos);
    myFood->generateFood(myPlayer->getPlayerPos());

}

void GetInput(void)
{
    
}

void RunLogic(void)
{   
    // temp variable to store food position
    // previous iteration
    // objPos tempFood;
    // myFood->getFoodPos(tempFood);

    // update players dir and move player
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(myFood);
    
    // clear input to avoid repeated processing
    myGM->clearInput(); 

}

void DrawScreen(void)
{
    MacUILib_clearScreen();   
    
    objPosArrayList* myPlayerList = myPlayer->getPlayerPos();
    objPosArrayList* foodBucket = myFood->getFoodBucket();

    objPos headPos;
    myPlayerList->getHeadElement(headPos);


    objPos bodyPos;

    // dimy is rows; dimx is columns
    for (int i = 0; i < myGM->getBoardSizeY(); i++) // rows
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++) // columns
        {
            // print player
            bool snakePrint = true;
            for (int k = 0; k < myPlayerList->getSize(); k++)
            {
                myPlayerList->getElement(bodyPos,k);
                if (bodyPos.y == i && bodyPos.x == j)
                {
                    MacUILib_printf("%c", bodyPos.symbol);
                    snakePrint = false; // havent finished printing
                    break;
                }
            }

            if(!snakePrint)
                continue;
            

            // print food
            bool foodPrint = true;
            for (int k = 0; k < foodBucket->getSize(); k++)
            {
                foodBucket->getElement(bodyPos, k);
                if (bodyPos.y == i && bodyPos.x == j)
                {
                    MacUILib_printf("%c", bodyPos.symbol);
                    foodPrint = false;
                    break;
                }
            }

            if (!foodPrint)
                continue;

            // print boarder
            if (i == 0 || i == myGM->getBoardSizeY() - 1 ||j == 0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');

            }
            else
            {
                MacUILib_printf("%c", ' ');
            }

        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Player Score: %d\n", myGM->getScore());
    MacUILib_printf("Snake Length: %d\n", myPlayerList->getSize());
    MacUILib_printf("Press spacebar to exit the game!\n");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    
    // if player self collided
    if(myGM->getLoseFlagStatus() == true)
    {
        MacUILib_clearScreen(); 
        MacUILib_printf("You have consumed yourself :( it's a suicide");
        MacUILib_uninit();
    }
    // if player ends game voluntarily
    else if (myGM->getLoseFlagStatus() == false)
    {
        MacUILib_printf("Your final score is %d", myGM->getScore());
        MacUILib_uninit();
    }
  
}
