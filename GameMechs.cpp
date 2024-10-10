#include "GameMechs.h"
#include <MacUILib.h>

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;   
    score = 0;          
    boardSizeX = 20;    
    boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;   
    score = 0;          
    boardSizeX = boardX; 
    boardSizeY = boardY;
}



GameMechs::~GameMechs(){

}


bool GameMechs::getExitFlagStatus()
{
     return exitFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar() !=0)
    {
        input = MacUILib_getChar();  // last typed value stored

    }
    return input;
}
//added
bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


int GameMechs::getScore()
{
    return score;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}


void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::incrementScore(){
    score++;
}

void GameMechs::incrementScoreBonus1()
{
    score += 5;
}

void GameMechs::incrementScoreBonus2()
{
    score += 10;
}
