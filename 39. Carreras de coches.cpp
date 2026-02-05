// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

void resuelveCaso() {
    int tam; cin >> tam;
    int suma; cin >> suma;
    vector<int> valores(tam);
    for (int i = 0; i < tam; ++i) cin >> valores[i];
    sort(valores.begin(), valores.end());

    deque<int> num;
    for (int i = 0; i < tam; ++i) num.push_back(valores[i]);

    int sol = 0;
    while (num.size() > 1) {
        if (num.front() + num.back() >= suma) {
            sol++;
            num.pop_back();
        }
        num.pop_front();
    }

    cout << sol << '\n';
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}
