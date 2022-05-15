//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Martin Kubicka <xkubic45@stud.fit.vutbr.cz>
// $Date:       $2022-03-09
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Martin Kubicka
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class matrixTestClass : public ::testing::Test
{
protected:
    Matrix matrix;

    //function for creating matrix[x][y]
    void createMatrix(int x, int y) {
        matrix = Matrix(x, y);
    }

    //function for checking if values are correct
    void checkSet(int x, int y, std::vector<std::vector<double>> values) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                EXPECT_EQ(matrix.get(i, j), values[i][j]);
            }
        }
    }
};

//test for creating matrix[1][1] and getting values
TEST_F(matrixTestClass, Matrix1x1) {
    EXPECT_NO_THROW(matrix = Matrix());
    EXPECT_EQ(matrix.get(0, 0), 0);
    //getting value outside of matrix
    EXPECT_ANY_THROW(matrix.get(1, 1));
}

//test for creating bigger matrix and getting values
TEST_F(matrixTestClass, biggerMatrix) {
    //creating incorrect matrix
    EXPECT_ANY_THROW(matrix = Matrix(0, 0));
    EXPECT_NO_THROW(matrix = Matrix(5, 4));
    EXPECT_EQ(matrix.get(2, 3), 0);
    EXPECT_ANY_THROW(matrix.get(4, 5));
}

//test for setting values
TEST_F(matrixTestClass, setValue) {
    EXPECT_NO_THROW(matrix = Matrix(2, 3));
    //setting value outside of matrix
    EXPECT_FALSE(matrix.set(4, 2, 4));
    EXPECT_TRUE(matrix.set(1, 2, 4));
}

//test for setting all values at once
TEST_F(matrixTestClass, setValuesArray) {
    //values which should throw error
    std::vector<std::vector<double>> falseReturnValues = {{1, -5, 3, 5, 4}, 
                                                        {8, 10, 15, 222, 854}};
    std::vector<std::vector<double>> trueReturnValues = {{2, -3}, 
                                                        {22, 145}, 
                                                        {65, 19}, 
                                                        {-675, 7}};
    //testing 4x2 matrix
    EXPECT_NO_THROW(matrix = Matrix(4, 2));
    //setting values outside of matrix
    EXPECT_FALSE(matrix.set(falseReturnValues));
    EXPECT_TRUE(matrix.set(trueReturnValues));
    checkSet(4, 2, trueReturnValues);
    
    //testing 1x1 matrix
    trueReturnValues = {{1}};
    EXPECT_NO_THROW(matrix = Matrix(1, 1));
    EXPECT_TRUE(matrix.set(trueReturnValues));
    checkSet(1, 1, trueReturnValues);

    //testing 4x4 square matrix
    trueReturnValues = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}};
    EXPECT_NO_THROW(matrix = Matrix(4, 4));
    EXPECT_TRUE(matrix.set(trueReturnValues));
    checkSet(4, 4, trueReturnValues);
}

//test for testing equality of two matrixes
TEST_F(matrixTestClass, testOperatorEqual) {
    //testing 3x2 matrix
    createMatrix(3, 2);
    //equality of 2 matrixes with different size
    EXPECT_ANY_THROW(matrix.operator==(Matrix(2, 3)));

    Matrix m = Matrix(3, 2);
    std::vector<std::vector<double>> values = {{2, -3}, 
                                                {22, 145},  
                                                {-675, 7}};
    EXPECT_TRUE(matrix.operator==(m));
    EXPECT_TRUE(m.set(values));
    EXPECT_FALSE(matrix.operator==(m));

    //testing 4x4 square matrix
    createMatrix(4, 4);
    m = Matrix(4, 4);
    values = {{1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}};
    EXPECT_TRUE(matrix.set(values));
    EXPECT_TRUE(m.set(values));
    EXPECT_TRUE(matrix.operator==(m));

    //testing 1x1 matrix
    createMatrix(1, 1);
    m = Matrix(1, 1);
    values = {{1}};
    EXPECT_TRUE(matrix.set(values));
    EXPECT_TRUE(m.set(values));
    EXPECT_TRUE(matrix.operator==(m));
    
}

