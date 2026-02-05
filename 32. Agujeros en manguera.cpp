// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

bool resuelveCaso() {
    int num_agujeros, long_parche;
    cin >> num_agujeros >> long_parche;

    if (!std::cin)
        return false;

    vector<int> posiciones(num_agujeros);
    for (int i = 0; i < num_agujeros; ++i) {
        cin >> posiciones[i];
    }

    int sol = 1;
    int posAct = posiciones[0] + long_parche;
    for (int i = 1; i < num_agujeros; ++i) {
        if (posiciones[i] > posAct) {
            sol++;
            posAct = posiciones[i] + long_parche;
        }
    }

    cout << sol << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}