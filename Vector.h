//
// Created by Kevin Wong on 2017-03-19.
//

#ifndef LINEARMATRIX_VECTOR_H
#define LINEARMATRIX_VECTOR_H


class Vector {

public:

    Vector();
    Vector(int dimensions, double* values);
    int         getDimension() const;
    double*     getValues() const;
    void        printValues();

private:

    int         numDimensions;
    double*     vectorValues;

};


#endif //LINEARMATRIX_VECTOR_H
