//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Martin Kubicka <xkubic45@stud.fit.vutbr.cz>
// $Date:       $2022-03-09
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Martin Kubicka
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyQueue : public ::testing::Test
{
protected:
    BinaryTree queue;
};

//testing function InsertNode on EmptyQueue
TEST_F(EmptyQueue, InsertNode) {
    ASSERT_TRUE(queue.GetRoot() == NULL);
    //inserting first value
    EXPECT_TRUE((queue.InsertNode(0)).first);
    EXPECT_FALSE((queue.InsertNode(0)).first);
    EXPECT_FALSE(queue.GetRoot() == NULL);
    //inserting second value
    EXPECT_TRUE((queue.InsertNode(-1)).first);
    EXPECT_FALSE((queue.InsertNode(-1)).first);
}

//testing function DeleteNode on EmptyQueue
TEST_F(EmptyQueue, DeleteNode) {
    //inserting first value
    ASSERT_TRUE((queue.InsertNode(0)).first);
    //deleting value
    EXPECT_TRUE(queue.DeleteNode(0));
    EXPECT_FALSE(queue.DeleteNode(0));
    //inserting second value
    ASSERT_TRUE((queue.InsertNode(-1)).first);
    //deleting value
    EXPECT_TRUE(queue.DeleteNode(-1));
}

//testing function FindNode on EmptyQueue
TEST_F(EmptyQueue, FindNode) {
    //trying to find non-existant value
    EXPECT_TRUE(queue.FindNode(0) == NULL);
    //inserting first value
    ASSERT_TRUE((queue.InsertNode(0)).first);
    EXPECT_TRUE(queue.FindNode(0) != NULL);
    //expecting that find node key value will be 0
    EXPECT_TRUE((queue.FindNode(0))->key == 0);
    //inserting second value
    ASSERT_TRUE((queue.InsertNode(-1)).first);
    EXPECT_TRUE(queue.FindNode(-1) != NULL);
    //expecting that find node key value will be -1
    EXPECT_TRUE((queue.FindNode(-1))->key == -1);
}

class NonEmptyQueue : public ::testing::Test
{
protected:
    //inserting values
    virtual void SetUp() {
        int addedValues[] = {2, 0, 4, 8, 12, 10, 22, 14};

        for(int i = 0; i < 8; i++) {
            queue.InsertNode(addedValues[i]);
        }
    }
    BinaryTree queue;
};

//testing InsertNode on NonEmptyQueue
TEST_F(NonEmptyQueue, InsertNode) {
    ASSERT_TRUE(queue.GetRoot() != NULL);
    //inserting value which is already in tree
    EXPECT_FALSE((queue.InsertNode(0)).first);
    //inserting value which is not in tree
    EXPECT_TRUE((queue.InsertNode(1)).first);
    //inserting second value which is not in tree
    EXPECT_TRUE((queue.InsertNode(-1)).first);
}

//testing DeleteNode on NonEmptyQueue
TEST_F(NonEmptyQueue, DeleteNode) {
    //deleting value which is in tree
    EXPECT_TRUE(queue.DeleteNode(0));
    //deteting value which is not in tree
    EXPECT_FALSE(queue.DeleteNode(0));
    //deleting value which is in tree
    EXPECT_TRUE(queue.DeleteNode(4));
    //inserting value which is not in tree
    EXPECT_TRUE((queue.InsertNode(-1)).first);
    //deleting inserted value
    EXPECT_TRUE(queue.DeleteNode(-1));

}

//testing FindNode on NonEmptyQueue
TEST_F(NonEmptyQueue, FindNode) {
    //trying to find value which is not in tree
    EXPECT_TRUE(queue.FindNode(1) == NULL);
    //trying to find number which is in tree
    EXPECT_FALSE(queue.FindNode(12) == NULL);
    EXPECT_TRUE(queue.DeleteNode(12));
    //trying to find deleted number from tree
    EXPECT_TRUE(queue.FindNode(12) == NULL);
    EXPECT_TRUE((queue.InsertNode(-1)).first);
    //trying to find inserted value
    EXPECT_FALSE(queue.FindNode(-1) == NULL);
}

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int addedValues[] = {2, 1, 5};

        for(int i = 0; i < 3; i++) {
            queue.InsertNode(addedValues[i]);
        }
    }
    
    BinaryTree queue; 
};

//testing first axiom
TEST_F(TreeAxioms, Axiom1) {
    std::vector<Node_t *> outLeafNodes = {};
    //getting leaf nodes
    queue.GetLeafNodes(outLeafNodes);
    for (int i = 0; i < outLeafNodes.size(); i++) {
        //expecting that all leaf nodes are black
        EXPECT_EQ((outLeafNodes[i])->color, 1);
    }
}

//testing second axiom
TEST_F(TreeAxioms, Axiom2) {
    std::vector<Node_t *> outNonLeafNodes = {};
    //getting non-leaf nodes
    queue.GetNonLeafNodes(outNonLeafNodes);
    for (int i = 0; i < outNonLeafNodes.size(); i++) {
        if (outNonLeafNodes[i]->color == 0) {
            //expecting if node color is red then node children are black
            EXPECT_EQ(outNonLeafNodes[i]->pLeft->color, 1);
            EXPECT_EQ(outNonLeafNodes[i]->pRight->color, 1);
        }
    }
}

//testing third axiom
TEST_F(TreeAxioms, Axiom3) {
    std::vector<Node_t *> outLeafNodes = {};
    //getting leaf nodes
    queue.GetLeafNodes(outLeafNodes);
    //creating array for counting
    int count[] = {0, 0, 0, 0};
    for (int i = 0; i < outLeafNodes.size(); i++) {
        Node_t *tmp = (outLeafNodes[i])->pParent;
        while (tmp->pParent != NULL) {
            if (tmp->color == 1) {
                //counting black nodes
                count[i] = count[i] + 1;
            }
            tmp = tmp->pParent;
        } 
        //expecting that there are same amout of black nodes on all ways to the parent
        EXPECT_EQ(count[i], count[0]);
    }
}

/*** Konec souboru black_box_tests.cpp ***/
