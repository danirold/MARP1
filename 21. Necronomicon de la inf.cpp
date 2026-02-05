// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Digrafo {

    int _V;   // número de vértices
    int _A;   // número de aristas
    std::vector<Adys> _ady;   // vector de listas de adyacentes

public:

    /**
     * Crea un grafo dirigido con V vértices.
     */
    Digrafo(int V) : _V(V), _A(0), _ady(_V) {}

    /**
     * Crea un grafo dirigido a partir de los datos en el flujo de entrada (si puede).
     * primer es el índice del primer vértice del grafo en el entrada.
     */
    Digrafo(std::istream& flujo, int primer = 0) : _A(0) {
        flujo >> _V;
        if (!flujo) return;
        _ady.resize(_V);
        int E, v, w;
        flujo >> E;
        while (E--) {
            flujo >> v >> w;
            ponArista(v - primer, w - primer);
        }
    }

    /**
     * Devuelve el número de vértices del grafo.
     */
    int V() const { return _V; }

    /**
     * Devuelve el número de aristas del grafo.
     */
    int A() const { return _A; }

    /**
     * Añade la arista dirigida v-w al grafo.
     * @throws domain_error si algún vértice no existe
     */
    void ponArista(int v, int w) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v].push_back(w);
    }


    /**
     * Comprueba si hay arista de u a v.
     */
    bool hayArista(int u, int v) const {
        for (int w : _ady[u])
            if (w == v) return true;
        return false;
    }


    /**
     * Devuelve la lista de adyacencia de v.
     * @throws domain_error si v no existe
     */
    Adys const& ady(int v) const {
        if (v < 0 || v >= _V)
            throw std::domain_error("Vertice inexistente");
        return _ady[v];
    }


    /**
     * Devuelve el grafo dirigido inverso.
     */
    Digrafo inverso() const {
        Digrafo inv(_V);
        for (int v = 0; v < _V; ++v) {
            for (int w : _ady[v]) {
                inv.ponArista(w, v);
            }
        }
        return inv;
    }


    /**
     * Muestra el grafo en el stream de salida o (para depurar)
     */
    void print(std::ostream& o = std::cout) const {
        o << _V << " vértices, " << _A << " aristas\n";
        for (int v = 0; v < _V; ++v) {
            o << v << ": ";
            for (int w : _ady[v]) {
                o << w << " ";
            }
            o << "\n";
        }
    }

};

/**
 * Para mostrar grafos por la salida estándar.
 */
inline std::ostream& operator<<(std::ostream& o, Digrafo const& g) {
    g.print(o);
    return o;
}

void dfs_Ciclo(Digrafo const& g, vector<bool>& visit, vector<bool>& apil, int v, bool& hayCiclo) {
    apil[v] = true;
    visit[v] = true;
    for (int w : g.ady(v)) {
        if (hayCiclo) return;
        if (!visit[w]) {
            dfs_Ciclo(g, visit, apil, w, hayCiclo);
        }
        else if (apil[w]) hayCiclo = true;
    }
    apil[v] = false;
}

void dfs_Camino(Digrafo const& g, vector<bool>& visit, int v) {
    visit[v] = true;
    for (int w : g.ady(v)) {
        if (!visit[w]) {
            dfs_Camino(g, visit, w);
        }
    }
}

bool resuelveCaso() {
    int num_vertices; cin >> num_vertices;

    if (!std::cin)
        return false;
   
    Digrafo G(num_vertices + 1);

    for (int i = 0; i < num_vertices; ++i) {
        char c; cin >> c;
        if (c == 'A') {
            G.ponArista(i, i + 1);
        }
        else if (c == 'J') {
            int salto; cin >> salto;
            G.ponArista(i, salto - 1);
        }
        else if (c == 'C') {
            int salto; cin >> salto;
            G.ponArista(i, salto - 1);
            G.ponArista(i, i + 1);
        }
    }

    //Veo si hay algun ciclo en el grafo
    vector<bool> visit_Ciclo(G.V(), false);
    vector<bool> apilado_Ciclo(G.V(), false);
    bool hayCiclo = false;
    dfs_Ciclo(G, visit_Ciclo, apilado_Ciclo, 0, hayCiclo);

    //Veo si hay algun camino desde la primera instruccion hasta la ultima
    vector<bool> visit_Cam(G.V(), false);
    dfs_Camino(G, visit_Cam, 0);
    bool hayCamino = visit_Cam[num_vertices];

    if (hayCamino) {
        if (hayCiclo) {
            cout << "A VECES\n";
        }
        else cout << "SIEMPRE\n";
    }
    else cout << "NUNCA\n";
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}