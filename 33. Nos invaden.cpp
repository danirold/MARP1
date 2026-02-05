// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool resuelveCaso() {
    int N; cin >> N;

    if (!std::cin)
        return false;

    vector<int> enemigos(N);
    vector<int> defensas(N);

    for (int i = 0; i < N; ++i) cin >> enemigos[i];
    for (int i = 0; i < N; ++i) cin >> defensas[i];
    sort(enemigos.begin(), enemigos.end());
    sort(defensas.begin(), defensas.end());

    int sol = 0;
    int i = 0; int j = 0;
    while (i < N && j < N) {
        if (enemigos[i] > defensas[j]) {
            ++j;
        }
        else {
            sol++;
            i++;
            j++;
        }
    }

    cout << sol << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}