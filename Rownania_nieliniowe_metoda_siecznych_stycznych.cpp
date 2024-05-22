#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

typedef double (*FunctionPointer)(double x);

int I = 100;

double func1(double x) { return -pow(x, 3) + 10 * x + 5; }

double func2(double x) { return -3 * pow(x, 2) + 10; }

double func3(double x) { return pow(x, 4) - 2 * pow(x, 2) - 5; }

double func4(double x) { return 4 * pow(x, 3) - 4 * x; }

string write_function(FunctionPointer func)
{
    if (func == func1) return "f(x) = -x^3 + 10x + 5";

    else if (func == func2) return "f'(x) = -3x^2 + 10";

    else if (func == func3) return "f'(x) = x^4 - 2x^2 - 5";

    else if (func == func4) return "f'(x) = 4x^3 - 4x";

    else return "Brak wzoru";
}

void tangent_method(FunctionPointer func1, FunctionPointer func2, double x0, double epsilon)
{
    double x = x0;
    int i;

    cout << "Metoda stycznych: " << endl;

    for (i = 0; i < I; i++)
    {
        if (fabs(func1(x)) < epsilon)
        {
            break;
        }
        x -= (func1(x) / func2(x));

        cout << i + 1 << " iteracja, " << "x = " << x << endl;
    }
    cout << "Liczba iteracji: " << i << "\n\n";

}

void secant_method(FunctionPointer func,  double x0, double epsilon)
{
    double x = x0;
    int i;

    cout << "Metoda siecznych: " << endl;

    for (i = 0; i < I; i++)
    {
        if (fabs(func(x)) < epsilon)
        {
            break;
        }
        double xkm1 = x0 - 0.1;
        x -= func(x) * ((x - xkm1) / (func(x) - func(xkm1)));

        cout << i + 1 << " iteracja, " << "x = " << x << endl;
    }
    cout << "Liczba iteracji: " << i << endl;
}

int main()
{
    double x0 = 6;
    double epsilon = 0.01;

    cout << "Pierwsza funkcja:\n";
    cout << write_function(func1) << "\n";
    cout << "X0 = " << x0 << "\n";
    cout << "Przyjeta dokladnosc = " << epsilon << "\n\n";

    tangent_method(func1, func2, x0, epsilon);

    secant_method(func1, x0, epsilon);
    cout << "Wynik dokladny: 3.38762" << "\n";

    x0 = 3;
    epsilon = 0.01;

    cout << "\n#################################################################################\n";
    cout << "\nDruga funkcja:\n";
    cout << write_function(func3) << "\n";
    cout << "X0 = " << x0 << "\n";
    cout << "Przyjeta dokladnosc = " << epsilon << "\n\n";

    tangent_method(func3, func4, x0, epsilon);

    secant_method(func3, x0, epsilon);
    cout << "Wynik dokladny: 1.8572" << "\n";

    return 0;
}

