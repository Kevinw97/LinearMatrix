#include <iostream>
#include "Vector.h"


using namespace std;

Vector::Vector() {
    numDimensions = 0;
    vectorValues = 0;
}

Vector::Vector(int dimensions, double* values) {
    numDimensions = dimensions;
    vectorValues = new double[dimensions];
    for (int i = 0; i < dimensions; i++) {
        vectorValues[i] = values[i];
    }
}

int Vector::getDimension() const {
    return numDimensions;
}

double* Vector::getValues() const {
    return vectorValues;
}

void Vector::printValues() {
    for (int i = 0; i < numDimensions ; i++) {
        cout << "val" << (i + 1) << " = " << vectorValues[i] << endl;
    }
}