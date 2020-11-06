
#include "Matrix.h"


Matrix::Matrix()
{
}
Matrix::Matrix(twoD matrix) {
	elements = matrix;
	rows = elements.size();
	columns = elements[0].size();
}
Matrix::Matrix(twoD matrix, string no) {
	elements = matrix;
	rows = elements.size();
	columns = elements[0].size();
	name = no;
}
Matrix::Matrix(string x) {
	name = x;

}
void Matrix::copy(Matrix b) {

	elements = b.elements;
	rows = b.rows;
	columns = b.columns;
}
Matrix::Matrix(long ro, long col) {
	twoD x(ro, vector<double>(col, 0));
	elements=x;
	rows = ro;
	columns = col;

}
void Matrix::show() const {
	for (auto &i : elements) {
		for (auto x : i) {
			cout<< x << " ";
		}
		cout << endl;
	}

}
double Matrix::value() const {
	long double value = 0;
	twoD temp;
	vector<double> tempSmall;
	if (rows != 2 && columns != 2) {
		for (int z = 0; z < columns; ++z) {
			for (int i = 1; i < rows; ++i) {
				for (int x = 0; x < columns; ++x) {
					if (x != z) {
						tempSmall.push_back(elements[i][x]);
					}
				}
				temp.push_back(tempSmall);
				tempSmall.clear();
			}
			Matrix small(temp);
			value += pow(-1, z)*elements[0][z]* small.value();
			temp.clear();
		}
	}
	else {
		value += elements[0][0] * elements[1][1] - elements[0][1] * elements[1][0];
	}
	
	

	return value;
}
Matrix Matrix::sum(Matrix b)const {
	Matrix no(1, 1);
	if (rows==b.rows&&columns==b.columns) {
		Matrix ret(rows, columns);
		for (int i = 0; i < rows; ++i) {
			for (int x = 0; x < columns; ++x) {
				ret.elements[i][x] = elements[i][x] + b.elements[i][x];
			}
		}
		return ret;
	}
	return no ;

}
Matrix Matrix::sub(Matrix b)const {
	Matrix no(1,1);
	if (rows == b.rows &&columns == b.columns) {
		Matrix ret(rows, columns);
		for (int i = 0; i < rows; ++i) {
			for (int x = 0; x < columns; ++x) {
				ret.elements[i][x] = elements[i][x] - b.elements[i][x];
			}
		}
		return ret;
	}
	return no;
	
}
Matrix Matrix::mutilplicate(Matrix b) const {
	Matrix no(1, 1);
	if (columns == b.rows) {
		double valueIndex = 0;
		Matrix c (rows, b.columns);
		for (int a = 0; a < rows; ++a) {
			for (int z = 0; z < b.columns; ++z) {
				for (int i = 0; i < columns; ++i) {
						c.elements[a][z] += elements[a][i] * b.elements[i][z];

				}
			}
		}
		return c;
	}
	return no;

}
Matrix Matrix::transpose( )const {
	Matrix c(columns, rows);
	for (int r = 0; r< rows; ++r) {
		for (int x = 0; x < columns; ++x) {

			c.elements[x][r] = elements[r][x];
		}

	}
	return c;
}
Matrix Matrix::inverse() const {
	Matrix c(rows ,columns);
	double determent = value();
	for (int i = 0; i < rows; ++i) {
		for (int x = 0; x < columns; ++x) {
			twoD temp;
			for (int z = 0; z < rows; ++z) {
				vector<double> tempS;
				for (int y = 0; y < columns; ++y) {
					if (z != i && y != x) tempS.push_back(elements[z][y]);
				}
				if(!tempS.empty()) temp.push_back(tempS);
				tempS.clear();

			}
			Matrix t(temp);
			c.elements[i][x] = pow(determent,-1)*pow(-1, i + x)*t.value();
			temp.clear();
		}

	}


	return c.transpose();
}
Matrix Matrix::division(Matrix b) const {

	return mutilplicate(b.inverse());

}
string Matrix::getName()const {
	return name;
}
Matrix::~Matrix()
{
}
ostream & operator<<(ostream & os, const Matrix & matrix) {
	for (auto &i : matrix.elements) {
		for (auto x : i) {
			os << x << " ";
		}
		os << endl;
	}
	return os;
}
Matrix operator+(const Matrix &a, const Matrix &b) {
	return a.sum(b);
}
Matrix operator-(const Matrix &a, const Matrix &b) {
	return a.sub(b);
}
Matrix& Matrix::operator=(Matrix const& m) {
	rows = m.rows;
	columns = m.columns;
	elements = m.elements;
	return *this;
}
Matrix operator*(const Matrix& a, const Matrix& b){
	return a.mutilplicate(b);
}
Matrix operator/(const Matrix& a, const Matrix& b) {
	return a.division(b);
}