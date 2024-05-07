#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int stopienWiel = 1;
int liczbaWez = 8;
int waga = 1;

vector<vector<double>> wezly{
	{1.0, 2.0},
	{2.0, 4.0},
	{3.0, 3.0},
	{4.0, 5.0},
	{5.0, 6.0},
	{6.0, 9.0},
	{7.0, 11.0},
	{8.0, 11.0}
};

vector<vector<double>> g;
vector<double> F;
vector<double> a;

void uzupelnianie()
{
	for (int i = 0; i <= stopienWiel; i++)
	{
		vector<double> row;
		for (int i = 0; i <= stopienWiel; i++)
		{
			row.push_back(0);
		}
		g.push_back(row);
		F.push_back(0);
		a.push_back(0);
	}
}

void wpisywanie_GiF()
{
	for (int k = 0; k <= stopienWiel; k++)
	{
		for (int j = 0; j <= stopienWiel; j++)
		{
			double temp = 0;
			for (int i = 0; i < liczbaWez; i++)
			{
				temp += pow(wezly[i][0], k) * pow(wezly[i][0], j) * waga;
			}
			g[k][j] = temp;
		}

		double temp = 0;
		for (int i = 0; i < liczbaWez; i++)
		{
			temp += pow(wezly[i][0], k) * wezly[i][1] * waga;
		}
		F[k] = temp;
	}
}

void wypisz(vector<double> tabB, vector<vector<double>> tabA)
{
	for (int i = 0; i < tabA.size(); i++)
	{
		for (int j = 0; j < tabA.size(); j++)
		{
			cout << tabA[i][j] << " ";
		}
		cout << tabB[i] << endl;
	}
	cout << endl;
}

void wypiszWezly(vector<vector<double>> wezly)
{
	for (int i = 0; i < liczbaWez; i++)
	{
		cout << "( " << wezly[i][0] << ", " << wezly[i][1] << " )\n";
	}
	cout << endl;
}

void wartosciWezly()
{
	for (int i = 0; i < liczbaWez; i++)
	{
		double temp = 0;
		for (int j = 0; j < stopienWiel; j++)
		{
			temp += a[j] * wezly[i][0];
		}
		temp += a[stopienWiel];

		cout << "( " << wezly[i][0] << ", " << temp << " )\n";
	}
	cout << endl;
}

void gauss_crout(vector<double> tabB, vector<vector<double>> tabA)
{
    vector<int> kolumny;
    for (int i = 0; i < tabA.size(); i++)
    {
        kolumny.push_back(i);
    }

    for (int k = 0; k < tabA.size() - 1; k++)
    {
        int tempY = k;
        double temp = tabA[k][k];
        for (int h = k + 1; h < tabA.size(); ++h) {
            if (abs(tabA[h][k]) > temp) {
                temp = abs(tabA[h][k]);
                tempY = h;
            }
        }
        if (tempY != k) {
            for (int i = 0; i < tabA.size(); ++i)
            {
                swap(tabA[i][k], tabA[i][tempY]);
            }
            swap(kolumny[k], kolumny[tempY]);
        }
        for (int i = k + 1; i < tabA.size(); i++)
        {
            double m = tabA[i][k] / tabA[k][k];

            for (int j = 0; j < tabA.size(); j++)
            {
                tabA[i][j] = tabA[i][j] - tabA[k][j] * m;
            }
            tabB[i] = tabB[i] - tabB[k] * m;
        }
    }

    for (int i = tabA.size() - 1; i >= 0; i--)
    {

        double x = tabB[i] / tabA[i][i];
		a[i] = x;

        cout << "a" << kolumny[i] << " = " << x << "\n";

        for (int j = i - 1; j >= 0; j--)
        {
            tabB[j] -= tabA[j][i] * x;
            tabA[j][i] = 0;
        }
    }
    cout << endl;
}

int main()
{
	uzupelnianie();
	wpisywanie_GiF();

	cout << "Liczba wezlow: " << liczbaWez << "\n";
	cout << "\nWspolczynnik wielomianu aproksymujacego:\n";
	gauss_crout(F, g);
	cout << "Podane wezly aproksymacji i wartosci w wezlach:\n";
	wypiszWezly(wezly);

	cout << "Obliczone wartosci funkcji aproksymujacej w podanych wezlach aproksymacji:\n";
	wartosciWezly();


	return 0;
}
