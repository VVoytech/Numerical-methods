#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

typedef double (*FunctionPointer)(double x);

int I = 100;

double func1(double x) { return cos(pow(x, 3) - 2 * x); }

double func2(double x) { return -pow(x, 3) + 10 * x + 5; }

double func3(double x) { return pow(x, 4) - 2 * pow(x, 2) - 5; }

void write_function(FunctionPointer func)
{
    if (func == func1) cout << "f(x) = cos(x^3 - 2x)\n\n";

    else if (func == func2) cout << "f'(x) = -x^3 + 10x + 5\n\n";

    else if (func == func3) cout << "f'(x) = x^4 - 2x^2 - 5\n\n";

    else cout << "Brak wzoru\n\n";
}

void bisection_method(FunctionPointer func, double a, double b, double epsilon)
{
    double x0;
    int i;
    
    cout << "Metoda bisekcji:\n";
    cout << "Przedzial: [" << a << ", " << b << "]\n";
    cout << "Zadana dokladnosc = " << epsilon << "\n\n";
    cout << setw(18) << "a" << setw(15) << "b" << setw(15) << "f(a)" << setw(15) << "f(b)" << setw(15) << "x0" << setw(15) << "f(x0)" << setw(15) << "f(a) * f(x0)" << "\n\n";

    for(i = 1; i <= I; i++)
    {
        x0 = (a + b) / 2;
        cout << setw(3) << i << setw(15) << a << setw(15) << b << setw(15) << func(a) << setw(15) << func(b) << setw(15) << x0 << setw(15) << func(x0) << setw(15) << func(a) * func(x0) << "\n";

        if (func(a) * func(x0) < 0) b = x0;
        else a = x0;

        if (fabs(func(x0)) < epsilon) break;
    }

    cout << "Wynik koncowy: x = " << x0 << "\n";
    cout << "Ilosc iteracji: " << i << "\n\n";
}

void regula_falsi(FunctionPointer func, double a, double b, double epsilon)
{
    double x1;
    int i;

    cout << "Regula falsi:\n";
    cout << "Przedzial: [" << a << ", " << b << "]\n";
    cout << "Zadana dokladnosc = " << epsilon << "\n\n";
    cout << setw(18) << "a" << setw(15) << "b" << setw(15) << "f(a)" << setw(15) << "f(b)" << setw(15) << "x1" << setw(15) << "f(x1)" << setw(15) << "f(a) * f(x1)" << "\n\n";

    for (i = 1; i <= I; i++)
    {
        x1 = a - (func(a) * (b - a)) / (func(b) - func(a));
        cout << setw(3) << i << setw(15) << a << setw(15) << b << setw(15) << func(a) << setw(15) << func(b) << setw(15) << x1 << setw(15) << func(x1) << setw(15) << func(a) * func(x1) << "\n";
        
        if (func(x1) * func(a) < 0) b = x1;
        else a = x1;

        if (fabs(func(x1)) < epsilon) break;
    }

    cout << "Wynik koncowy: x = " << x1 << "\n";
    cout << "Ilosc iteracji: " << i << "\n\n";
}

int main()
{
    int a = 0;
    int b = 2;
    double epsilon = 0.01;

    write_function(func1);
    bisection_method(func1, a, b, epsilon);
    regula_falsi(func1, a, b, epsilon);

    a = 0;
    b = 4;

    write_function(func2);
    bisection_method(func2, a, b, epsilon);
    regula_falsi(func2, a, b, epsilon);

    a = 0;
    b = 3;

    write_function(func3);
    bisection_method(func3, a, b, epsilon);
    regula_falsi(func3, a, b, epsilon);

    return 0;
}

