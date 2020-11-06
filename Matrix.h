#if !defined(MATRIX)
#define MATRIX


#include <string>
#include <vector>
#include<iostream>
#include<math.h>

using namespace std;
typedef vector<vector<double>> twoD;
class Matrix
{
public:
	Matrix();
	Matrix(twoD matrix);
	Matrix(twoD matrix, string no);
	Matrix(long ro, long col);
	Matrix(string x);
	string getName() const;
	void copy(Matrix b);
	//prints content of matrix on the console
	void show()const;
	//returns matrix value
	double value()const;
	//addition of two matrices
	Matrix sum(Matrix b)const;
	//subtraction of two matricies
	Matrix sub(Matrix b)const;
	//Multiplication of two matricies
	Matrix mutilplicate(Matrix b) const;
	//Transpose of Matrix
	Matrix transpose() const;
	//Division between two matricies
	Matrix division(Matrix b)const;
	//find the inverse of matrix
	Matrix inverse()const;
	~Matrix();
	friend  ostream &  operator<<(ostream & os,const Matrix & matrix);
	friend Matrix operator+(const Matrix& a, const Matrix& b);
	friend Matrix operator-(const Matrix& a, const Matrix& b);
	friend Matrix operator*(const Matrix& a, const Matrix& b);
	friend Matrix operator/(const Matrix& a, const Matrix& b);

	Matrix& operator=(Matrix const& m);
private:
	twoD elements;
	string name;
	long rows, columns;
};


#endif // MATRIX