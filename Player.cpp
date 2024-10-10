#include "Player.h"
#include "Food.h"
#include <iostream>


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    mainFood = thisFoodRef;

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*'); //sets inital position
    
    playerPosList = new objPosArrayList();  
    playerPosList->insertHead(tempPos);    //sets the first head 
    
}


Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    //Get's keyboard input
    char input = mainGameMechsRef->getInput();
    // PPA3 input processing logic
    switch(input)
    {
        case 'w':  // UP keypress 
                if (myDir != DOWN)
                { 
                    myDir = UP;
                }
                break;
            
        case 's':  // DOWN keypress 
            if (myDir != UP)
            { 
                myDir = DOWN;
            }
            break;
        
        case 'd':  // RIGHT keypress 
            if (myDir != LEFT)
            { 
                myDir = RIGHT;
            }
            break;
        
        case 'a':  // LEFT keypress 
            if (myDir != RIGHT)
            { 
                myDir = LEFT;
            }
            break;

        default:
            break;

    }
            
}

bool Player::checkFoodConsumption(objPos &head, objPos &cfood)
{
    bool flag = false;
    objPosArrayList foodlocations; //holds position of food locations
    objPos foodLoc;                 //holds position of a single food object
    mainFood->getFoodPos(foodlocations); //geting the info of generated food on gameboard  

    for(int i = 0; i < foodlocations.getSize(); i++)  //loop for checking if the head of snake collides with a food item
    {
        foodlocations.getElement(foodLoc, i);
        if (foodLoc.x == head.x && foodLoc.y == head.y)     //checks collison 
        {
            flag = true; 
            cfood.symbol = foodLoc.symbol;   //appends the correct food symbol 
        }
    }
    
    return flag;

}


void Player::increasePlayerLength(objPos head)
{
    playerPosList->insertHead(head);   //inserts head 
}

bool Player::checkSelfCollision(objPos head)
{
    bool flag = false;
    objPos temp;      //holds temporary position of elements in playerPosList

    for (int i = 0; i < playerPosList->getSize() && mainGameMechsRef->getScore() != 0; i++)   //loops through snake body elements to check if collison
    {
        playerPosList->getElement(temp, i);
        if (head.isPosEqual(&temp))           //collision condition to exit game 
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            flag = true;
        }
        
    }
    return flag;
}

void Player::movePlayer()
{
    objPos currHead; //holds current head info
    playerPosList->getHeadElement(currHead);
    objPos cfood; //holds colllied food info 

    //collects the boundary values of the game board
    int xbound = (mainGameMechsRef->getBoardSizeX()-2);
    int ybound = (mainGameMechsRef->getBoardSizeY()-2);
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
        case UP:
            currHead.y -= 1;
            if (currHead.y < 1)
            {
                currHead.y = ybound;
            }
            break;

        case DOWN:
            currHead.y += 1;
            if (currHead.y > ybound)
            {
                currHead.y = 1;
            }
            break;

        case RIGHT:
            currHead.x += 1;
            if (currHead.x > xbound)
            {
                currHead.x = 1;
            }
            break;
        
        case LEFT:
            currHead.x -= 1;
            if (currHead.x < 1)
            {
                currHead.x = xbound;
            }
            break;  
        
        case STOP:
        default:
            break;
    }

    
    if (checkSelfCollision(currHead) == false)
    {
        increasePlayerLength(currHead);     //inserts head only 
        if (checkFoodConsumption(currHead, cfood))         //checks food consumption 
        {  
            if (cfood.symbol == '+')                       //condition for bonus spicy nacho  
            {
                mainGameMechsRef->incrementScoreBonus1();  //increases score by 5
        
            }
            else if (cfood.symbol == '$')                  //condition for bonus energy drink 
            { 
                mainGameMechsRef->incrementScoreBonus2();  //increases score by 10
                playerPosList->insertTail(currHead);       //increments the length of snake by 2 instead of 1              
                
            }
            else 
            {
                mainGameMechsRef->incrementScore();         //default increase score by 1
            }
            mainFood->generateFood(playerPosList);         //generates new food
        }
        else
        {
            playerPosList->removeTail();         //removes the tail
        }
    }

    

}


