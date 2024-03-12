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

    file.close();
    return tabA;
}



void wypisz(const vector<double>& tabB, const vector<vector<double>>& tabA)
{
    for (int i = 0; i < tabA.size(); i++)
    {
        for (int j = 0; j < tabA.size(); j++)
        {
            cout << tabA[i][j] << " ";
        }
        cout << tabB[i] << endl;
    }
}

void gauss(vector<double> tabB, vector<vector<double>> tabA)
{
    for (int k = 0; k < tabA.size() - 1; k++)
    {
        for (int i = k + 1; i < tabA.size(); i++)
        {
            double m = tabA[i][k] / tabA[k][k];
            // cout << m << endl;
            for (int j = 0; j < tabA.size() ; j++)
            {
                tabA[i][j] = tabA[i][j] - tabA[k][j] * m;
            }
            tabB[i] = tabB[i] - tabB[k] * m;
        }
    }
    cout << "\n\nMaciez po sprowadzeniu do postaci gornie trojkatnej:\n";
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
}

int main()
{

    cout << "Wczytana maciez:\n";

    vector<double> tabB;
    vector<vector<double>> tabA;

    tabB = loadB("B1.txt");
    tabA = loadA("A1.txt");
    wypisz(tabB, tabA);
    gauss(tabB, tabA);


    return 0;
}