#include<iostream>
#include"matrix.h"
using namespace std;

int main() {
	matrix<double> A(2, 2);
	A.get_data_refer(0, 0) = 1.1;
	A.get_data_refer(0, 1) = 2;
	A.get_data_refer(1, 0) = 3;
	A.get_data_refer(1, 1) = 4;
	matrix<double> B(2, 1);
	B.get_data_refer(0, 0) = 2.2;
	B.get_data_refer(1, 0) = 2;
	cout << A;
	cout << B;
	cout << B(0,0) << endl;
	cout << A * B;
	matrix<double> C = A;
	cout << C * A;
	cout << "test transpose:" << endl;
	A.transpose();
	B.transpose();
	cout << A;
	cout << B;
	cout << transpose(B);
	cout << "begin test kroneck product" << endl;
	cout << kron(A, B);
	cout << kron(B, A);
	cout << kron(A, A);
	return 0;
}