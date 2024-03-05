#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

double newton_interpolation(const vector<double>& x, const vector<double>& values, double Xi) {
    double result = 0;
    for (int i = 1; i < x.size() && i <= Xi; ++i) {
        double Pk = 1;
        for (int j = 0; j < i; j++)
        {
            Pk = Pk * (Xi - x[j]);
        }

        double Bk = 0;
        for (int j = 0; j <= i; j++)
        {
            double Bk_divider = 1;
            for (int k = 0; k <= i; k++)
            {
                if (k == j) k++;
                if (k > i) break;
                Bk_divider = Bk_divider * (x[j] - x[k]);
            }
            Bk = Bk + (values[j] / Bk_divider);
        }
        result = result + (Pk * Bk);
    }
    result = result + (1 * values[0]);

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

int main()
{

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
    double result = newton_interpolation(x, values, n);
    cout << "Wartosc wielomianu Newton'a w danym punkcie: " << result << "\n\n";

    return 0;
}