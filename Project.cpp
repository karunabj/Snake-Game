#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include "objPosArrayList.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
Player* myPlayer;
GameMechs* myGM;
objPosArrayList* foodBucket;
objPosArrayList* playerBody;

Food* myFood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus()  == false && myGM->getLoseFlagStatus() == false)  //checking for endgame status
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

    //allocating/initalizing required parameters
    myGM = new GameMechs(26,13);  
    foodBucket = new objPosArrayList();
    myFood = new Food(myGM, foodBucket);
    myPlayer = new Player(myGM, myFood);
    playerBody = myPlayer->getPlayerPos();

    myFood->generateFood(playerBody);   //generates food 
    
}

void GetInput(void)
{
   myGM->getInput();
}

void RunLogic(void)
{

    objPos playerPosCheck; //create an instance for temporary pos
    myPlayer->getPlayerPos(); //get the player pos  

    //player movement update logic
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();   

    if (myGM->getInput() == 27){    //setting exit key to escape
        myGM->setExitTrue();
    }   
    

    myGM->clearInput();  //clearing input 


}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    //initalizing required parameters 
    bool drawn, drawn2;
    int i,j;
    objPos tempBody;
    objPosArrayList tempFood;    //temporary geneerated array of food 
    objPos tempFoodObj;          //temporary single food objects 

    myFood->getFoodPos(tempFood);  //gets the generated foodlist 


    //printing on screen logic 

    MacUILib_printf("!!!SNAKE GAME!!!\n\n:P Menu: \n\n'O'is a classic bagel --> +1 score; +1 body\n'+'is a spicy nacho --> +5 score\n'$'is an energy drink  --> +10 score; +2 body\n\n");

    for(i=0; i<myGM->getBoardSizeY(); i++)         //drawing all elements on board 
    {
        for(j=0; j<myGM->getBoardSizeX(); j++)
        {
            drawn = false;
            //iterate thourgh every single element on the playerlist
            for(int k = 0; k < playerBody->getSize(); k++)           //drawing snakebody 
            {
                playerBody->getElement(tempBody,k);
                if(tempBody.x == j && tempBody.y == i && drawn == false)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                }
            }

            if (drawn) continue;    //if player body was drawn, don't draw anything below

            drawn2 = false;
            for (int k = 0; k < tempFood.getSize(); k++)       //drawing food on board 
            {
                tempFood.getElement(tempFoodObj,k);

                if (j == tempFoodObj.x && i == tempFoodObj.y)
                {
                    MacUILib_printf("%c", tempFoodObj.symbol);
                    drawn2 = true;

                }
            }

            if (drawn2) continue;   //if food was drawn then dont do anything below 

            if(i==0 || i== myGM->getBoardSizeY()-1 || j==0 || j== myGM->getBoardSizeX()-1)   //condition for the boarder drawing
            {
                MacUILib_printf("%c", '#');
            }        

            else
            {
                MacUILib_printf("%c",' ');
            }

        }
        
        printf("\n");

    }


    MacUILib_printf("Score: %d\n", myGM->getScore());    //writing the score 

    
    

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  

    if (myGM->getLoseFlagStatus()){
        MacUILib_printf("You died womp womp (T-T)\n\nSlay though you ate. Happiness Level: %d :0\n", myGM->getScore());
    }

    else{
        MacUILib_printf("Game exited sucessfully.");
    }
    
    delete myGM;
    delete myPlayer;  
    delete myFood;
    delete foodBucket;
  
    MacUILib_uninit();
}
