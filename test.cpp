#include "matrix.hpp"

int main(int argc, char const *argv[])
{
    //matrix <float> & m = new matrix(2, 3);
    double data[] = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3};
    matrix <double> m(3, 3, data);
    // print the new matrix
    m.print();

    cout << endl;

    // get transposition
    matrix <double> * mt = m.T();

    cout << m.m[1][2] << " == " << mt -> m[2][1] << endl;
    cout << endl;

    // print transposition
    mt -> print();
    cout << endl;

    // dot product with transposition
    matrix <double> * mdot = m.dot(*mt);

    // print dot product result
    mdot -> print();

    cout << endl;

    mdot -> multiply(1.0 / 10.0);

    mdot -> print();

    // you must take care of these memory allocated by new in head.
    delete mt;
    delete mdot;
    return 0;
}