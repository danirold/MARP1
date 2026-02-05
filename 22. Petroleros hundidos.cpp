#include <vector>
#include <iostream>
using namespace std;

class ConjuntosDisjuntos {
protected:
	int ncjtos;  // número de conjuntos disjuntos
	mutable std::vector<int> p;  // enlace al padre
	std::vector<int> tam;  // tamaño de los árboles
	int maxTam;
	int numManchas;
public:

	// crea una estructura de partición con los elementos 0..N-1,
	// cada uno en un conjunto, partición unitaria
	ConjuntosDisjuntos(int N) : ncjtos(N), p(N), tam(N, 1), maxTam(1), numManchas(N) {
		for (int i = 0; i < N; ++i) {
			p[i] = i;
		}
	}

	ConjuntosDisjuntos() : ncjtos(0), p(0), tam(0), maxTam(0), numManchas(0) {}

	//  devuelve el representante del conjunto que contiene a a
	int buscar(int a) const {
		if (p.at(a) == a) // es una raíz
			return a;
		else
			return p[a] = buscar(p[a]);
	}

	// unir los conjuntos que contengan a a y b
	void unir(int a, int b) {
		int i = buscar(a);
		int j = buscar(b);
		if (i == j) return;
		if (tam[i] > tam[j]) { // i es la raíz del árbol más grande
			tam[i] += tam[j]; p[j] = i;
			if (tam[i] > maxTam) maxTam = tam[i];
		}
		else {
			tam[j] += tam[i]; p[i] = j;
			if (tam[j] > maxTam) maxTam = tam[j];
		}
		--ncjtos;
	}

	// devuelve si a y b están en el mismo conjunto
	bool unidos(int a, int b) const {
		return buscar(a) == buscar(b);
	}

	// devuelve el número de elementos en el conjunto de a
	int cardinal(int a) const {
		return tam[buscar(a)];
	}

	// devuelve el número de conjuntos disjuntos
	int num_cjtos() const { return ncjtos; }

	int tamMaximo() const { return maxTam; }

	int nuevoConjunto() {
		++ncjtos;
		++numManchas;
		p.resize(numManchas);
		p[numManchas - 1] = numManchas - 1;
		tam.resize(numManchas);
		tam[numManchas - 1] = 1;
		if (maxTam < 1) maxTam = 1;
		return numManchas - 1;
	}

};

bool resuelveCaso() {
	int numF, numC, numNuevas, fila, col, tam;
	cin >> numF;
	if (!cin)return false;
	cin >> numC;
	vector<vector<int>> manchas(numF, vector<int>(numC)); //"Imagen" de las manchas
	char c;
	ConjuntosDisjuntos cd;
	//Lectura de las manchas
	c = getchar();
	for (int i = 0; i < numF; ++i) {
		for (int j = 0; j < numC; ++j) {
			c = getchar();
			if (c == '#') {
				manchas[i][j] = cd.nuevoConjunto();
				if (i > 0 && manchas[i - 1][j] != -1 && !cd.unidos(manchas[i][j], manchas[i - 1][j])) cd.unir(manchas[i][j], manchas[i - 1][j]);
				if (i > 0 && j > 0 && manchas[i - 1][j - 1] != -1 && !cd.unidos(manchas[i][j], manchas[i - 1][j - 1])) cd.unir(manchas[i][j], manchas[i - 1][j - 1]);
				if (i > 0 && j < manchas[i].size() - 1 && manchas[i - 1][j + 1] != -1 && !cd.unidos(manchas[i][j], manchas[i - 1][j + 1])) cd.unir(manchas[i][j], manchas[i - 1][j + 1]);
				if (j > 0 && manchas[i][j - 1] != -1 && !cd.unidos(manchas[i][j], manchas[i][j - 1])) cd.unir(manchas[i][j], manchas[i][j - 1]);
			}
			else	manchas[i][j] = -1;
		}
		c = getchar();
	}
	cout << cd.tamMaximo() << ' ';
	cin >> numNuevas;
	for (int k = 0; k < numNuevas; ++k) {
		cin >> fila >> col;
		int i = fila - 1;
		int j = col - 1;
		if (manchas[i][j] == -1) {
			manchas[i][j] = cd.nuevoConjunto();
			if (i > 0 && manchas[i - 1][j] != -1 && !cd.unidos(manchas[i][j], manchas[i - 1][j]))cd.unir(manchas[i][j], manchas[i - 1][j]);
			if (i < manchas.size() - 1 && manchas[i + 1][j] != -1 && !cd.unidos(manchas[i][j], manchas[i + 1][j])) cd.unir(manchas[i][j], manchas[i + 1][j]);
			if (j > 0 && manchas[i][j - 1] != -1 && !cd.unidos(manchas[i][j], manchas[i][j - 1])) cd.unir(manchas[i][j], manchas[i][j - 1]);
			if (j < manchas[i].size() - 1 && manchas[i][j + 1] != -1 && !cd.unidos(manchas[i][j], manchas[i][j + 1])) cd.unir(manchas[i][j], manchas[i][j + 1]);
			if (i > 0 && j > 0 && manchas[i - 1][j - 1] != -1 && !cd.unidos(manchas[i][j], manchas[i - 1][j - 1])) cd.unir(manchas[i][j], manchas[i - 1][j - 1]);
			if (i > 0 && j < manchas[i].size() - 1 && manchas[i - 1][j + 1] != -1 && !cd.unidos(manchas[i][j], manchas[i - 1][j + 1])) cd.unir(manchas[i][j], manchas[i - 1][j + 1]);
			if (i < manchas.size() - 1 && j > 0 && manchas[i + 1][j - 1] != -1 && !cd.unidos(manchas[i][j], manchas[i + 1][j - 1])) cd.unir(manchas[i][j], manchas[i + 1][j - 1]);
			if (i < manchas.size() - 1 && j < manchas[i].size() - 1 && manchas[i + 1][j + 1] != -1 && !cd.unidos(manchas[i][j], manchas[i + 1][j + 1])) cd.unir(manchas[i][j], manchas[i + 1][j + 1]);
		}
		cout << cd.tamMaximo() << ' ';
	}

	cout << '\n';
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}
