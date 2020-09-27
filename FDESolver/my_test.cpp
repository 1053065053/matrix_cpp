#include<iostream>
#include<fftw3.h>
#include"matrix.h"
using namespace std;

int main() {
	matrix<double> A(2, 2);
	A.get_data_refer(0, 0) = 1.1;
	A.get_data_refer(0, 1) = 2;
	A.get_data_refer(1, 0) = 3;
	A.get_data_refer(1, 1) = 4;
	matrix<double> D;
	D = A;

	matrix<double> B(2, 1);
	B.get_data_refer(0, 0) = 2.2;
	B.get_data_refer(1, 0) = 2;
	cout << A;
	cout << B;
	cout << B(0,0) << endl;
	cout << A * B;
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
	
	matrix<double> C(5, 1);
	C(0, 0) = 0;
	C(1, 0) = 1;
	C(2, 0) = 2;
	C(3, 0) = 3;
	C(4, 0) = 4;
	cout << toep(C);
	cout << unit(10);
	cout << "over!" << endl;

	


	return 0;


}