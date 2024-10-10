#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef,  Food* thisFoodRef);
        ~Player();

        objPosArrayList* getPlayerPos(); 
        void updatePlayerDir();
        void movePlayer();
        bool checkFoodConsumption(objPos &head, objPos &cfood);
        void increasePlayerLength(objPos head);
        bool checkSelfCollision(objPos head); 
    

    private:
        objPosArrayList *playerPosList;        
        enum Dir myDir;
        //refrence to food item 
        Food* mainFood;

        //reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif