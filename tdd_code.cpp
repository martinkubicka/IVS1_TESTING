//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Martin Kubicka <xkubic45@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Kubicka
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find/GetHead ...
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "singly linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

//creating queue and setting head to NULL
PriorityQueue::PriorityQueue()
{
    m_pHead = NULL;
}

//deleting queue
PriorityQueue::~PriorityQueue()
{
    //counting number of items
    int count = 0;
    for (Element_t *tmp = m_pHead; tmp != NULL; tmp = tmp->pNext) {
        count++;
    }
    
    //deleting items and changing pointers
    Element_t *previousItem = m_pHead;
    for (int i = 0; i < count; i++) {
        for (Element_t *tmp = m_pHead; tmp != NULL; tmp = tmp->pNext) { 
            m_pHead = tmp->pNext; 
            delete tmp;
            break;
        }
    }
}

//inserting values - bigger number will be before smaller number
void PriorityQueue::Insert(int value)
{
    //creating new node
    Element_t *node = new Element_t;
    //setting new node
    node->pNext = NULL;
    node->value = value;

    //if there are no other nodes
    if (m_pHead == NULL) {
        m_pHead = node;
    } else {
        Element_t *tmp = m_pHead;
        Element_t *previousItem = m_pHead;
        //counting if node was inserted
        int isSet = 0;
        //inserting on first position
        if (m_pHead->value < value) {
            node->pNext = m_pHead;
            m_pHead = node;
            isSet = 1;
        //inserting on position somewhere in the middle
        } else {
            while (tmp->pNext != NULL) {
                if (tmp->value < value) {
                    node->pNext = previousItem->pNext;
                    previousItem->pNext = node;
                    isSet = 1;
                    break;
                } else {
                    previousItem = tmp;
                    tmp = tmp->pNext;
                }
            }
        }
        //if node wasnt inserted, it will be inserted at the end
        if (!isSet) {
            if (tmp->value < value) {
                node->pNext = tmp;
                previousItem->pNext = node;
            } else {
                tmp->pNext = node;
            }
        }
    }
}

//removing item
bool PriorityQueue::Remove(int value)
{
    Element_t *previousItem = m_pHead;
    int count = 0;
    for (Element_t *tmp = m_pHead; tmp != NULL; tmp = tmp->pNext) {
        count++;
        if (tmp->value == value) {
            //removing first item
            if (count == 1){
                m_pHead = tmp->pNext;
            //removing not first item
            } else {
                previousItem->pNext = tmp->pNext;
            }
            delete tmp;
            return true;
        } 
        previousItem = tmp;
    }
    return false;
}

//finding value
PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    for (Element_t *tmp = m_pHead; tmp != NULL; tmp = tmp->pNext) {
        //if value was found -> returning pointer to the node with the value
        if (tmp->value == value) {
            return tmp;
        }
    }
    //value wasnt found -> returning NULL
    return NULL;
}

//getting lenght
size_t PriorityQueue::Length()
{
    int count = 0;
    for (Element_t *tmp = m_pHead; tmp != NULL; tmp = tmp->pNext) {
        count++;
    }
    return count;
}

//geting head of queue
PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
