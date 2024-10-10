#include "Food.h"
#include <time.h>
#include <stdio.h>
#include "MacUILib.h"


Food::Food(GameMechs* foodGM, objPosArrayList* foods)
{
    srand(time(NULL));
    
    mainGMrefFood = foodGM;
    foodBucket = foods;
    
}

Food::~Food()
{
    
}

void Food::generateFood(objPosArrayList* objList)   //passing the player array
{
    int i;
    int special_count1 = 0, special_count2 = 0; //counts for the special foods
    
    
    for(int clear = 0; clear < bucketSize; clear++)      //clearing the foodbucket before regeneration 
    {
        foodBucket->removeTail();
    }
    
    
    int vectorx[mainGMrefFood->getBoardSizeX()-2] = {0};    //bit vector look up table for non repeating x coordinates
    int vectory[mainGMrefFood->getBoardSizeY()-2] = {0};    //bit vector look up table for non repeating y coordinates

    
    
    for(int count = 0; count < bucketSize; count++)
    {
        bool flag = 1;
        objPos Pos;          //holds player info
        objPos foodObj;      //holds food info
        int xcandidate, ycandidate;

        xcandidate = (rand()% (mainGMrefFood->getBoardSizeX()-2)) + 1;
                                                            //rand num % 18 giving [0,17], however 0 is the border so +1 to the candidate for coords
                                                            // THEREFORE item x range is [1,...,18] and the borders are 0 and 19

        ycandidate = (rand()% (mainGMrefFood->getBoardSizeY()-2)) + 1;    //mainGMrefFood->getBoardSizeY() 
                                                            //rand num %8 giving [0,7], add 1 to get all y.coords in between border
                                                            // THEREFORE item y range is [1,...,8] and the borders are 0 and 9
        while (flag)      //only exits when the generated position is for sure not a snakebody element
        {
            flag = 0;
            for (i = 0; i < objList->getSize(); i++)     //loop for checking if the generated position is alligned with any snakebody element
            {
                objList->getElement(Pos, i);
                if ((Pos.x == xcandidate && Pos.y == ycandidate) || (vectorx[xcandidate-1] == 1 && vectory[ycandidate-1] == 1))     //if equal to a snake body element regenerate the positon
                {
                    xcandidate = (rand()% (mainGMrefFood->getBoardSizeX()-2)) + 1;
                    ycandidate = (rand()% (mainGMrefFood->getBoardSizeY()-2)) + 1;
                    flag = 1;
                }
            }
            
        }
        if (flag == 0)         //once confirmed set the food object
        {
            if (special_count1 < 1)      //creates 1 special spicy nacho food
            {
                foodObj.setObjPos(xcandidate, ycandidate, '+');
                special_count1++;
            }
            else if (special_count2 < 1)   //creates 1 special energy drink
            {
               foodObj.setObjPos(xcandidate, ycandidate, '$'); 
               special_count2++;
            }
            else                           //creates default bagel 
            {
                foodObj.setObjPos(xcandidate, ycandidate, 'O');
            }
            foodBucket->insertTail(foodObj);  
            vectorx[xcandidate-1]++;
            vectory[ycandidate-1]++;
        }
    }
    
}



void Food::getFoodPos(objPosArrayList &returnPos)    
{
    objPos food;
    int i = 0;
    for (i = 0; i < bucketSize; i++){          
        foodBucket->getElement(food, i);    
        returnPos.insertTail(food);
    }
}

int Food::getBucketSize(){
    return bucketSize;
}