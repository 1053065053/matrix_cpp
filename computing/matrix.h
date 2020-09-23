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
      matrix() :Data(NULL), rows(0), cols(0) { cout << "call the default constructor" << endl; }
    // constructor
      matrix(const int& rr, const int& cc);

    // copy constructor
    matrix(const matrix<T> &m);
    // move constructor...???????§Ö?????????????????
    matrix(matrix<T>&& m) noexcept :Data(m.Data), rows(m.rows), cols(m.cols) {
        m.Data = nullptr;
        m.rows = m.cols = 0;
        cout << "has called move constructor" << endl;
    }
    // can be used to change the ith row and the jth col, 0<=i<=rows-1,
    // 0<=j<=cols-1
    T& get_data_refer(const int &row, const int &col);
    // get the ith row and jth col element of thr matrix, 0<=i<=rows-1,
    // 0<=j<=cols-1
    T get_data(const int &row, const int &col) const;
    // destructor
    ~matrix();
    // overload operator=
    matrix<T>& operator=(const matrix<T> &m);
    // get rows
    int row() const;
    // get cols
    int col() const;
    // overload operator*,????????????????????????????????????
    matrix operator*(const matrix<T> &m) const;
    //overload operator() to realize get_data_refer
    T& operator()(const int& row, const int& col);
    //overload operator() to realize get_data
    T operator()(const int& row, const int& col) const;
	//tranpose
    void transpose();
};


//overload standard output
template<typename T>
ostream& operator<<(ostream& os, const matrix<T>& m);
//transpose
template<typename T>
matrix<T> transpose(const matrix<T>& m);
//kroneck product
template<typename T>
matrix<T> kron(const matrix<T>& m1, const matrix<T>& m2);
//generate unit matrix
matrix<int> unit(const int& k);
//generate toeplitz matrix, m is an odd dimensional column vector
template<typename T>
matrix<T> toep(const matrix<T>& m);





//???
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
    /*cout << "destorying the:" << endl;
    cout << *this;*/
    for (int i = 0; i < rows; i++) {
        delete[] Data[i];
    }
    delete[] Data;
    cout << "has used the destructor" << endl;
}

template<typename T>
T matrix<T>::get_data(const int& row, const int& col) const {
    return Data[row][col];
}
template<typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m) {
    if (&m != this) {
        cout << "???¡¤???" << endl;
        cout << this->rows << endl;
        cout << this->cols << endl;
        for (int i = 0; i < this->rows; i++) {
            delete[] Data[i];
            cout << "???¡¤???" << endl;
        }
        delete[] Data;

        cout << "???¡¤???" << endl;
        cols = m.col();
        rows = m.row();
        //??????????????????§Û?
        Data = new T * [rows];

        for (int i = 0; i < rows; i++) {
            Data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                Data[i][j] = m.get_data(i, j);
            }
        }
    }
    return *this;
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
            temp(i, j) = m.get_data(j,i);
        }
    }
    return temp;
}

template<typename T>
void matrix<T>::transpose() {
    if (this->rows == this->cols) {//no need to apply a new memory
        T temp;
        for (int i = 0; i < this->col(); i++) {
            for (int j = i+1; j <this->row(); j++) {
                temp = this->operator()(j, i);
                this->operator()(j,i) = this->operator()(i,j);
                this->operator()(i, j) = temp;
            }
        }
    }
    else {//call the non-member function transpose
        this->operator= (::transpose(*this));
    }
}

template<typename T>
T matrix<T>::operator()(const int& row, const int& col) const {
    return this->get_data(row,col);
}

template<typename T>
matrix<T> kron(const matrix<T>& m1, const matrix<T>& m2) {
    matrix<T> temp(m1.row() * m2.row(), m1.col() * m2.col());
    for (int i = 0; i < m1.row(); ++i) {
        for (int j = 0; j < m1.col(); ++j) {
            for (int k = 0; k < m2.row(); ++k) {
                for (int m = 0; m < m2.col(); ++m) {
                    temp(i*m2.row()+k,j*m2.col()+m ) = m1(i, j) * m2(k, m);
                }
            }
        }
    }
    return temp;
}

template<typename T>
matrix<T> toep(const matrix<T>& m) {
    int m_length = m.row();
    int res_rows = m.row() / 2 + 1;
    matrix<T> res(res_rows, res_rows);
    for (int i = 0; i < res_rows; ++i) {
        for (int j = 0; j < res_rows; ++j) {
            res(i, j) = m(i - j + res_rows - 1, 0);
        }
    }
    return res;
}

//template<typename T>
//matrix<T>::matrix(matrix<T>&& m) noexcept :Data(m.Data), rows(m.rows), cols(m.cols) {
//    m.Data = nullptr;
//    m.rows = m.cols = 0;
//    cout << "has called move constructor" << endl;
//}