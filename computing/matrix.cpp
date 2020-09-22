#include"matrix.h"

matrix<int> unit(const int& k) {
    //ʹ��toeplitz��ʵ��
    matrix<int> temp(2 * k - 1, 1);
    for (int i = 0; i < temp.row(); ++i) {
        temp(i, 0) = 0;
    }
    temp(k - 1, 0) = 1;
    return toep(temp);
}