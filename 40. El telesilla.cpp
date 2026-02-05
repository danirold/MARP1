// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

bool resuelveCaso() {
    int peso_max; cin >> peso_max;
    int tam; cin >> tam;

    if (!std::cin)
        return false;

    vector<int> valores(tam);
    for (int i = 0; i < tam; ++i) cin >> valores[i];
    sort(valores.begin(), valores.end());

    deque<int> num;
    for (int i = 0; i < tam; ++i) num.push_back(valores[i]);

    int sol = 0;
    while (num.size() > 1) {
        if (num.front() + num.back() <= peso_max) {
            num.pop_front();
        }
        num.pop_back();
        sol++;
    }
    
    if(num.size() == 1) sol++;

    cout << sol << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}