#include<string>
#include<sstream>
#include<iomanip>
#include<iostream>

using namespace std;

class Matrix 
{
    public:
	Matrix(float elements[4][4]);
	Matrix* Multiply(Matrix* matrix);
	Matrix* Homogenize(Matrix* matrix);
	float DotProduct(Matrix* matrix_a, Matrix* matrix_b, int row, int column);
	string ToString();
	Matrix(void);
	~Matrix(void);
	float elements[4][4];
	void Vector( float vector[4] );
	void Line( Matrix* p1, Matrix* p2);
	void Line( float p1[3], float p2[3]);
	int rows, columns;
	int isEmpty;
};
