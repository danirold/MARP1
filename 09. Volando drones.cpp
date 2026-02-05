// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

using namespace std;

// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T>>
class PriorityQueue {

    // vector que contiene los datos
    std::vector<T> array;     // primer elemento en la posición 1

    /* Objeto función que sabe comparar elementos.
     antes(a,b) es cierto si a es más prioritario que b (a debe salir antes que b) */
    Comparator antes;

public:

    PriorityQueue(Comparator c = Comparator()) : array(1), antes(c) {}

    /* Constructor a partir de un vector de elementos */
    PriorityQueue(std::vector<T> const& v_ini, Comparator c = Comparator()) :
        array(v_ini.size() + 1), antes(c) {
        for (auto i = 0; i < v_ini.size(); ++i)
            array[i + 1] = v_ini[i];
        monticulizar();
    }


    /* Insertar el elemento x (que incluye su prioridad).
     Si no hay espacio, el array se agranda. */
    void push(T const& x) {
        array.push_back(x);
        flotar(array.size() - 1);
    }

    /* Devuelve el número de elementos en la cola. */
    int size() const { return int(array.size()) - 1; }

    /* Averigua si la cola con prioridad está vacía. */
    bool empty() const { return size() == 0; }

    /* Si la cola no es vacía, devuelve el elemento más prioritario. */
    T const& top()  const {
        if (empty()) throw std::domain_error("La cola vacia no tiene top");
        else return array[1];
    }

    /* Si la cola no es vacía, elimina el elemento más prioritario. */
    void pop() {
        if (empty())
            throw std::domain_error("Imposible eliminar el primero de una cola vacia");
        else {
            array[1] = std::move(array.back());
            array.pop_back();
            if (!empty()) hundir(1);
        }
    }

    /* Si la cola no es vacía, elimina y devuelve el elemento más prioritario. */
    void pop(T& prim) {
        if (empty())
            throw std::domain_error("Imposible eliminar el primero de una cola vacia");
        else {
            prim = std::move(array[1]);
            array[1] = std::move(array.back());
            array.pop_back();
            if (!empty()) hundir(1);
        }
    }

private:

    /* Flota el elemento situado en la posición i del montículo. */
    void flotar(int i) {
        T elem = std::move(array[i]);
        int hueco = i;
        while (hueco != 1 && antes(elem, array[hueco / 2])) {
            array[hueco] = std::move(array[hueco / 2]);
            hueco /= 2;
        }
        array[hueco] = std::move(elem);
    }

    /* Hunde el elemento situado en la posición n del montículo. */
    void hundir(int i) {
        T elem = std::move(array[i]);
        int hueco = i;
        int hijo = 2 * hueco; // hijo izquierdo, si existe
        while (hijo <= size()) {
            // cambiar al hijo derecho si existe y va antes que el izquierdo
            if (hijo < size() && antes(array[hijo + 1], array[hijo]))
                ++hijo;
            // flotar el hijo si va antes que el elemento hundiéndose
            if (antes(array[hijo], elem)) {
                array[hueco] = std::move(array[hijo]);
                hueco = hijo; hijo = 2 * hueco;
            }
            else break;
        }
        array[hueco] = std::move(elem);
    }

    /* Convierte un vector en un montículo. */
    void monticulizar() {
        for (auto i = size() / 2; i > 0; --i)
            hundir(i);
    }
};

struct tDron {
    int V9;
    int V1_5;
};

bool resuelveCaso() {
    int drones, pilas9V, pilas1_5V;
    cin >> drones >> pilas9V >> pilas1_5V;

    if (!std::cin)
        return false;

    vector<int> horas9V(pilas9V);
    for (int i = 0; i < pilas9V; ++i) {
        cin >> horas9V[i];
    }

    vector<int> horas1_5V(pilas1_5V);
    for (int i = 0; i < pilas1_5V; ++i) {
        cin >> horas1_5V[i];
    }

    PriorityQueue<int, greater<int>> p9V(horas9V);
    PriorityQueue<int, greater<int>> p1_5V(horas1_5V);

    while (!p9V.empty() && !p1_5V.empty()) {
        int suma = 0;
        int tam_vector = drones;
        if (p9V.size() < drones || p1_5V.size() < drones) {
            tam_vector = min(p9V.size(), p1_5V.size());
        }
        vector<tDron> v_drones(tam_vector);
        for (int i = 0; i < tam_vector; ++i) {
            v_drones[i] = { p9V.top(), p1_5V.top() };
            p9V.pop(); p1_5V.pop();
        }
        for (int i = 0; i < tam_vector; ++i) {
            if (v_drones[i].V9 == v_drones[i].V1_5) {
                suma += v_drones[i].V9;
            }
            else if (v_drones[i].V9 > v_drones[i].V1_5) {
                suma += v_drones[i].V1_5;
                p9V.push(v_drones[i].V9 - v_drones[i].V1_5);
            }
            else {
                suma += v_drones[i].V9;
                p1_5V.push(v_drones[i].V1_5 - v_drones[i].V9);
            }
        }

        cout << suma << ' ';
    }

    cout << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}