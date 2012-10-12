#include"Matrix.h"

Matrix::Matrix(float elements[4][4]){
    for(int row=0; row<4; row++){
	for(int column=0; column<4; column++){
	    this->elements[row][column] = elements[row][column];
	}
    }
}

Matrix* Matrix::Multiply(Matrix* matrix){
    Matrix* ret = new Matrix();
    return ret;
}

Matrix::Matrix(void)
{
}

Matrix::~Matrix(void)
{
}
