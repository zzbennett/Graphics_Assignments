#include"Matrix.h"
#include<stdio.h>

Matrix::Matrix(float elements[4][4]){
    for(int row=0; row<4; row++){
	for(int column=0; column<4; column++){
	    this->elements[row][column] = elements[row][column];
	}
    }

    this->rows = 4;
    this->columns = 4;
}

void Matrix::Vector( float vector[4] ){
    for(int column = 0; column<4; column++){
	elements[0][column] = vector[column];
    }
    this->rows = 1;
    this->columns = 4;
}

Matrix* Matrix::Multiply(Matrix* matrix){
    if(this->columns != matrix->rows){
	/*Throw an error!*/
    }
    Matrix* ret = new Matrix();
    ret->rows = this->rows;
    ret->columns = matrix->columns;
    for(int row = 0; row<this->rows; row++){
	for(int column = 0; column<matrix->columns; column++){
	    ret->elements[row][column] = Matrix::DotProduct(this, matrix, row, column);
	}
    }
	    

    return ret;
}

/*Given Matrix A and Matrix B, take the dot product of given row in A and given column in B*/
float Matrix::DotProduct(Matrix* matrix_a, Matrix* matrix_b, int row, int column){
    /*take dot product of this row of this matrix and this column of input matrix*/
	    /*		    q
	      < a b c > * < r > == aq + br + cs
			    s			    */
    float sum = 0;
    int i;
    int j;
    for(i = 0, j = 0; i<matrix_a->columns; i++, j++){
	    sum += ((matrix_a->elements[row][i]) * (matrix_b->elements[j][column]));
    }
    return sum;
}

Matrix* Matrix::Homogenize(Matrix* matrix)
{
    float elements[matrix->rows][matrix->columns];
    float divisor = matrix->elements[matrix->rows-1][matrix->columns-1];
    for(int row = 0; row < matrix->rows; row++){
	for(int column = 0; column < matrix->columns; column++){
	    //elements[row][column] = (matrix->elements[row][column])/divisor;
	    matrix->elements[row][column] = (matrix->elements[row][column])/divisor;
	}
    }

    return matrix;
}

Matrix::Matrix(void)
{
    this->rows = 0;
    this->columns = 0;

}

Matrix::~Matrix(void)
{
}

string Matrix::ToString(){

    string matrixString = "";

    for(int row=0;row<this->rows;row++){
	for(int column=0;column<this->columns;column++){
	    float matrixElement = this->elements[row][column];
	    cout << fixed << setprecision(3) << matrixElement << "\t\t";
	}

	 
	cout << "\n" << endl;
    }

    return matrixString;
}
