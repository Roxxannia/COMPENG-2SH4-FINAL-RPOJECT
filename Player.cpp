#include "Player.h"
#include <iostream>
#include "Food.h"
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();
    // intialize player position center of board
    objPos newPos{mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*'};
    playerPosList->insertHead(newPos);
}


Player::~Player()
{
    delete playerPosList;
}


int Player::checkFoodConsumption(objPos headPos, objPosArrayList* foodBucket)
{
    objPos foodPos;

    int score = 0;

    // bonus - check if any food consumed
    for (int i = 0; i < foodBucket->getSize(); i++)
    {
        foodBucket->getElement(foodPos, i);

        // if special food consumed, increase score by 5
        if (headPos.x == foodPos.x && headPos.y == foodPos.y && foodPos.symbol == '$')
        {
           score = 5;
           break;
            
        }
        // normal food increase scroe by 1
        else if (headPos.x == foodPos.x && headPos.y == foodPos.y && foodPos.symbol == 'o')
        {
           score = 1;
           break;
        }
    }
    return score;

}

void Player::increasePlayerLength()
{
    objPos increPos;
    playerPosList->getHeadElement(increPos);
    playerPosList->insertHead(increPos);
}

bool Player::checkSelfCollision()
{
    objPos headPos;
    objPos colliPos;

    playerPosList->getHeadElement(headPos);

    // loop through player body to check for collision
    for (int i = 1; i<playerPosList->getSize(); i++)
    {
        playerPosList->getElement(colliPos,i);
        if (headPos.x == colliPos.x && headPos.y == colliPos.y)
        {
            return true;
            
        }
    }
    return false;

}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    switch(mainGameMechsRef->getInput())
    {
        case 'w':
        case 'W':
            if(myDir != UP && myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        case 's':
        case 'S':
            if(myDir != UP && myDir != DOWN)
            {
                myDir = DOWN;
            }
            break;
        case 'a':
        case 'A':
            if(myDir != LEFT && myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;

        case 'd':
        case 'D':
            if(myDir != LEFT && myDir != RIGHT)
            {
                myDir = RIGHT;
            }
            break;

        case ' ':
            myDir = STOP;
            mainGameMechsRef->setExitTrue();
            break;

        default:
            break;
    }   
}


void Player::movePlayer(Food* foodRef)
{
    objPos currPos;
    playerPosList->getHeadElement(currPos);

    // get list of food items
    objPosArrayList* foodBucket = foodRef->getFoodBucket();

    int newY = currPos.y;
    int newX = currPos.x;

    switch ((myDir))
    {
        case UP:
            if(newY <= 1)
            {
                newY = mainGameMechsRef->getBoardSizeY()-1;
            }
            newY--;
            break;
        case DOWN:
            if(newY >= mainGameMechsRef->getBoardSizeY()-2)
            {
                newY = 0;
            }
            newY++;
            break;
        case LEFT:
            if(newX <= 1)
            {
                newX = mainGameMechsRef->getBoardSizeX()-1;
            }
            newX--;
            break;
        case RIGHT:
            if(newX >= mainGameMechsRef->getBoardSizeX()-2)
            {
                newX = 0;
            } 
            newX++;
            break;           
        case STOP:
        default:
            break;
    }

    // create new position for player
    // position updated based on its movement direction
    objPos newPos{newX,newY,'*'};
    
    //checking sellf collision event
    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }

    if (checkFoodConsumption(newPos,foodBucket) == 1)
    {
        playerPosList->insertHead(newPos); //player length increase by 1
        mainGameMechsRef->incrementScore(1);
        foodRef->generateFood(playerPosList);  // to ensure generation not on snake body --> newPos --> playerPosList

    }
    else if (checkFoodConsumption(newPos,foodBucket) == 5)
    {
        playerPosList->insertHead(newPos);
        playerPosList->removeTail(); //no player length increment
        mainGameMechsRef->incrementScore(5);
        foodRef->generateFood(playerPosList);  // to ensure generation not on snake body --> newPos --> playerPosList
    }
    else
    {
        playerPosList->insertHead(newPos);
        playerPosList->removeTail();
    }
    
}
