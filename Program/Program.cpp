// Program.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

void test_matrix();
void test_broadcast();
void test_decomposition();
void test_interpolation();
void test_regression();
void test_spline();

int _tmain(int argc, _TCHAR* argv[])
{
	ndmatrix<3> t0(dim(3, 3, 4, 4), 0);
	t0[0] += 10;
	t0.cout();
	test_matrix();

	return 0;
}

void test_matrix()
{
	clock_t t;
	algmat m0(msize(4, 4));
	algmat m1(msize(4, 4));
	t = clock();
	for (int i = 0; i < 100000; i++)
	{
// 		for (int j = 0; j < m0.length(); j++)
// 		{
// 			m0(0, 0) = 3.14;
// 			m0[0][0] = 3.14;
// 		}
		algmat m2(m0);
	}
	t = clock() - t;
	cout << (float)t << "ms" << endl;
}

void test_broadcast()
{
	algmat m0(msize(4, 4));
	m0[0][0] = 100; m0[0][1] = 3; m0[0][2] = 45; m0[0][3] = 33;
	m0[1][0] = 5; m0[1][1] = 3; m0[1][2] = 5; m0[1][3] = 65;
	m0[2][0] = 100; m0[2][1] = 23; m0[2][2] = 45; m0[2][3] = 56;
	m0[3][0] = 5; m0[3][1] = 3; m0[3][2] = 9; m0[3][3] = 8;
	m0.cout();
	algmat m1(msize(4, 1));
	m1[0][0] = 10;
	m1[1][0] = 20;
	m1[2][0] = 30;
	m1[3][0] = 40;
	m1.cout();
	algmat m2(msize(1, 4));
	m2[0][0] = 10;
	m2[0][1] = 20;
	m2[0][2] = 30;
	m2[0][3] = 40;
	m2.cout();
	(m0 + m1).cout();
	(m1 + m0).cout();
	(m0 - m1).cout();
	(m1 - m0).cout();
	(m0 * m1).cout();
	(m1 * m0).cout();
	(m0 / m1).cout();
	(m1 / m0).cout();
}

void test_decomposition()
{
	clock_t t;
	t = clock();

	algmat m0(msize(4, 4));
	m0[0][0] = 100; m0[0][1] = 3; m0[0][2] = 45; m0[0][3] = 33;
	m0[1][0] = 5; m0[1][1] = 3; m0[1][2] = 5; m0[1][3] = 65;
	m0[2][0] = 100; m0[2][1] = 23; m0[2][2] = 45; m0[2][3] = 56;
	m0[3][0] = 5; m0[3][1] = 3; m0[3][2] = 9; m0[3][3] = 8;
	m0.cout();
	LUD lu(m0, LU_FULL_PIVOT);
	lu[0].cout();
	lu[1].cout();
	lu[0].dot(lu[1]).cout();
	QRD qr(m0);
	qr[0].cout();
	qr[1].cout();
	qr[0].dot(qr[1]).cout();
	qr[0].dot(qr[0].t()).cout();
	EVD ev(m0);
	ev[0].cout();
	ev[1].cout();
	ev[0].dot(ev[1]).dot(ev[0].inv()).cout();
	algmat m1(msize(1, 4));
	m1[0][0] = 5; m1[0][1] = 3; m1[0][2] = 9; m1[0][3] = 8;
	m1.cout();
	SVD sv(m1);
	sv[0].cout();
	sv[1].cout();
	sv[2].cout();
	sv[0].dot(sv[1]).dot(sv[2].t()).cout();
	algmat m2(msize(3, 3));
	m2[0][0] = 1; m2[0][1] = 2; m2[0][2] = 3;
	m2[1][0] = 4; m2[1][1] = 5; m2[1][2] = 6;
	m2[2][0] = 7; m2[2][1] = 8; m2[2][2] = 9;
	m2.dot(SVD::pinv(m2)).cout();
	SVD::pinv(m2).cout();

	t = clock() - t;
	cout << (float)t << "ms" << endl;
}

