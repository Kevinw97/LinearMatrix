#ifndef LINEARMATRIX_MATRIX_H
#define LINEARMATRIX_MATRIX_H


#include "Vector.h"

class Matrix {

public:

    Matrix();
    Matrix(int rows, int columns);
    void setRowValues(int row, int numVals, double* values);
    void setColumnValues(int column, int numVals, double* values);
    void setValue(int row, int column, double value);
    void printRow(int row);
    void printColumn(int column);
    void printMatrix();
    void printInverseMatrix();
    bool multipliable(Matrix matrix);
    Matrix addMatrix(Matrix matrix);
    Matrix leftMultiplyBy(Matrix matrix);
    Matrix rightMultiplyBy(Matrix matrix);
    Matrix inverseMatrix();
    double determinant();
    void rowReduceREF();
    void rowReduceRREF();
    void addRows(int one, int two, double factor, int size);
    void scaleRow(int row, double factor, int size);
    void swap(int row1, int row2, int size);
    int getPivotCol(int row, int size);

private:

    int         numRows;
    int         numColumns;
    double**     matrixValues;
};


#endif //LINEARMATRIX_MATRIX_H
