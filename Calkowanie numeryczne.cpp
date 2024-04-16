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
        integral += func(x + (dx/2));
    }
    return integral * dx;
}

// Metoda trapezów
double trapezoid_method(FunctionPointer func, double a, double b, int n) {
    double dx = (b - a) / n;
    double integral = 0;
    for (int i = 0; i < n; ++i) {
        double x = a + i * dx;
        integral += (((x+dx) - x) / 2) * (func(x) + func(x+dx));
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

void calculate_integral(FunctionPointer func, double a, double b, int n, string func_name) {
    cout << "Wzor calkowanej funkcji: " << func_name << endl;
    cout << "Przedzial calkowania: " << a << " - " << b << endl;
    cout << "Liczba przedzialow: " << n << endl;

    double rect_integral = rectangle_method(func, a, b, n);
    double trap_integral = trapezoid_method(func, a, b, n);
    double para_integral = parabolic_method(func, a, b, n);

    cout << "Wynik obliczony metoda prostokatow: " << rect_integral << endl;
    cout << "Wynik obliczony metoda trapezow: " << trap_integral << endl;
    cout << "Wynik obliczony metod parabol: " << para_integral << endl;
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

int main() {
    calculate_integral(function1, 0.5, 2.5, 4, "sin(x)");
    calculate_integral(function2, 0.5, 5, 4, "x^2 + 2x + 5");
    calculate_integral(function3, 0.5, 5, 4, "exp(x)");

    return 0;
}
