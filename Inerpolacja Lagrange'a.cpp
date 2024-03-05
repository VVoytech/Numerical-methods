#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

double lagrange_interpolation(const vector<double>& x, const vector<double>& values, double Xi) {
    double result = 0;
    for (int i = 0; i < x.size(); ++i) {
        double term = values[i];
        for (int j = 0; j < x.size(); ++j) {
            if (j != i) {
                term *= (Xi - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

string* split(string s, string delimiter) {

    int pos_start = 0;
    int pos_end;
    int delim_len = delimiter.length();

    string token;
    static string buffer[3];

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

pair<vector<double>, vector<double>> read_data_from_file(const string& filename) {
    vector<double> x, y;
    ifstream file(filename);
    
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            string* buffer = split(line, " ");
            x.push_back(stod(buffer[0]));
            y.push_back(stod(buffer[1]));

        }
        file.close();
    }
    else cout << "Nie mozna otworzyc!";

    return make_pair(x, y);
}

pair<vector<double>, vector<double>> read_data_zad_2(double tab[]) {
    vector<double> x, y;
    for (int i = 0; i < 3; i++)
    {
        x.push_back(tab[i]);
        y.push_back(cbrt(tab[i]));
    }

    return make_pair(x, y);
}

int main() {
    
    cout << "Zadanie 1\n";

    auto data = read_data_from_file("plik.txt");    //w wierszu w pliku tekstowym znajduje się x oraz wartość a deliminatorem jest spacja
    vector<double> x = data.first;
    vector<double> values = data.second;

    cout << "Liczba wezlow: " << x.size() << endl;
    cout << "Dane: wezly interpolacji i wartosci funkcji w wezlach:" << endl;
    for (size_t i = 0; i < x.size(); ++i) {
        cout << "Wezel: " << x[i] << " | Wartosc funkcji: " << values[i] << endl;
    }
    cout << endl;

    double n;
    cout << "Podaj punkt, w ktorym chcesz obliczyc wartosc wielomianu: ";
    cin >> n;
    double result = lagrange_interpolation(x, values, n);
    cout << "Wartosc wielomianu Lagrange'a w danym punkcie: " << result << "\n\n";

    cout << "\nZadanie 2\n";
    double tab[4] = { 27, 64, 125, 216 };
    auto data2 = read_data_zad_2(tab);
    vector<double> x_zad2 = data2.first;
    vector<double> values_zad2 = data2.second;
    n = 50;
    double result_zad2 = lagrange_interpolation(x_zad2, values_zad2, n);
    cout << "Wartosc wielomianu Lagrange'a w punkcie 50 wynosi: " << result_zad2 << endl;

    return 0;
}
