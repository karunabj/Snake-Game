#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; //creates 200 elements 
    sizeArray = ARRAY_MAX_CAP;
    sizeList = 0; //no elements in list at the start 
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (sizeList < sizeArray)
    {
        //shifts alll elements towards the tail to open a spot at the head
        for (int i = sizeList; i > 0; i--)
        {
            aList[i].setObjPos(aList[i-1]);
        }
        //fills the head spot with the new element
        aList[0].setObjPos(thisPos);
        //incremnt the size of list
        sizeList++;
    }

}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList < sizeArray)
    {
        //fills the tail spot with the new element
        aList[sizeList].setObjPos(thisPos);
        //increment the size of list
        sizeList++;
    }
}

void objPosArrayList::removeHead()
{
    if (sizeList > 0) //make sure theres at least 1 element in the list to remove
    {
        //shifts all elements towards the head to remove a spot at the head
        for (int i = 0; i < sizeList; i++)
        {
            aList[i].setObjPos(aList[i+1]);  
        }
        //decrement the size of list
        sizeList--;
    }
    
    
}

void objPosArrayList::removeTail()
{
    //hi 2
    if (sizeList > 0) //make sure theres at least 1 element in the list to remove
    {
        //decremnt the size of list
        sizeList--;
    }
    
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}

