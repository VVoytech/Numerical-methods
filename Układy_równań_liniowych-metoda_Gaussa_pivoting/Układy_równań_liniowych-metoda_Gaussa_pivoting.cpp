#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int N = 0;

string* split(string s, string delimiter) {

    int pos_start = 0;
    int pos_end;
    int delim_len = delimiter.length();

    string token;
    string* buffer = new string[N];
    //static string buffer[100];

    int idx = 0;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {

        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;

        buffer[idx] = token;
        idx++;

    }

    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    buffer[idx] = token;

    return buffer;

}

vector<double> loadB(const string& filename)
{
    ifstream file(filename);

    string line;
    vector<double> tabB;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            tabB.push_back(stod(line));
            N++;
        }
    }
    else cout << "Nie mozna otworzyc!\n";

    file.close();
    return tabB;
}

vector<vector<double>> loadA(const string& filename)
{
    ifstream file(filename);

    vector<vector<double>> tabA;
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<double> row;
            string* buffer = split(line, " ");
            for (int i = 0; i < N; i++)
            {
                row.push_back(stod(buffer[i]));
            }
            tabA.push_back(row);
        }
    }
    else cout << "Nie mozna otworzyc!\n";

    file.close();
    return tabA;
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

void gauss_partial_pivoting(vector<double> tabB, vector<vector<double>> tabA)
{
    for (int k = 0; k < tabA.size() - 1; k++)
    {
        double temp = tabA[k][k];
        int tempY = k;
        for (int h = k; h < tabA.size(); h++)
        {
            if (abs(temp) < abs(tabA[h][k]))
            {
                temp = tabA[h][k];
                tempY = h;
            }
        }
        tabA[k].swap(tabA[tempY]);
        swap(tabB[k],tabB[tempY]);

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
    cout << "\nMaciez po sprowadzeniu do postaci gornie trojkatnej:\n";
    wypisz(tabB, tabA);


    for (int i = tabA.size() - 1; i >= 0; i--)
    {

        double x = tabB[i] / tabA[i][i];

        cout << "\nx" << i << " = " << x;

        for (int j = i - 1; j >= 0; j--)
        {
            tabB[j] -= tabA[j][i] * x;
            tabA[j][i] = 0;
        }
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
    cout << "\n\nMaciez po sprowadzeniu do postaci gornie trojkatnej:\n";
    wypisz(tabB, tabA);

    //double *x = new double[tabA.size()];
    for (int i = tabA.size() - 1; i >= 0; i--)
    {

        double x = tabB[i] / tabA[i][i];

        cout << "\nx" << kolumny[i] << " = " << x;

        for (int j = i - 1; j >= 0; j--)
        {
            tabB[j] -= tabA[j][i] * x;
            tabA[j][i] = 0;
        }
    }
    //int a = tabA.size()-1;
    //for (int i = tabA.size() - 1; i >= 0; i--)
    //{
    //    cout << "\nx" << i << " = " << x[kolumny[abs(i-a)]];
    //}
    cout << endl;
}

int main()
{
    int a;

    cout << "Zadanie 1:\n";
    vector<double> tabB;
    vector<vector<double>> tabA;

    tabB = loadB("B1.txt");
    tabA = loadA("A1.txt");

    cout << "Wczytana maciez przed obliczeniami:\n";
    wypisz(tabB, tabA);

    cout << "Rownanie rozwiazane metoda eliminacji Gaussa z wyborem czesciowym:\n";
    gauss_partial_pivoting(tabB, tabA);

    cout << "\nZadanie 2:\n";
    cout << "Wczytana maciez przed obliczeniami:\n";
    wypisz(tabB, tabA);
    cout << "Rownanie rozwiazane metoda eliminacji Gaussa-Crouta:\n";
    gauss_crout(tabB, tabA);

    return 0;
}