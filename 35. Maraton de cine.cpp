// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct tPeli {
    int c; int f;
};
bool operator<(tPeli const& p1, tPeli const& p2) {
    return p1.f < p2.f;
}

bool resuelveCaso() {
    int num_pelis;
    cin >> num_pelis;

    if (num_pelis == 0)
        return false;

    vector<tPeli> pelis(num_pelis);
    for (int i = 0; i < num_pelis; ++i) {
        int h; char c; int m; int d;
        cin >> h >> c >> m >> d;
        pelis[i] = { h * 60 + m, h * 60 + 10 + m + d};
    }
    sort(pelis.begin(), pelis.end());

    int sol = 1; int fin = pelis[0].f;
    for (int i = 1; i < num_pelis; ++i) {
        if (pelis[i].c >= fin) {
            sol++;
            fin = pelis[i].f;
        }
    }

    cout << sol << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
