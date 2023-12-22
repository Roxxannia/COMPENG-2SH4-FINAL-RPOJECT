#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
    aList = new objPos[sizeArray];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList; // original was return sizeArray;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // check if space available for head insertion
    if (sizeList < sizeArray) {
        for (int i = sizeList; i > 0; i--)
        {
            // shift elements down to tail
            aList[i] = aList[i - 1];
        }
        // inserting new head
        aList[0] = thisPos;
        // size of list now increased
        sizeList++;

    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // check if space available for tail insertion
    if (sizeList < sizeArray)
    {
        // inserting new tail
        aList[sizeList] = thisPos;

        // increase size of list
        sizeList++;
    }
}

void objPosArrayList::removeHead()
{
    // check if list empty
    if (sizeList > 0)
    {
        // shuffle all elements towards head
        for (int i = 0; i < sizeList - 1; i++)
        {
            aList[i] = aList[i + 1];
        }
        // decrease size of list
        sizeList--;
    }
}

void objPosArrayList::removeTail()
{
    // check if list empty
    if (sizeList > 0)
    {
        // removing last element/decrease size of list
        sizeList--;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    // get element sat the target index
    // head -> index = 0
    // tail -> index = sizeList - 1
    // anywhere else - just use input index 
    // use pass-by-reference to return values

    // check if list is not empty
    if (sizeList > 0)
    {   
        // get head element
        returnPos = aList[0];
    }
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    // // check if list is not empty
    if (sizeList > 0) 
    {
        // get tail element
        returnPos = aList[sizeList - 1];
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    // check if index within range 
    // if (index >= 0 && index < sizeList) 
    {
        // get the element
        returnPos = aList[index];
    }
}