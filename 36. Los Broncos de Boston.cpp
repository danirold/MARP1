// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool resuelveCaso() {
    int num_partidos; cin >> num_partidos;

    if (num_partidos == 0)
        return false;

    vector<int> rivales(num_partidos);
    vector<int> Broncos(num_partidos);
    for (int i = 0; i < num_partidos; ++i) cin >> rivales[i];
    for (int i = 0; i < num_partidos; ++i) cin >> Broncos[i];
    sort(rivales.begin(), rivales.end());
    sort(Broncos.begin(), Broncos.end());

    int sol = 0;
    for (int i = 0; i < num_partidos; ++i) {
        if (Broncos[num_partidos - 1 - i] > rivales[i]) {
            sol += Broncos[num_partidos - 1 - i] - rivales[i];
        }
    }

    cout << sol << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
