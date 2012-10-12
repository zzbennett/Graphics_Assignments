using namespace std;

class Matrix 
{
    public:
	Matrix(float elements[4][4]);
	Matrix* Multiply(Matrix* matrix);
	Matrix* Homogenize(Matrix* matrix);
	float DotProduct(Matrix* matrix_a, Matrix* matrix_b, int row, int column);
	Matrix(void);
	~Matrix(void);
	float elements[4][4];
    private:
	int rows, columns;
};
