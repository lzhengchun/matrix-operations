/*
 *  matrix.hpp
 *
 *
 *  matrix.hpp contains the code that realize some common used matrix operations
 *  
 *  how to use: include this file in your code, details please check the test 
 *  file which contains demo for all the realized functions
 */
#include <iostream>
#include <stdio.h>     
#include <stdlib.h>     

#ifndef MATRIX_HPP_
#define MATRIX_HPP_
using namespace std;

template <class type> class matrix;

template <class type> 
class matrix
{
public:
    // dot operation
    matrix<type> * dot(matrix & m);

    unsigned int ncol, nrow;
    // to store matrix data
    type **m;
    // matrix transposition
    matrix<type> * T();
    
    // print all items in he matrix
    void print();
    friend std::ostream &operator<< (std::ostream & os, const matrix<type> & mt){
        os << endl;
        for (int i = 0; i < mt.nrow; ++i){
            for (int j = 0; j < mt.ncol; ++j){
                os << mt.m[i][j] << ", ";
            }
            os << endl;
        } 
        return os; 
    }
    // matrix multiplication operation
    void multiply(type times);
    // reload += operation
    void operator+=(type scaler);
    // reload *= operation
    void operator*= (type scaler);
    // construct function, without initial value passed
    matrix(unsigned int row, unsigned int col);
    // construct function, with initial value passed
    matrix(unsigned int row, unsigned int col, type * data);

    ~matrix(){
        for(int i = 0; i < nrow; i++){
            free(m[i]);
        }
        free(m);
    }
private:
    
};
/*
*********************************************************************
function name: dot

description: dot product operation

parameters: 
            & mt matrix to dot product with

return: none
*********************************************************************
*/
template <class type> 
matrix<type> * matrix<type>::dot(matrix<type> & mt)
{
    matrix<type> * mres = new matrix(nrow, mt.ncol, NULL);      // to store result matrix
    type sum;
    for (int i = 0; i < mres -> nrow; ++i){
        for (int j = 0; j < mres -> ncol; ++j){
            sum = 0.0;
            for (int k = 0; k < ncol; ++k){
                sum += m[i][k] * mt.m[k][j];
            }
            mres -> m[i][j] = sum;
        }
    }
    return mres;
}
/*
*********************************************************************
function name: T

description: matrix transposition

parameters: 
            none

return: none
*********************************************************************
*/
template <class type> 
matrix<type> * matrix<type>::T()
{
    matrix<type> * mres = new matrix(ncol, nrow, NULL);

    for (int i = 0; i < nrow; ++i){
        for (int j = 0; j < ncol; ++j){
            mres -> m[j][i] = m[i][j];
        }
    }
    return mres;
}
/*
*********************************************************************
function name: print

description: dot product operation

parameters: 
            none

return: none
*********************************************************************
*/
template <class type> 
void matrix<type>::print()
{
    for (int i = 0; i < nrow; ++i){
        for (int j = 0; j < ncol; ++j){
            cout << m[i][j] << ", ";
        }
        cout << endl;
    }
}

/*
*********************************************************************
function name: multiply

description: multiply with a number for all items

parameters: 
            none

return: none
*********************************************************************
*/
template <class type> 
void matrix<type>::multiply(type times)
{
    for (int i = 0; i < nrow; ++i){
        for (int j = 0; j < ncol; ++j){
            m[i][j] *= times;
        }
    }
}
/*
*********************************************************************
function name: matrix

description: constructor to handle with initial value passed.

parameters: 
            none

return: none
*********************************************************************
*/
template <class type> 
matrix<type>::matrix(unsigned int row, unsigned int col, type * data)
{
    // first, allocate space for pointers of each row
    m = (type **)malloc(row * sizeof(type *));
    for(int i = 0; i < row; i++){
        // allocate space for all the rows
        m[i] = (type *)malloc(col * sizeof(type));
        if(m[i] == NULL){
            fprintf(stderr, "out of memory\n");
            exit(1);
        }
    }
    // update object properties
    nrow = row;
    ncol = col;

    // initialize with give data
    if(NULL != data)
    {
        for (int i = 0; i < nrow; ++i){
            for (int j = 0; j < ncol; ++j){
                m[i][j] = data[i*ncol + j];
            }
        }
    }
    else // if no initialize data given, force initialize as zero
    {   
        for (int i = 0; i < nrow; ++i){
            for (int j = 0; j < ncol; ++j){
                m[i][j] = 0;
            }
        }
    }
}

/*
*********************************************************************
function name: matrix

description: constructor to handle without pass initial value.

parameters: 
            none

return: none
*********************************************************************
*/
template <class type> 
matrix<type>::matrix(unsigned int row, unsigned int col)
{
    // first, allocate space for pointers of each row
    m = (type **)malloc(row * sizeof(type *));
    for(int i = 0; i < row; i++){
        // allocate space for all the rows
        m[i] = (type *)malloc(col * sizeof(type));
        if(m[i] == NULL){
            fprintf(stderr, "out of memory\n");
            exit(1);
        }
    }
    // update object properties
    nrow = row;
    ncol = col;

    // force initialize as zero
    for (int i = 0; i < nrow; ++i){
        for (int j = 0; j < ncol; ++j){
            m[i][j] = 0;
        }
    }
}
/*
*********************************************************************
function name: operator+= 

description: reload += operation to add a bias to all items

parameters: 
            none

return: none
*********************************************************************
*/
template <class type> 
void matrix<type>::operator+= (type bias)
{
    for (int i = 0; i < nrow; ++i){
        for (int j = 0; j < ncol; ++j){
            m[i][j] += bias;
        }
    }
}

/*
*********************************************************************
function name: operator+*= 

description: reload *= operation to time a scaler to all items

parameters: 
            none

return: none
*********************************************************************
*/
template <class type> 
void matrix<type>::operator*= (type scaler)
{
    for (int i = 0; i < nrow; ++i){
        for (int j = 0; j < ncol; ++j){
            m[i][j] *= scaler;
        }
    }
}

#endif  // MATRIX_HPP_