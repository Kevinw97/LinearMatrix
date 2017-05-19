//
// Created by Kevin Wong on 2017-03-19.
//

#include "Matrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

Matrix::Matrix() {
    numRows = 0;
    numColumns = 0;
    matrixValues = 0;
}

Matrix::Matrix(int rows, int columns) {
    numRows = rows;
    numColumns = columns;
    matrixValues = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrixValues[i] = new double[columns];
    }
}

//void Matrix::setRowValues(int row, int numVals, double* values) {
//    if (row < 1 || row > numRows) {
//        return;
//    }
//    if (sizeof(values)/sizeof(double) <= numColumns) {
//        for (int i = 0; i < numColumns; i++) {
//            matrixValues[row-1][i] = values[i];
//        }
//    }
//}

void Matrix::setColumnValues(int column, int numVals, double* values) {
    if (column < 1 || column > numColumns) {
        return;
    }
    if (sizeof(values)/sizeof(double) <= numRows) {
        for (int i = 0; i < numRows; i++) {
            matrixValues[i][column-1] = values[i];
        }
    }

}

void Matrix::setValue(int row, int column, double value) {
    if (row < 1 || row > numRows || column < 1 || column > numColumns) {
        return;
    }
    matrixValues[row-1][column-1] = value;
}

// Prints out the values of a single row
//void Matrix::printRow(int row) {
//    for (int i = 0; i < numColumns; i++) {
//        cout << "col" << (i + 1) << " val = " << matrixValues[row-1][i] <<  endl;
//    }
//}

// Prints out the values of a single column
//void Matrix::printColumn(int column) {
//    for (int i = 0; i < numRows; i++) {
//        cout << "row" << (i + 1) << " val = " << matrixValues[i][column-1] << endl;
//    }
//}

// Prints matrix out in a grid style
void Matrix::printMatrix() {
    cout << endl;
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numColumns; column++) {
            if (matrixValues[row][column] == 0.0) {
                matrixValues[row][column] = 0.0;
            }
            cout << right << setw(10) << matrixValues[row][column];
        }
        cout << endl;
        cout << endl;
    }
}

// Prints the inverse matrix, given a row-reduced Nx2N matrix
void Matrix::printInverseMatrix() {
    cout << endl;
    if (numColumns == 2* numRows) {
        bool validInverse = 1;
        for (int i = 0; i < numRows; i++) {
            if (matrixValues[i][i] != 1) {
                validInverse = 0;
                break;
            }
        }
        if (validInverse) {
            cout << "The inverse matrix:" << endl;
            cout << endl;
            for (int row = 0; row < numRows; row++) {
                for (int column = 0; column < numRows; column++) {
                    if (matrixValues[row][column+numRows] == 0.0) {
                        matrixValues[row][column+numRows] = 0.0;
                    }
                    cout << right << setw(10) << matrixValues[row][column+numRows];
                }
                cout << endl;
                cout << endl;
            }
        }
        else {
            cout << "The matrix you entered is not invertible." << endl;
        }
    }
}

// Determines if this matrix can be multiplied with the given matrix
bool Matrix::multipliable(Matrix matrix) {
    if (this->numColumns == matrix.numRows) {
        return true;
    }
    else {
        return false;
    }
}

// Returns new matrix with values added by both
Matrix Matrix::addMatrix(Matrix matrix) {
    if ((this->numRows == matrix.numRows) && (this->numColumns == matrix.numColumns)) {
        Matrix returnMatrix = Matrix(numRows, numColumns);
        for (int row = 0; row < numRows; row++) {
            for (int column = 0; column < numColumns; column++) {
                double val = this->matrixValues[row][column] + matrix.matrixValues[row][column];
                returnMatrix.matrixValues[row][column] = val;
            }
        }
        return returnMatrix;
    }
}

// Left multiplies this matrix by another
Matrix Matrix::leftMultiplyBy(Matrix matrix) {
    if (matrix.numColumns == this->numRows) {
        Matrix returnMatrix = Matrix(matrix.numRows, this->numColumns);
        int retMatrixRows = matrix.numRows;
        int retMatrixCols = this->numColumns;
        int mults = matrix.numColumns;
        for (int row = 0; row < retMatrixRows; row++) {
            for (int column = 0; column < retMatrixCols; column++) {
                double val = 0;
                for (int x = 0; x < mults; x++) {
                    val += matrix.matrixValues[row][x] * this->matrixValues[x][column];
                }
                returnMatrix.matrixValues[row][column] = val;
            }
        }
        return returnMatrix;
    }
}

// Right multiplies this matrix by another
Matrix Matrix::rightMultiplyBy(Matrix matrix) {
    if (this->numColumns == matrix.numRows) {
        Matrix returnMatrix = Matrix(this->numRows, matrix.numColumns);
        int retMatrixRows = this->numRows;
        int retMatrixCols = matrix.numColumns;
        int mults = this->numColumns;
        for (int row = 0; row < retMatrixRows; row++) {
            for (int column = 0; column < retMatrixCols; column++) {
                double val = 0;
                for (int x = 0; x < mults; x++) {
                    val += this->matrixValues[row][x] * matrix.matrixValues[x][column];
                }
                returnMatrix.matrixValues[row][column] = val;
            }
        }
        return returnMatrix;
    }
}

