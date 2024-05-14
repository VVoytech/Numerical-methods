#include <iostream>
#include <cmath>

using namespace std;

typedef double (*FunctionPointer)(double x, double y);



double function(double x, double y) {
	return pow(x, 2) + y;
}

void euler_method(FunctionPointer func, double a, double b, double N, double Y0)
{
	double h = (b - a) / N;
	double tempX = a;
	double tempY = Y0;

	cout << "Rozwiazanie zadania metada Eulera\n";

	for (int i = 1; i <= N; i++)
	{
		double X = tempX + h;
		double Y = tempY + h * (func(tempX, tempY));
		cout << "x" << i << " = " << X << endl;
		cout << "y" << i << " = " << Y << endl;
		tempX = X;
		tempY = Y;
	}

	cout << "\nRozwiazanie w koncowym punkcie: " << tempY << endl;
}

double RK2(FunctionPointer func, double tempX, double tempY, double h)
{
	double k1, k2;

	k1 = func(tempX, tempY);
	k2 = func(tempX + h, tempY + h * k1);

	return (k1 + k2) / 2;
}

double RK4(FunctionPointer func, double tempX, double tempY, double h)
{
	double k1, k2, k3, k4;

	k1 = func(tempX, tempY);
	k2 = func(tempX + (h / 2), tempY + ((h * k1) / 2));
	k3 = func(tempX + (h / 2), tempY + ((h * k2) / 2));
	k4 = func(tempX + h, tempY + (h * k3));

	return (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

void runge_method(FunctionPointer func, double a, double b, double N, double Y0)
{
	double h = (b - a) / N;
	double tempX = a;
	double tempY = Y0;

	cout << "\nRozwiazanie zadania metada Rungego-Kutty drugiego rzedu\n";

	for (int i = 1; i <= N; i++)
	{
		double X = tempX + h;
		double Y = tempY + h * RK2(func, tempX, tempY, h);
		cout << "x" << i << " = " << X << endl;
		cout << "y" << i << " = " << Y << endl;
		tempX = X;
		tempY = Y;
	}
	cout << "\nRozwiazanie w koncowym punkcie: " << tempY << endl;

	cout << "\nRozwiazanie zadania metada Rungego-Kutty czwartego rzedu\n";

	tempX = a;
	tempY = Y0;

	for (int i = 1; i <= N; i++)
	{
		double X = tempX + h;
		double Y = tempY + h * RK4(func, tempX, tempY, h);
		cout << "x" << i << " = " << X << endl;
		cout << "y" << i << " = " << Y << endl;
		tempX = X;
		tempY = Y;
	}
	cout << "\nRozwiazanie w koncowym punkcie: " << tempY << endl;
}

int main()
{
	double a = 0;
	double b = 0.3;
	double N = 3;
	double Y0 = 0.1;

	cout << "Warunek poczatkawy: y( " << a << " ) = " << Y0 << endl;
	cout << "Punkt koncowy: " << b << endl;
	cout << "Krok obliczen: " << (b - a) / N << "\n\n";

	euler_method(function, a, b, N, Y0);
	runge_method(function, a, b, N, Y0);

	return 0;
}