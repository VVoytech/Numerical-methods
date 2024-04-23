#include <iostream>
#include <cmath>
using namespace std;

typedef double (*FunctionPointer)(double);

// Metoda prostokątów
double rectangle_method(FunctionPointer func, double a, double b, int n) {
    double dx = (b - a) / n;
    double integral = 0;
    for (int i = 0; i < n; ++i) {
        double x = a + i * dx;
        integral += func(x + (dx / 2));
    }
    return integral * dx;
}

// Metoda trapezów
double trapezoid_method(FunctionPointer func, double a, double b, int n) {
    double dx = (b - a) / n;
    double integral = 0;
    for (int i = 0; i < n; ++i) {
        double x = a + i * dx;
        integral += (((x + dx) - x) / 2) * (func(x) + func(x + dx));
    }
    return integral;
}

// Metoda parabol
double parabolic_method(FunctionPointer func, double a, double b, int n) {
    double dx = (b - a) / n;
    double integral = 0;
    integral += (((b - a) / 6) * (func(a) + 4 * func((a + b) / 2) + func(b)));
    return integral;
}

// Dwa węzły
double two_node(FunctionPointer func, double a, double b)
{
    double integral = 0;
    double X[2] = { -(sqrt(3.0) / 3.0), sqrt(3.0) / 3.0 };
    double A[2] = { 1.0, 1.0 };

    for (int i = 0; i < 2; i++)
    {
        integral += A[i] * func(((a + b) / 2.0) + ((b - a) / 2.0) * X[i]);
    }
    integral *= (b - a) / 2.0;

    return integral;
}

// Trzy węzły
double three_node(FunctionPointer func, double a, double b)
{
    double integral = 0;
    double X[3] = { -sqrt(3.0/5.0), 0, sqrt(3.0/5.0) };
    double A[3] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };

    for (int i = 0; i < 3; i++)
    {
        integral += A[i] * func(((a + b) / 2.0) + ((b - a) / 2.0) * X[i]);
    }
    integral *= (b - a) / 2.0;

    return integral;
}

//Cztery węzły
double four_node(FunctionPointer func, double a, double b)
{
    double integral = 0;
    double X[4] = { -(1.0 / 35.0) * sqrt(525.0 + 70.0 * sqrt(30.0)), -(1.0 / 35.0) * sqrt(525.0 - 70.0 * sqrt(30.0)), (1.0 / 35.0) * sqrt(525.0 - 70.0 * sqrt(30.0)), (1.0 / 35.0) * sqrt(525.0 + 70.0 * sqrt(30.0)) };
    double A[4] = { (1.0 / 36.0) * (18.0 - sqrt(30.0)), (1.0 / 36.0) * (18.0 + sqrt(30.0)), (1.0 / 36.0) * (18.0 + sqrt(30.0)), (1.0 / 36.0) * (18.0 - sqrt(30.0)) };

    for (int i = 0; i < 4; i++)
    {
        integral += A[i] * func(((a + b) / 2.0) + ((b - a) / 2.0) * X[i]);
    }
    integral *= (b - a) / 2.0;

    return integral;
}

void calculate_integral(FunctionPointer func, double a, double b, int n, string func_name, double accurate) {
    cout << "Wzor calkowanej funkcji: " << func_name << endl;
    cout << "Przedzial calkowania: " << a << " - " << b << endl;
    cout << "Liczba przedzialow: " << n << endl;

    double rect_integral = rectangle_method(func, a, b, n);
    double trap_integral = trapezoid_method(func, a, b, n);
    double para_integral = parabolic_method(func, a, b, n);
    double two_node_integral = two_node(func, a, b);
    double three_node_integral = three_node(func, a, b);
    double four_node_integral = four_node(func, a, b);

    cout << "Wynik obliczony metoda prostokatow: " << rect_integral << endl;
    cout << "Wynik obliczony metoda trapezow: " << trap_integral << endl;
    cout << "Wynik obliczony metod parabol: " << para_integral << endl;

    cout << "Wynik obliczony dla 2 wezlow: " << two_node_integral << endl;
    cout << "Wynik obliczony dla 3 wezlow: " << three_node_integral << endl;
    cout << "Wynik obliczony dla 4 wezlow: " << four_node_integral << endl;

    cout << "Wynik dokladny to: " << accurate << endl;

    cout << endl;
}

double function1(double x) {
    return sin(x);
}

double function2(double x) {
    return x * x + 2 * x + 5;
}

double function3(double x) {
    return exp(x);
}

int main()
{
    calculate_integral(function1, 0.5, 2.5, 20, "sin(x)", 1.67872617744);
    calculate_integral(function2, 0.5, 5, 20, "x^2 + 2x +5", 88.875);
    calculate_integral(function3, 0.5, 5, 20, "exp(x)", 146.764437832);

    return 0;
}
