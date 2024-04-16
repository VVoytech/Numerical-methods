#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int N = 0;
int iter = 10;
int istotne = 0;

vector<double> tabB;
vector<double> tabX1;
vector<double> tabX2;
vector<double> tabBlad;
vector<vector<double>> tabA;
vector<vector<double>> tabU;
vector<vector<double>> tabL;
vector<vector<double>> tabD;
vector<vector<double>> tabM;

string* split(string s, string delimiter) {

    int pos_start = 0;
    int pos_end;
    int delim_len = delimiter.length();

    string token;
    string* buffer = new string[N];

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

void wypisz_bezX(vector<vector<double>> tabA)
{
    for (int i = 0; i < tabA.size(); i++)
    {
        for (int j = 0; j < tabA.size(); j++)
        {
            cout << tabA[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

void wypisz_koniec(vector<double> tabA)
{
    for (int i = 0; i < tabA.size(); i++)
    {
        cout << tabA[i] << "\n";
    }
    cout << endl;
}

bool czyIstotna()
{
    for (int i = 0; i < tabA.size(); i++)
    {
        double temp = 0;
        for (int j = 0; j < tabA.size(); j++)
        {
            if (i == j)
            {
                j++;
                if (j >= tabA.size()) break;
            }
            temp += tabA[i][j];
        }
        if (tabA[i][i] >= temp)
        {
            istotne++;
        }
        if (tabA[i][i] > temp)
        {
            return 1;
        }
    }
    if(istotne == tabA.size())
    {
        return 1;
    }
    return 0;
}

void matrix_U_L_D()
{
    tabL = tabA;
    for (int i = 0; i < tabL.size(); i++)
    {
        for (int j = i; j < tabL.size(); j++)
        {
            tabL[i][j] = 0;
        }
    }
    cout << "Macierz L:\n";
    wypisz_bezX(tabL);

    tabU = tabA;
    for (int i = tabU.size() - 1; i >= 0; i--)
    {
        for (int j = i; j >= 0; j--)
        {
            tabU[i][j] = 0;
        }
    }
    cout << "Macierz U:\n";
    wypisz_bezX(tabU);

    for(int j = 0; j < tabA.size(); j++)
    {
        vector<double> row;
        for (int i = 0; i < N; i++)
        {
            row.push_back(0);
        }
        tabD.push_back(row);
    }

    for (int i = 0; i < tabA.size(); i++)
    {
        tabD[i][i] = 1 / tabA[i][i];
    }
    cout << "Macierz D^-1:\n";
    wypisz_bezX(tabD);

    tabM = tabA;
    for (int i = 0; i < tabA.size(); i++)
    {
        for (int j = 0; j < tabA.size(); j++)
        {
            if (i == j)
            {
                tabM[i][j] = 0;
            }
            else
            {
                tabM[i][j] = -(tabA[i][j] * tabD[i][i]);
            }
        }
    }
}

void jacobi_zad1()
{
    matrix_U_L_D();

    tabX1 = tabB;
    tabX2 = tabB;
    tabBlad = tabB;

    for (int i = 0; i < tabA.size(); i++)
    {
        tabX1[i] = 0;
        tabX2[i] = 0;
        tabBlad[i] = 0;
    }

    for (int k = 0; k < iter; k++) {
        for (int i = 0; i < tabA.size(); i++) {
            tabX2[i] = tabD[i][i] * tabB[i];
            for (int j = 0; j < tabA.size(); j++)
                tabX2[i] += tabM[i][j] * tabX1[j];
        }
        for (int i = 0; i < tabA.size(); i++)
            tabX1[i] = tabX2[i];
    }

    cout << "Ilosc wykonanych iteracji: " << iter << "\n";
    cout << "Wynik\n";
    for (int i = 0; i < tabA.size(); i++)
    {
        cout << "x" << i << " = " << tabX1[i] << "\n";
    }
    cout << "\n";
}

void jacobi_zad2(double blad)
{
    iter = 100;
    int k = 0;

    for (int i = 0; i < tabA.size(); i++)
    {
        tabX1[i] = 0;
        tabX2[i] = 0;
    }

    for (k = 0; k < iter; k++)
    {
        istotne = 0;
        for (int i = 0; i < tabA.size(); i++)
        {
            tabX2[i] = tabD[i][i] * tabB[i];
            for (int j = 0; j < tabA.size(); j++)
            {
                tabX2[i] += tabM[i][j] * tabX1[j];
                tabBlad[i] = tabX1[i];
            }
        }
        for (int i = 0; i < tabA.size(); i++)
        {
            if (abs(tabX2[i] - tabX1[i]) < blad)
            {
                istotne++;
            }
            
            tabX1[i] = tabX2[i];
        }
        if (istotne == tabA.size())
        {
            cout << "Ilosc wykonanych iteracji: " << k << "\n";
            cout << "Przyjety blad: " << blad << "\n";
            break;
        }
    }

    setprecision(10);
    cout << "Wynik:\n";
    for (int i = 0; i < tabA.size(); i++)
    {
        double blad2 = abs(tabBlad[i] - tabX1[i]);
        cout << "x" << i << " = " << tabX1[i] << ", blad: " << blad2 << "\n";
    }
    cout << "\n";
}

int main()
{
    tabB = loadB("B1.txt");
    tabA = loadA("A1.txt");
    cout << "Wczytana z pliku macierz rozszerzona:\n";
    wypisz(tabB, tabA);

    if(czyIstotna()) cout << "Macierz jest slabo dominujaca\n";
    else
    {
        cout << "Macierz nie jest slabo dominujaca\n";
        return 0;
    }

    cout << "Zadanie 1:\n";
    jacobi_zad1();

    cout << "Zadanie2:\n";
    jacobi_zad2(0.001);
    jacobi_zad2(0.0001);

    return 0;
}