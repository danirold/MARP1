// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool resuelveCaso() {
    int jugadores, camisetas;
    cin >> jugadores >> camisetas;

    if (!std::cin)
        return false;

    vector<int> jug(jugadores);
    vector<int> cam(camisetas);
    for (int i = 0; i < jugadores; ++i) cin >> jug[i];
    for (int i = 0; i < camisetas; ++i) cin >> cam[i];
    sort(jug.begin(), jug.end());
    sort(cam.begin(), cam.end());

    int sol = 0; 
    int i = 0; int j = 0;
    while (i < jugadores && j < camisetas) {
        if (jug[i] > cam[j]) {
            ++j;
        }
        else if (jug[i] == cam[j]) {
            ++sol; ++i; ++j;
        }
        else if (jug[i] + 1 == cam[j]) {
            ++sol; ++i; ++j;
        }
        else ++i;
    }

    cout << jugadores - sol << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}