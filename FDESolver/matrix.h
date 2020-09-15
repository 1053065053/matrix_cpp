#pragma once
#include <iostream>

using namespace std;

template<typename T>
class matrix {
  private:
    T **Data;
    int rows;
    int cols;

  public:
    //default constructor
    // constructor
      matrix(const int& rr, const int& cc);

    // copy constructor
    matrix(const matrix<T> &m);
    // can be used to change the ith row and the jth col, 0<=i<=rows-1,
    // 0<=j<=cols-1
    T& get_data_refer(const int &row, const int &col);
    // get the ith row and jth col element of thr matrix, 0<=i<=rows-1,
    // 0<=j<=cols-1
    T get_data(const int &row, const int &col) const;
    // destructor
    ~matrix();
    // overload operator=
    void operator=(const matrix<T> &m);
    // get rows
    int row() const;
    // get cols
    int col() const;
    // overload operator*,����ķ�������ĳ����ÿ��ܻ���ã����������⡣
    matrix operator*(const matrix<T> &m) const;
    //overload operator() to realize get_data_refer
    T& operator()(const int& row, const int& col);
	//tranpose
    void transpose();
};
//overload standard output
template<typename T>
ostream& operator<<(ostream& os, const matrix<T>& m);
//transpose
template<typename T>
matrix<T> transpose(const matrix<T>& m);






//ʵ��
template<typename T>
ostream& operator<<(ostream& os, const matrix<T>& m) {
    for (int i = 0; i < m.row(); i++) {
        for (int j = 0; j < m.col(); j++) {
            os << m.get_data(i, j) << '\t';
        }
        os << endl;
    }
    return os;
}

template<typename T>
matrix<T>::matrix(const int& rr, const int& cc) {
    rows = rr;
    cols = cc;
    Data = new T * [rows];
    for (int i = 0; i < rows; i++) {
        Data[i] = new T[cols];
    }
}

template<typename T>
matrix<T>::matrix(const matrix<T>& m) { *this = m; cout << "has used copy constructor" << endl; }

template<typename T>
matrix<T>::~matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] Data[i];
    }
    delete[] Data;
}

template<typename T>
T matrix<T>::get_data(const int& row, const int& col) const {
    return Data[row][col];
}
template<typename T>
void matrix<T>::operator=(const matrix<T>& m) {

    cols = m.col();
    rows = m.row();
    //ע��һ������᲻�����ڴ�й©
    Data = new T * [rows];

    for (int i = 0; i < rows; i++) {
        Data[i] = new T[cols];
        for (int j = 0; j < cols; j++) {
            Data[i][j] = m.get_data(i, j);
        }
    }
}
template<typename T>
int matrix<T>::col() const { return cols; }

template<typename T>
int matrix<T>::row() const { return rows; }

template<typename T>
T& matrix<T>::get_data_refer(const int& row, const int& col) {
    return Data[row][col];
}

template<typename T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const {

    matrix res(this->rows, m.col());

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < m.col(); j++) {
            double temp = 0;
            for (int k = 0; k < cols; k++) {
                temp += Data[i][k] * m.Data[k][j];
            }
            res.get_data_refer(i, j) = temp;
        }
    }
    return res;
}

template<typename T>
T& matrix<T>::operator()(const int& row, const int& col) { return this->get_data_refer(row, col); }

template<typename T>
matrix<T> transpose(const matrix<T>& m) {
    matrix<T> temp(m.col(), m.row());
    for (int i = 0; i < m.col(); i++) {
        for (int j = 0; j < m.row(); j++) {
            temp(i, j) = m(j, i);
        }
    }
    return temp;
}