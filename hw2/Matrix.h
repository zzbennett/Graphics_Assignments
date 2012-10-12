using namespace std;

class Matrix 
{
    public:
	Matrix(float elements[4][4]);
	Matrix* Multiply(Matrix* matrix);
	Matrix(void);
	~Matrix(void);
	float elements[4][4];
};
