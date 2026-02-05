// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

int recorrido_profund(vector<vector<char>> const& matriz, vector<vector<bool>> & visit, int i, int j, int const& fil, int const& col) {
    int sol = 1;
    visit[i][j] = true;
    //Comprobamos las cuatro direcciones
    int i1 = i + 1; int j1 = j;  // Uno a la dcha
    if (0 <= i1 && i1 < fil && 0 <= j1 && j1 < col && matriz[i1][j1] == '#' && !visit[i1][j1]) {
        sol += recorrido_profund(matriz, visit, i1, j1, fil, col);
    }

    int i2 = i - 1; int j2 = j;  // Uno a la izq
    if (0 <= i2 && i2 < fil && 0 <= j2 && j2 < col && matriz[i2][j2] == '#' && !visit[i2][j2]) {
        sol += recorrido_profund(matriz, visit, i2, j2, fil, col);
    }

    int i3 = i; int j3 = j + 1;  // Uno abajo
    if (0 <= i3 && i3 < fil && 0 <= j3 && j3 < col && matriz[i3][j3] == '#' && !visit[i3][j3]) {
        sol += recorrido_profund(matriz, visit, i3, j3, fil, col);
    }

    int i4 = i; int j4 = j - 1;  // Uno arriba
    if (0 <= i4 && i4 < fil && 0 <= j4 && j4 < col && matriz[i4][j4] == '#' && !visit[i4][j4]) {
        sol += recorrido_profund(matriz, visit, i4, j4, fil, col);
    }

    return sol;
}

bool resuelveCaso() {
    int filas, columnas;
    cin >> filas >> columnas;

    if (!std::cin)
        return false;

    vector<vector<char>> matriz(filas, vector<char>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cin >> matriz[i][j];
        }
    }

    vector<vector<bool>> visit(filas, vector<bool>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            visit[i][j] = false;
        }
    }

    int num_manchas = 0;
    int mancha_mas_grande = 0;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (!visit[i][j] && matriz[i][j] == '#') {
                num_manchas++;
                int nueva_mancha = recorrido_profund(matriz, visit, i, j, filas, columnas);
                mancha_mas_grande = max(mancha_mas_grande, nueva_mancha);
            }
        }
    }

    cout << num_manchas << ' ' << mancha_mas_grande << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}