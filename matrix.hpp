/*
 *  dht11_to_mysql.c
 *
 *
 *  dht11_to_mysql.c contains the code that read measured data from dht11, 
 *  data process (sensor protocol) and insert read value to database table 
 *  
 *  compile: gcc -Wall -o dht11_to_mysql dht11_to_mysql.c -lwiringPi `mysql_config --cflags --libs`
 */
#include <iostream>

using namespace std;

template <class type> class matrix
{
  public:
    matrix<type> * dot(matrix & m);
    unsigned int ncol, nrow;
    matrix<type> * T();
    type **m;
    void print();

    matrix(unsigned int row, unsigned int col, type * data)
    {
        m = (type **)malloc(row * sizeof(type *));
        for(int i = 0; i < row; i++)
        {
            m[i] = (type *)malloc(col * sizeof(type));
            if(m[i] == NULL)
            {
                fprintf(stderr, "out of memory\n");
                exit(1);
            }
        }
        nrow = row;
        ncol = col;
        if(NULL != data)
        {
            for (int i = 0; i < nrow; ++i)
            {
                for (int j = 0; j < ncol; ++j)
                {
                    m[i][j] = data[i*ncol + j];
                }
            }
        }
    }
    ~matrix()
    {
        free(m);
    }
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
template <class type> matrix<type> * matrix<type>::dot(matrix<type> & mt)
{
    matrix<type> * mres = new matrix(nrow, mt.ncol, NULL);      // to store result matrix
    type sum;
    for (int i = 0; i < mres -> nrow; ++i)
    {
        for (int j = 0; j < mres -> ncol; ++j)
        {
            sum = 0.0;
            for (int k = 0; k < ncol; ++k)
            {
                sum += m[i][k] * mt.m[k][j];
            }
            mres -> m[i][j] = sum;
        }
    }
    return mres;
}
/*
*********************************************************************
function name: matrix transposition

description: dot product operation

parameters: 
            none

return: none
*********************************************************************
*/
template <class type> matrix<type> * matrix<type>::T()
{
    matrix<type> * mres = new matrix(ncol, nrow, NULL);

    for (int i = 0; i < nrow; ++i)
    {
        for (int j = 0; j < ncol; ++j)
        {
            mres -> m[j][i] = m[i][j];
        }
    }
    return mres;
}
/*
*********************************************************************
function name: print matrix items

description: dot product operation

parameters: 
            none

return: none
*********************************************************************
*/
template <class type> void matrix<type>::print()
{
    for (int i = 0; i < nrow; ++i)
    {
        for (int j = 0; j < ncol; ++j)
        {
            cout << m[i][j] << ", ";
        }
        cout << endl;
    }
}
