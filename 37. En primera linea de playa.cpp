// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <utility>
#include<algorithm>

using namespace std;

bool resuelveCaso() {
    int N; cin >> N;

    if (N == 0)
        return false;

    vector<pair<int, int>> edificios(N);
    for (int i = 0; i < N; ++i) {
        cin >> edificios[i].first >> edificios[i].second;
    }
    sort(edificios.begin(), edificios.end());

    int sol = 1;
    int final = edificios[0].second;
    for (int i = 1; i < N; ++i) {
        if (edificios[i].first >= final) {
            sol++;
            final = edificios[i].second;
        }
        else final = min(edificios[i].second, final);
    }

    cout << sol << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