//test for testing operator + between 2 matrixes
TEST_F(matrixTestClass, operatorPlus) {
    //creating 3x2 matrix
    createMatrix(3, 2);
    //testing operator + between two matrixes with different size
    EXPECT_ANY_THROW(matrix.operator+(Matrix(2, 3)));

    std::vector<std::vector<double>> valuesLocalMatrix = {{1, -8}, 
                                                        {12, 145},  
                                                        {-5, 225}};
    std::vector<std::vector<double>> valuesObjectMatrix = {{-29, 2}, 
                                                        {35, 15},  
                                                        {-5, 5}};
    std::vector<std::vector<double>> correctValues = {{-28, -6}, 
                                                    {47, 160},  
                                                    {-10, 230}};                                                 

    Matrix m = Matrix(3, 2);
    Matrix correctMatrix = Matrix(3, 2);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_TRUE(matrix.set(valuesObjectMatrix));
    EXPECT_TRUE(m.set(valuesLocalMatrix));
    EXPECT_TRUE(matrix.operator+(m) == correctMatrix);

    //testing 1x1 matrix
    createMatrix(1, 1);
    valuesLocalMatrix = {{1}};
    valuesObjectMatrix = {{-4}};
    correctValues = {{-3}};                                                 
    m = Matrix(1, 1);
    correctMatrix = Matrix(1, 1);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_TRUE(matrix.set(valuesObjectMatrix));
    EXPECT_TRUE(m.set(valuesLocalMatrix));
    EXPECT_TRUE(matrix.operator+(m) == correctMatrix);

    //testing 4x4 matrix
    createMatrix(4, 4);
    valuesLocalMatrix = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}};
    valuesObjectMatrix = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}};
    correctValues = {{2, 4, 6, 8},
                    {10, 12, 14, 16},
                    {18, 20, 22, 24},
                    {26, 28, 30, 32}};                                                 
    m = Matrix(4, 4);
    correctMatrix = Matrix(4, 4);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_TRUE(matrix.set(valuesObjectMatrix));
    EXPECT_TRUE(m.set(valuesLocalMatrix));
    EXPECT_TRUE(matrix.operator+(m) == correctMatrix);
}

//test for testing operator * between two matrixes
TEST_F(matrixTestClass, operatorMultiplyByMatrix) {
    //testing 3x4 matrix
    createMatrix(3, 4);
    Matrix m = Matrix(3, 2);
    //testing operator * between two matrixes with incorrect sizes 
    EXPECT_ANY_THROW(matrix.operator*(m));
    m = Matrix(4, 2);

    std::vector<std::vector<double>> valuesClassMatrix = {{12, -8, 12, 10}, 
                                                        {38, 5, -2, 124},  
                                                        {0, 1, 0, 0}};
    
    std::vector<std::vector<double>> valuesLocalMatrix = {{3, -28}, 
                                                        {86, 45},  
                                                        {0, 21}, 
                                                        {5, -3}};
    std::vector<std::vector<double>> correctValues = {{-602, -474},
                                                    {1164, -1253},
                                                    {86, 45}};                                                
    matrix.set(valuesClassMatrix);
    m.set(valuesLocalMatrix);
    Matrix correctMatrix = Matrix(3, 2);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_TRUE(matrix.operator*(m) == correctMatrix);
    
    //testing 1x1 matrix
    createMatrix(1, 1);
    m = Matrix(1, 1);
    valuesClassMatrix = {{1}};    
    valuesLocalMatrix = {{5}};
    correctValues = {{5}};                                                
    matrix.set(valuesClassMatrix);
    m.set(valuesLocalMatrix);
    correctMatrix = Matrix(1, 1);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_TRUE(matrix.operator*(m) == correctMatrix); 

    //testing 4x4 matrix
    createMatrix(4, 4);
    m = Matrix(4, 4);
    valuesClassMatrix = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}};   
    valuesLocalMatrix = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}};
    correctValues = {{90, 100, 110, 120},
                    {202, 228, 254, 280},
                    {314, 356, 398, 440},
                    {426, 484, 542, 600}};                                                
    matrix.set(valuesClassMatrix);
    m.set(valuesLocalMatrix);
    correctMatrix = Matrix(4, 4);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_TRUE(matrix.operator*(m) == correctMatrix);
}

//testing operator * between matrix and number
TEST_F(matrixTestClass, operatorMultiplyByNumber) {
    //testing 3x2 matrix
    createMatrix(3, 2);
    int operand = -2;
    std::vector<std::vector<double>> values = {{3, -28}, 
                                                {86, 45},  
                                                {0, 21}};
    std::vector<std::vector<double>> correctValues = {{-6, 56}, 
                                                    {-172, -90},  
                                                    {0, -42}};
    matrix.set(values);
    Matrix correctMatrix = Matrix(3, 2);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_EQ(matrix.operator*(operand), correctMatrix);
    
    //testing 1x1 matrix
    createMatrix(1, 1);
    operand = 0;
    values = {{25}};
    correctValues = {{0}};
    matrix.set(values);
    correctMatrix = Matrix(1, 1);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_EQ(matrix.operator*(operand), correctMatrix);

    //testing 4x4 matrix
    createMatrix(4, 4);
    operand = 1;
    values = {{90, 100, 110, 120},
            {202, 228, 254, 280},
            {314, 356, 398, 440},
            {426, 484, 542, 600}}; 
    correctValues = values;
    matrix.set(values);
    correctMatrix = Matrix(4, 4);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_EQ(matrix.operator*(operand), correctMatrix);
}