// Calculates and returns the determinant
double Matrix::determinant() {
    double det = 0;
    // Base case: the matrix is 2 by 2 and can be calculated by cross-multiplying its values
    if ((numRows == 2) && (numColumns == 2)) {
        det = (matrixValues[0][0] * matrixValues[1][1]) -
                (matrixValues[1][0] * matrixValues[0][1]);
        return det;
    }
    if (numRows == numColumns) {
        // Cofactor expansion portion
        for (int x = 0; x < numRows; x++) {
            double sign = 1;
            double b = matrixValues[0][x];
            if (b != 0) {
                // Determine what the sign of the cofactor should be
                if (x % 2 == 0) {
                    sign = 1;
                } else {
                    sign = -1;
                }
                // Create a sub-matrix to calculate the determinant of
                Matrix cofactorDet = Matrix(numRows - 1, numColumns - 1);
                // Get values of the columns to left of cofactor number
                for (int i = 0; i < x; i++) {
                    // Temporarily copy a column
                    double *colVals = new double[numColumns - 1];
                    for (int j = 1; j < numColumns; j++) {
                        colVals[j - 1] = matrixValues[j][i];
                    }
                    cofactorDet.setColumnValues(i + 1, numColumns-1, colVals);
                    delete[] colVals;
                }
                // Get values of the columns to right of cofactor number;
                for (int i = x + 1; i < numColumns; i++) {
                    double *colVals = new double[numColumns - 1];
                    for (int j = 1; j < numColumns; j++) {
                        colVals[j - 1] = matrixValues[j][i];
                    }
                    cofactorDet.setColumnValues(i, numColumns-1, colVals);
                    delete[] colVals;
                }
                // Recursively calculate and add the sub matrix determinants
                det += (b * sign * cofactorDet.determinant());
            }
        }
        return det;
    }
}

void Matrix::rowReduceREF() {
    // Row exchange rows by descending order of first value
    int pivotRow = 1;
    // Gaussian elimination first step
    for (int i = 1; i <= numRows && pivotRow <= numRows; i++) {
        int count = pivotRow + 1;
        // Swap until the pivotRow is non-zero
        while (matrixValues[pivotRow-1][i-1] == 0 && count <= numRows) {
            swap(pivotRow, count, numColumns);
            count++;
        }
        double pivotValue = matrixValues[pivotRow-1][i-1];
        // If pivotValue is not 0, then row eliminate everything below
        if (pivotValue != 0) {
            for (int j = pivotRow + 1; j <= numRows; j++) {
                double factor = (matrixValues[j-1][i-1] / pivotValue)*-1;
                addRows(pivotRow, j, factor, numColumns);
            }
            pivotRow++;
        }
    }
}

void Matrix::rowReduceRREF() {
    // Reduce to REF first
    rowReduceREF();
    // Scale every single row so that the leading value is a pivot (1)
    for (int i = numRows; i >= 1; i--) {
        int col = getPivotCol(i, numColumns);
        if (col != 0) {
            double pivotValue = matrixValues[i - 1][col - 1];
            double scaleFactor = 1 / pivotValue;
            scaleRow(i, scaleFactor, numColumns);
        }
    }
    // Row eliminate upwards starting from the bottom row
    for (int i = numRows; i >= 1; i--) {
        int col = getPivotCol(i, numColumns);
        if (col != 0) {
            for (int j = i - 1; j >= 1; j--) {
                double pivotValue = matrixValues[i-1][col-1];
                double factor = (matrixValues[j-1][col-1] / pivotValue)*-1;
                addRows(i, j, factor, numColumns);
            }
        }
    }

}

// Prepare a Nx2N matrix to row-reduce and extract an inverse matrix from
Matrix Matrix::inverseMatrix() {
    Matrix invMatrix = Matrix(numRows, 2*numColumns);
    for (int i = 1; i <= numRows; i++) {
        for (int j = 1; j <= numRows; j++) {
            if (i == j) {
                invMatrix.setValue(i,j+numColumns,1);
            }
            else {
                invMatrix.setValue(i,j+numColumns,0);
            }
            invMatrix.setValue(i,j,matrixValues[i-1][j-1]);

        }
    }
    return invMatrix;
}

// Helper function to get the column that the pivot is on (not zero based)
int Matrix::getPivotCol(int row, int size) {
    int position = 0;
    for (int i = 0; i < size; i++) {
        if (matrixValues[row-1][i] != 0) {
            position = i+1;
            break;
        }
    }
    return position;
}

// Swap two rows
void Matrix::swap(int row1, int row2, int size) {
    int temp[size];
    for (int i = 0; i < size; i++) {
        temp[i] = matrixValues[row1-1][i];
    }
    for (int j = 0; j < size; j++) {
        matrixValues[row1-1][j] = matrixValues[row2-1][j];
        matrixValues[row2-1][j] = temp[j];
    }
}

// Simple addition of two rows with a factor
void Matrix::addRows(int from, int to, double factor, int size) {
    for (int i = 0; i < size; i++) {
        matrixValues[to-1][i] += matrixValues[from-1][i] * factor;
    }
}

// Multiply a row by a scalar quantity
void Matrix::scaleRow(int row, double factor, int size) {
    for (int i = 0; i < size; i++) {
        matrixValues[row-1][i] *= factor;
    }
}

