#include"matrix.h"
#include<fftw3.h>

matrix<int> unit(const int& k) {
    //使用toeplitz来实现
    matrix<int> temp(2 * k - 1, 1);
    for (int i = 0; i < temp.row(); ++i) {
        temp(i, 0) = 0;
    }
    temp(k - 1, 0) = 1;
    return toep(temp);
}

matrix<double> fft(const matrix<double>& v, const int& flag) {
    //call the fftw
	fftw_complex* in;
	fftw_plan p;
	int N = v.row();
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	p = fftw_plan_dft_1d(N, in, in, 1, FFTW_ESTIMATE);

	for (int i = 0; i < N; ++i) {
		in[i][0] = v(i, 0);
		in[i][1] = 0;
	}
	fftw_execute(p);

	matrix<double> res(N,1);
	if (flag == -1) {
		for (int i = 0; i < N; ++i) {
			res(i, 0) = in[i][0];
		}
	}else {
		for (int i = 0; i < N; ++i) {
			res(i, 0) = in[i][0];
		}
	}
	fftw_destroy_plan(p);
	fftw_free(in);
	return res;
}