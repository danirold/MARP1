// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

struct tInfo {
    int comienzo; 
    int final;
};
bool operator<(tInfo const& intervalo1, tInfo const& intervalo2) {
    return intervalo1.comienzo < intervalo2.comienzo || (intervalo1.comienzo == intervalo2.comienzo && intervalo1.final < intervalo2.final);
}

bool resuelveCaso() {
    int comienzo, final, N;
    cin >> comienzo >> final >> N;

    if (comienzo == 0 && final == 0 && N == 0)
        return false;

    vector<tInfo> valores(N);
    for (int i = 0; i < N; ++i) {
        int com, fin;
        cin >> com >> fin;
        valores[i] = { com, fin};
    }

    sort(valores.begin(), valores.end());

    int cont = 1;
    int i = 0;
    int max = 0;
    int ind = -1;

    while (i < N && valores[i].comienzo <= comienzo) {
        if (valores[i].final > comienzo) {
            if (valores[i].final > max) {
                max = valores[i].final;
                ind = i;
            }
        }
        ++i;
    }

    i = ind;
    bool imposible = false;

    if (ind == -1) imposible = true;

    while (i < N && max < final && !imposible) {
        bool imposible_aux = true;
        int aux = i + 1;
        ind = aux;
        while (aux < N && valores[aux].comienzo <= valores[i].final) {
            imposible_aux = false;
            if (valores[aux].final > max) {
                max = valores[aux].final;
                ind = aux;
            }
            aux++;
        }
        imposible = imposible_aux;
        cont++;
        i = ind;
    }

    if (max < final || imposible) cout << "Imposible\n";
    else cout << cont << '\n';
    
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
