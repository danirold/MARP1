// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <queue>

using namespace std;

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Grafo {
private:
    int _V;  // número de vértices
    int _A;  // número de aristas
    std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

    /**
     * Crea un grafo con V vértices.
     */
    Grafo(int V) : _V(V), _A(0), _ady(_V) {}

    /**
     * Crea un grafo a partir de los datos en el flujo de entrada (si puede).
     * primer es el índice del primer vértice del grafo en el entrada.
     */
    Grafo(std::istream& flujo, int primer = 0) : _A(0) {
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
     * Añade la arista v-w al grafo.
     * @throws domain_error si algún vértice no existe
     */
    void ponArista(int v, int w) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v].push_back(w);
        _ady[w].push_back(v);
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
 * Para mostrar grafos por la salida estándar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo const& g) {
    g.print(o);
    return o;
}

void bfs(Grafo const& g, vector<bool> & visit, vector<int>& ant, vector<int> & dist, int s, int valor) {
    queue<int> q;
    dist[s] = 0; visit[s] = true;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int w : g.ady(v)) {
            if (!visit[w]) {
                ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
                q.push(w);
            }
        }
    }
}

bool resuelveCaso() {
    Grafo G(cin, 1);

    if (!std::cin)
        return false;

    int num_consultas; cin >> num_consultas;
    for (int i = 0; i < num_consultas; ++i) {
        int nodo_inicial; cin >> nodo_inicial;
        int valor_inicial; cin >> valor_inicial;

        vector<bool> visit(G.V(), false);
        vector<int> ant(G.V());
        vector<int> dist(G.V());

        bfs(G, visit, ant, dist, nodo_inicial - 1, valor_inicial);
        int sol = 1;
        for (int i = 0; i < G.V(); ++i) {
            if (dist[i] <= valor_inicial && dist[i] != 0) {
                sol++;
            }
        }

        cout << G.V() - sol << '\n';
    }

    cout << "---\n";
   
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}