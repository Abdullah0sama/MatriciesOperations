#include <string>
#include <vector>
#include<iostream>
#include <cstdlib>
#include "iomanip"
#include <map>
#include<algorithm>
#include<set>
#include<functional>
#include "Matrix.h"
using namespace std;

map<string, function<Matrix(Matrix, Matrix)>> operations = { {"+", plus < Matrix>()}, {"-", minus<Matrix>()},
															{"*" ,multiplies<Matrix>()}, {"/", divides<Matrix>()}};
/**
Changes string to 2D vector  of  type double
@parm takes string  in form of A = [1 2 3 ...;1 2 3 ...;..........]
@return vector  of  type  vector<double>
*/
vector<vector<double>> toNumbers(string whole) {
	auto x = whole.find("[");
	string no = whole.substr(x + 1, whole.size() - x - 2);
	size_t endRow;
	vector<vector<double>> contain;
	do {
		endRow = no.find(";");
		vector<double> temp;
		string hold = no.substr(0, endRow);
		//add numbers to first row
		size_t space;
		do {
			space = hold.find(" ");
			temp.push_back(stod(hold.substr(0, hold.find(" "))));
			hold = hold.substr(hold.find(" ") + 1, hold.size() - hold.find(" "));

		} while (space != string::npos);
		no = no.substr(endRow + 2, no.size() - endRow);
		contain.push_back(temp);
		temp.clear();
	} while (endRow != string::npos);
	return contain;

}
//Remove left and right spaces in string
string strip(const string& str) {
	auto x = find_if_not(str.begin(), str.end(), [](const char& a) {
		return isspace(a);
	});
	auto y = find_if(x, str.end(), [](const char& a) {
		return isspace(a);
	});
	return string(x, y);
}
//Cuts the equation into a vector where each element represent a variable or operation
vector<string> cut(const string& cmd) {
	set<char> signs = { '+', '-', '*', '/', '\'', '=' };
	vector<string> parts;
	auto start = cmd.begin();
	while (true && start != cmd.end()) {
		auto pointer = find_if(start, cmd.end(), [signs](const char& c) {
			return (signs.find(c) != signs.end());
		});
		parts.push_back(strip(string(start, pointer)));
		if (pointer == cmd.end())break;
		parts.push_back(string(pointer, pointer + 1));
		start = pointer + 1;
	}
	return parts;
}

int main()
{
	map<string, Matrix> matricies;
	string hold;
	while (hold != "exit") {
		getline(cin, hold);
		vector<string> variables(cut(hold));
		//The if conditions checks and preformes the user input
		if (hold.find("[")!= string::npos) {
			matricies[variables[0]] = Matrix(toNumbers(hold));
		}
		else if (hold.find("det") != string::npos) {
			cout << setprecision(15) << matricies[strip(string(hold.begin()+3, hold.end()))].value() << endl;
		}
		else {
			if (variables.size() == 5) {
				matricies[variables[0]] = operations[variables[3]](matricies[variables[2]], matricies[variables[4]]);
			}
			else if (variables.size() == 4) {
				matricies[variables[0]] = matricies[variables[2]].transpose();
			}
				cout << matricies[variables[0]];
		}
	}
	system("pause");
}



	/*
	Test Cases
	A = [2 3 4 12 12; 12 34 55 12 2; 23 21 23 13 3; 13 43 23 12 4; 1 2 3 4 5]
	B = [213 21 23 21 1; 22 23 45 1 2; 13 4 5 5 1; 2 23 4 5 5; 12 345 231 12 12]
	C = [3 2 1; 3 2 4; 12 23 4]
	D = [54 3 9; 3 7 2; 2 6 4]
	E = [21 21 4; 6 2 1; 8 10 23]
	*/


