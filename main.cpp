#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {

    double one[3] = {5,2,1};
    double two[3] = {3,2,1};

    bool keepGoing = true;
    while (keepGoing) {
        cout << "Choose operation:" << endl;
        cout << "1 : Addition" << endl;
        cout << "2 : Multiplication" << endl;
        cout << "3 : Calculate determinant on NxN matrix" << endl;
        cout << "4 : Row reduce to row echelon form" << endl;
        cout << "5 : Row reduce to reduce row echelon form" << endl;
        cout << "6 : Calculate inverse matrix" << endl;

        char buffer[256];
        int operation;
        cin >> buffer;
        operation = atoi(buffer);

        switch (operation) {
            case 1 : {
                cout << "Enter the number of rows in each matrix: ";
                int rows;
                cin >> buffer;
                rows = atoi(buffer);
                cout << endl;

                cout << "Enter the number of columns in each matrix: ";
                int columns;
                cin >> buffer;
                columns = atoi(buffer);
                cout << endl;

                Matrix matrix1 = Matrix(rows, columns);
                Matrix matrix2 = Matrix(rows, columns);

                cout << "Enter values for first matrix: ";
                for (int row = 1; row <= rows; row++) {
                    cout << "Row " << (row) << endl;
                    for (int column = 1; column <= columns; column++) {
                        cout << "Enter value of a" << (row) << (column) << ":";
                        double val;
                        cin >> buffer;
                        val = atof(buffer);
                        matrix1.setValue(row, column, val);
                    }
                    cout << endl;
                }
                cout << "Enter values for second matrix: ";
                for (int row = 1; row <= rows; row++) {
                    cout << "Row " << (row) << endl;
                    for (int column = 1; column <= columns; column++) {
                        cout << "Enter value of a" << (row) << (column) << ": ";
                        double val;
                        cin >> buffer;
                        val = atof(buffer);
                        matrix2.setValue(row, column, val);
                    }
                    cout << endl;
                }

                cout << "Matrix 1:" << endl;
                matrix1.printMatrix();
                cout << endl;
                cout << "Matrix 2:" << endl;
                matrix2.printMatrix();
                cout << endl;

                Matrix summedMatrix = matrix1.addMatrix(matrix2);
                cout << "Result after adding:" << endl;
                summedMatrix.printMatrix();
                break;
            }
            case 2 : {
                cout << "Enter number of rows in left matrix: ";
                cin >> buffer;
                int m1Rows;
                m1Rows = atof(buffer);
                cout << endl;

                cout << "Enter number of columns in left matrix: ";
                cin >> buffer;
                int m1Columns;
                m1Columns = atof(buffer);
                cout << endl;

                Matrix matrix1 = Matrix(m1Rows, m1Columns);

                cout << "Enter number of rows in right matrix: ";
                cin >> buffer;
                int m2Rows;
                m2Rows = atof(buffer);
                cout << endl;

                cout << "Enter number of columns in right matrix: ";
                cin >> buffer;
                int m2Columns;
                m2Columns = atof(buffer);
                cout << endl;

                Matrix matrix2 = Matrix(m2Rows, m2Columns);

                if (matrix1.multipliable(matrix2)) {
                    cout << "Enter values for first matrix: ";
                    for (int row = 1; row <= m1Rows; row++) {
                        cout << "Row " << (row) << endl;
                        for (int column = 1; column <= m1Columns; column++) {
                            cout << "Enter value of a" << (row) << (column) << ": ";
                            double val;
                            cin >> buffer;
                            val = atof(buffer);
                            matrix1.setValue(row, column, val);
                        }
                        cout << endl;
                    }

                    cout << "Enter values for second matrix: ";
                    for (int row = 1; row <= m2Rows; row++) {
                        cout << "Row " << (row) << endl;
                        for (int column = 1; column <= m2Columns; column++) {
                            cout << "Enter value of a" << (row) << (column) << ": ";
                            double val;
                            cin >> buffer;
                            val = atof(buffer);
                            matrix2.setValue(row, column, val);
                        }
                        cout << endl;
                    }

                    cout << "Matrix 1:" << endl;
                    matrix1.printMatrix();
                    cout << endl;
                    cout << "Matrix 2:" << endl;
                    matrix2.printMatrix();
                    cout << endl;

                    Matrix multipliedMatrix = matrix1.rightMultiplyBy(matrix2);
                    cout << "Result after adding:" << endl;
                    multipliedMatrix.printMatrix();
                } else {
                    cout << "Can't multiply a " << m1Rows << "x" << m1Columns << " matrix with a "
                         << m2Rows << "x" << m2Columns << " matrix." << endl;
                }
                break;
            }
            case 3 : {
                cout << "Enter N (number of rows and columns): ";
                int rowsCols;
                cin >> buffer;
                rowsCols = atoi(buffer);
                Matrix matrix = Matrix(rowsCols, rowsCols);
                cout << endl;

                cout << "Enter values for the matrix: ";
                for (int row = 1; row <= rowsCols; row++) {
                    cout << "Row " << (row) << endl;
                    for (int column = 1; column <= rowsCols; column++) {
                        cout << "Enter value of a" << (row) << (column) << ":";
                        double val;
                        cin >> buffer;
                        val = atof(buffer);
                        matrix.setValue(row, column, val);
                    }
                    cout << endl;
                }

                cout << "Matrix :" << endl;
                matrix.printMatrix();
                cout << endl;

                cout << "Determinant is " << matrix.determinant() << endl;
                break;
            }
            case 4 : {
                cout << "Enter the number of rows: ";
                int rows;
                cin >> buffer;
                rows = atoi(buffer);
                cout << endl;

                cout << "Enter the number of columns: ";
                int columns;
                cin >> buffer;
                columns = atoi(buffer);
                cout << endl;

                Matrix matrix = Matrix(rows, columns);

                cout << "Enter values for the matrix: ";
                for (int row = 1; row <= rows; row++) {
                    cout << "Row " << (row) << endl;
                    for (int column = 1; column <= columns; column++) {
                        cout << "Enter value of a" << (row) << (column) << ":";
                        double val;
                        cin >> buffer;
                        val = atof(buffer);
                        matrix.setValue(row, column, val);
                    }
                    cout << endl;
                }
                matrix.rowReduceREF();
                matrix.printMatrix();
                break;
            }
            case 5: {
                cout << "Enter the number of rows: ";
                int rows;
                cin >> buffer;
                rows = atoi(buffer);
                cout << endl;

                cout << "Enter the number of columns: ";
                int columns;
                cin >> buffer;
                columns = atoi(buffer);
                cout << endl;

                Matrix matrix = Matrix(rows, columns);

                cout << "Enter values for the matrix: ";
                for (int row = 1; row <= rows; row++) {
                    cout << "Row " << (row) << endl;
                    for (int column = 1; column <= columns; column++) {
                        cout << "Enter value of a" << (row) << (column) << ":";
                        double val;
                        cin >> buffer;
                        val = atof(buffer);
                        matrix.setValue(row, column, val);
                    }
                    cout << endl;
                }
                matrix.rowReduceRREF();
                matrix.printMatrix();
                break;
            }
            case 6: {
                cout << "Enter N (number of rows and columns): ";
                int rowsCols;
                cin >> buffer;
                rowsCols = atoi(buffer);
                Matrix matrix = Matrix(rowsCols, rowsCols);
                cout << endl;

                cout << "Enter values for the matrix: ";
                for (int row = 1; row <= rowsCols; row++) {
                    cout << "Row " << (row) << endl;
                    for (int column = 1; column <= rowsCols; column++) {
                        cout << "Enter value of a" << (row) << (column) << ":";
                        double val;
                        cin >> buffer;
                        val = atof(buffer);
                        matrix.setValue(row, column, val);
                    }
                    cout << endl;
                }

                cout << "Matrix you entered:" << endl;
                matrix.printMatrix();
                Matrix inverse = matrix.inverseMatrix();
                inverse.rowReduceRREF();
                inverse.printInverseMatrix();
                cout << endl;
                break;
            }
        }
    }
    return 0;
}