//testing solving equation
TEST_F(matrixTestClass, solveEquation) {
    std::vector<double> values = {-1, 0};
    createMatrix(3, 2);
    //incorrect size of matrix with number of values after =
    EXPECT_ANY_THROW(matrix.solveEquation(values));
    
    values = {5, 16, 10};
    //matrix not set
    EXPECT_ANY_THROW(matrix.solveEquation(values));
    
    //testing square matrix 3x3
    int xySize = 3;
    createMatrix(xySize, xySize);
    //matrix not set
    EXPECT_ANY_THROW(matrix.solveEquation(values));

    std::vector<std::vector<double>> matrixValues = {{2, 1, 0}, 
                                                {1, 0, 3},  
                                                {0, 5, -1}};
    EXPECT_TRUE(matrix.set(matrixValues));

    std::vector<double> result = matrix.solveEquation(values);
    std::vector<double> wantedResult = {1, 3, 5};

    EXPECT_TRUE(result == wantedResult);

    //testing 1x1 matrix
    xySize = 1;
    createMatrix(xySize, xySize);
    values = {3};
    matrixValues = {{1}};
    EXPECT_TRUE(matrix.set(matrixValues));

    result = matrix.solveEquation(values);
    wantedResult = {3};

    EXPECT_TRUE(result == wantedResult);

    //testing 4x4 square matrix
    xySize = 4;
    createMatrix(xySize, xySize);
    values = {10, 4, 2, 0};
    matrixValues = {{1, 1, 1, 1}, 
                    {1, 1, -1, -1},  
                    {1, -1, 1, -1},
                    {1, -1, -1, 1}};
    EXPECT_TRUE(matrix.set(matrixValues));

    result = matrix.solveEquation(values);
    wantedResult = {4, 3, 2, 1};

    EXPECT_TRUE(result == wantedResult);
}

//tesing transpose of matrix
TEST_F(matrixTestClass, transpose) {
    //testing 5x2 matrix
    createMatrix(5, 2);
    std::vector<std::vector<double>> values = {{12, -8}, 
                                                {38, 5},  
                                                {0, 1},
                                                {2, 1},
                                                {12, 987}};

    std::vector<std::vector<double>> correctValues = {{12, 38, 0, 2, 12}, 
                                                    {-8, 5, 1, 1, 987}};
    matrix.set(values);
    Matrix correctMatrix = Matrix(2, 5);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_TRUE(matrix.transpose() == correctMatrix);

    //testing 1x1 matrix
    createMatrix(1, 1);
    values = {{15}};

    correctValues = {{15}};
    matrix.set(values);
    correctMatrix = Matrix(1, 1);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_TRUE(matrix.transpose() == correctMatrix);

    //testing 4x4 square matrix
    createMatrix(4, 4);
    values = {{1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}}; 

    correctValues = {{1, 5, 9, 13},
                    {2, 6, 10, 14},
                    {3, 7, 11, 15},
                    {4, 8, 12, 16}}; 
    matrix.set(values);
    correctMatrix = Matrix(4, 4);
    EXPECT_TRUE(correctMatrix.set(correctValues));
    EXPECT_TRUE(matrix.transpose() == correctMatrix);
}

//testing inverse of matrix
TEST_F(matrixTestClass, inverse) {
    //matrix size can be 2x2 or 3x3
    createMatrix(1, 1);
    EXPECT_ANY_THROW(matrix.inverse());
    
    createMatrix(4, 4);
    EXPECT_ANY_THROW(matrix.inverse());
    
    createMatrix(2, 3);
    EXPECT_ANY_THROW(matrix.inverse());

    //determinant == 0
    createMatrix(3, 3);
    EXPECT_ANY_THROW(matrix.inverse());

    //testing 2x2 matrix
    createMatrix(2, 2);
    std::vector<std::vector<double>> values = {{12, -8}, 
                                                {38, 5}};

    Matrix identityMatrix = Matrix(2, 2);
    std::vector<std::vector<double>> identityValues = {{1, 0},
                                                        {0, 1}};

    EXPECT_TRUE(matrix.set(values));
    EXPECT_TRUE(identityMatrix.set(identityValues));
    EXPECT_TRUE(matrix.operator*(matrix.inverse()) == identityMatrix);

    //testing 3x3 matrix
    createMatrix(3, 3);
    values = {{1, 2, 3}, 
            {4, 5, 6},  
            {7, 8, 9}};
    EXPECT_TRUE(matrix.set(values));
    //determinat == 0
    EXPECT_ANY_THROW(matrix.inverse());
    values = {{1, 4, 5}, 
            {0, 3, 0},  
            {2, 8, 9}};

    identityMatrix = Matrix(3, 3);
    identityValues = {{1, 0, 0},
                    {0, 1, 0},
                    {0, 0, 1}};

    EXPECT_TRUE(matrix.set(values));
    EXPECT_TRUE(identityMatrix.set(identityValues));
    EXPECT_TRUE(matrix.operator*(matrix.inverse()) == identityMatrix);
}
/*** Konec souboru white_box_tests.cpp ***/
