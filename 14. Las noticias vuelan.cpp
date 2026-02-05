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

int resolver(Grafo const& g, vector<bool> & visit, int v, queue<int> &valores) {
    visit[v] = true;
    int tam = 1;
    valores.push(v);
    for (int w : g.ady(v)) {
        if (!visit[w]) {
            tam += resolver(g, visit, w, valores);
        }
    }
    return tam;
}

void solucion(Grafo const& g, vector<bool>& visit, vector<int> & sol) {
    for (int i = 1; i <= g.V(); ++i) {
        if (!visit[i - 1]) {
            queue<int> valores;
            int tam = resolver(g, visit, i - 1, valores);
            while (!valores.empty()) {
                sol[valores.front()] = tam;
                valores.pop();
            }
        }
    }
}

bool resuelveCaso() {
    int num_personas, num_grupos; 
    cin >> num_personas >> num_grupos;

    if (!std::cin)
        return false;

    Grafo G(num_personas);

    for (int i = 0; i < num_grupos; ++i) {
        int num_users; cin >> num_users;
        if (num_users > 0) {
            int primer_valor; cin >> primer_valor;
            int segundo_valor;
            for (int i = 1; i < num_users; ++i) {
                cin >> segundo_valor;
                G.ponArista(primer_valor - 1, segundo_valor - 1);
                primer_valor = segundo_valor;
            }
        }
    }

    vector<int> sol(num_personas, 1);
    vector<bool> visit(num_personas, false);
    solucion(G, visit, sol);

    for (int i = 0; i < sol.size(); ++i) {
        cout << sol[i] << ' ';
    }

    cout << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}