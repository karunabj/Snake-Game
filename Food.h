#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

class Food: public objPosArrayList
{
    private:
        int bucketSize = 5;
        GameMechs* mainGMrefFood;
        objPosArrayList* foodBucket;
        

    public:
        Food(GameMechs* foodGM, objPosArrayList* foods);
        ~Food();

        void generateFood(objPosArrayList* objList);    
        void getFoodPos(objPosArrayList &returnPos);
        int getBucketSize();
};

#endif