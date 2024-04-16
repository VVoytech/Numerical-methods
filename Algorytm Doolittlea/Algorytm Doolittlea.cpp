#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int N = 0;

vector<double> tabB;
vector<double> tabY;
vector<double> tabX;
vector<vector<double>> tabA;
vector<vector<double>> tabU;
vector<vector<double>> tabL;

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

void matrixUiL()
{
    for (int i = 0; i < tabL.size(); i++)
    {
        for (int k = i; k < tabL.size(); k++)
        {
            double temp = 0;
            for (int j = 0; j < i; j++)
            {
                temp += (tabL[i][j] * tabU[j][k]);
            }
            tabU[i][k] = tabA[i][k] - temp;
        }

        for (int k = i; k < tabL.size(); k++)
        {
            if (i == k) 
            {
                tabL[i][i] = 1;
            }
            else
            {
                double temp = 0;
                for (int j = 0; j < i; j++)
                {
                    temp += (tabL[k][j] * tabU[j][i]);
                }
                tabL[k][i] = ((tabA[k][i] - temp) / tabU[i][i]);
            }
        }
    }
}

void doolittle()
{

    for (int i = 0; i < tabA.size(); i++)
    {
        vector<double> row;
        for (int j = 0; j < tabA.size(); j++)
        {
            row.push_back(0);
        }
        tabL.push_back(row);
        tabU.push_back(row);
    }
    matrixUiL();

    cout << "Macierz U:\n";
    wypisz_bezX(tabU);
    cout << "Macierz L:\n";
    wypisz_bezX(tabL);

    for (int i = 0; i < tabB.size(); i++)
    {
        tabY.push_back(0);
        tabX.push_back(0);
    }
    tabY[0] = tabB[0];

    for (int i = 1; i < tabB.size(); i++)
    {
        double temp = 0;
        for (int j = 0; j <= i - 1; j++)
        {
            temp += tabL[i][j] * tabY[j];
        }
        tabY[i] = tabB[i] - temp;
    }
    cout << "Wektor Y:\n";
    wypisz_koniec(tabY);

    tabX[tabX.size()-1] = tabY[tabY.size() - 1] / tabU[tabU.size() - 1][tabU.size() - 1];
    for (int i = tabY.size() - 2; i >= 0; i--)
    {
        double temp = tabY[i];
        for (int j = i + 1; j <= tabY.size()-1; j++)
        {
            temp -= tabU[i][j] * tabX[j];
        }
        tabX[i] = (1 / tabU[i][i]) * temp;
    }

    cout << "Wyniki:\n";
    for (int i = 0; i < tabX.size(); i++)
    {
        cout << "X" << i << " = " << tabX[i] << "\n";
    }
}

int main()
{
    tabB = loadB("B1.txt");
    tabA = loadA("A1.txt");
    cout << "Wczytana z pliku macierz rozszerzona:\n";
    wypisz(tabB, tabA);

    doolittle();


    return 0;
}