void test_interpolation()
{
	clock_t t;
	t = clock();

	algmat X(msize(6, 1));
	algmat Y(msize(6, 1));
	X[0][0] = 0.0; X[1][0] = 1.0; X[2][0] = 2.0; X[3][0] = 3.0; X[4][0] = 4.0; X[5][0] = 5.0;
	Y[0][0] = 2.1; Y[1][0] = 7.7; Y[2][0] = 13.6; Y[3][0] = 27.2; Y[4][0] = 40.9; Y[5][0] = 61.1;
	vandermonde vd(X, Y);
	double result = vd.interpolate(4.5);
	algmat C = vd.coeff();
	C.cout();
	newton nt(X, Y);
	result = nt.interpolate(4.5);
	C = nt.coeff();
	C.cout();
	lagrange lg(X, Y);
	result = lg.interpolate(4.5);

	t = clock() - t;
	cout << (float)t << "ms" << endl;
}

void test_regression()
{
	clock_t t;
	t = clock();

	algmat X(msize(6, 1));
	algmat Y(msize(6, 1));
	X[0][0] = 0.0; X[1][0] = 1.0; X[2][0] = 2.0; X[3][0] = 3.0; X[4][0] = 4.0; X[5][0] = 5.0;
	Y[0][0] = 2.1; Y[1][0] = 7.7; Y[2][0] = 13.6; Y[3][0] = 27.2; Y[4][0] = 40.9; Y[5][0] = 61.1;
	polyfit pf(X, Y, 3);
	double result = pf.fit(4.5);
	algmat C = pf.coeff();
	C.cout();
	algmat Xp = algmat::pow(X, 3);
	for (int i = 2; i >= 0; i--)
	{
		Xp = Xp.append(algmat::pow(X, i), 1);
	}
	Xp.cout();
	C = Xp.t().dot(Xp).inv().dot(Xp.t()).dot(Y);
	C.cout();

	t = clock() - t;
	cout << (float)t << "ms" << endl;
}

void test_spline()
{
	clock_t t;
	t = clock();

	algmat X(msize(4, 1));
	algmat Y(msize(4, 1));
	X[0][0] = 3.0; X[1][0] = 4.5; X[2][0] = 7.0; X[3][0] = 9.0;
	Y[0][0] = 2.5; Y[1][0] = 1.0; Y[2][0] = 2.5; Y[3][0] = 0.5;
	linear_spline sp1(X, Y);
	double result = sp1.interpolate(5.0);
	algmat C = sp1.coeff();
	C.cout();
// 	FILE* writer;
// 	fopen_s(&writer, "D:\\linear_spline.csv", "w");
// 	for (double i = 3.0; i <= 9.0; i += 0.1)
// 	{
// 		fprintf_s(writer, "%lf,%lf\n", i, sp1.interpolate(i));
// 	}
// 	fclose(writer);
	quadratic_spline sp2(X, Y);
	result = sp2.interpolate(5.0);
	C = sp2.coeff();
	C.cout();
// 	fopen_s(&writer, "D:\\quadratic_spline.csv", "w");
// 	for (double i = 3.0; i <= 9.0; i += 0.1)
// 	{
// 		fprintf_s(writer, "%lf,%lf\n", i, sp2.interpolate(i));
// 	}
// 	fclose(writer);
	cubic_spline sp3(X, Y, notaknot());
	result = sp3.interpolate(5.0);
	C = sp3.coeff();
	C.cout();
// 	fopen_s(&writer, "D:\\cubic_spline.csv", "w");
// 	for (double i = 3.0; i <= 9.0; i += 0.1)
// 	{
// 		fprintf_s(writer, "%lf,%lf\n", i, sp3.interpolate(i));
// 	}
// 	fclose(writer);
	hermite hm(X, Y);
	result = hm.interpolate(5.0);
	C = hm.coeff();
	C.cout();
// 	fopen_s(&writer, "D:\\hermite_spline.csv", "w");
// 	for (double i = 3.0; i <= 9.0; i += 0.1)
// 	{
// 		fprintf_s(writer, "%lf,%lf\n", i, hm.interpolate(i));
// 	}
// 	fclose(writer);
	akima ak(X, Y);
	result = ak.interpolate(5.0);
	C = ak.coeff();
	C.cout();
// 	fopen_s(&writer, "D:\\akima_spline.csv", "w");
// 	for (double i = 3.0; i <= 9.0; i += 0.1)
// 	{
// 		fprintf_s(writer, "%lf,%lf\n", i, ak.interpolate(i));
// 	}
// 	fclose(writer);

	t = clock() - t;
	cout << (float)t << "ms" << endl;
}
