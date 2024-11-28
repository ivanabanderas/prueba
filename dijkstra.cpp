#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Definimos una constante para representar "infinito"
const int INF = numeric_limits<int>::max();

struct Arista{
    int inicio;
    int destino;
    double peso;
};

class Grafo{
    private:
        int n;
        vector<vector<pair<int, double>>> aristas;
    public:
        Grafo(int n) : n(n), aristas(n) {};
        void agregar(int antes, int destino, double peso){
            aristas[antes].push_back({destino, peso});
            aristas[destino].push_back({antes, peso});

        } 

        const vector<vector<pair<int, double>>>& obtener() const {
            return aristas;
        }

        int getNodo(){
            return n;
        }
};
// Función de Dijkstra
vector<double> dijkstra(int n, int origen, const vector<vector<pair<int, double>>>& grafo, vector<int> & padres) {
    // Vector de distancias, inicializado en "infinito" para todos los nodos
    vector<double> distancias(n, INF);
    distancias[origen] = 0;

    // Cola de prioridad para seleccionar el nodo con la distancia mínima
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, origen}); // La cola almacena pares {distancia, nodo}

    while (!pq.empty()) {
        int distancia_actual = pq.top().first; // distancia minima actual
        int nodo_actual = pq.top().second; // nodo esa distancia
        pq.pop(); // sacar el elemento 

        // Ignoramos nodos ya procesados
        if (distancia_actual > distancias[nodo_actual]) continue;

        // Exploramos los vecinos del nodo actual
        for (const auto& vecino : grafo[nodo_actual]) {
            int nodo_vecino = vecino.first;
            double peso_arista = vecino.second;

            // Calculamos la nueva distancia al vecino 
            double nueva_distancia = distancia_actual + peso_arista;

            // Si encontramos una distancia más corta, la actualizamos
            if (nueva_distancia < distancias[nodo_vecino]) {
                distancias[nodo_vecino] = nueva_distancia;
                pq.push({nueva_distancia, nodo_vecino});
                padres[nodo_vecino] = nodo_actual;
            }
        }
    }

    return distancias;
}

void rutaFinal(int origen, int destino, const vector <int>& padres){
    vector<int> ruta;
    for (int nodo = destino; nodo != -1; nodo = padres[nodo]){
        ruta.push_back(nodo);
    }

    cout << "Path chosen: ";
    for (int i = ruta.size() - 1; i >= 0; --i){
        cout << ruta[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}
int main() {
    int n = 7; // Número de nodos
    Grafo grafo(7);

    // Añadir aristas al grafo {nodo_ origen, nodo_destino, peso}   a=0, b=1, ...
    grafo.agregar(0, 1, 200); //distancia en metros
    grafo.agregar(1, 2, 98.69); 
    grafo.agregar(1, 3, 293.40);
    grafo.agregar(2, 4, 97); 
    grafo.agregar(2, 4, 97); 
    grafo.agregar(2, 4, 97); 
    grafo.agregar(4, 5, 26.25);
    grafo.agregar(3, 6, 40.38); 
    grafo.agregar(5, 6, 100.22); 

    int origen = 0;
    int destino = 6; 

    vector<int> padres (n, -1);
    vector<double> distancias = dijkstra(n, origen, grafo.obtener(), padres);


    rutaFinal(origen, destino, padres);

    cout << "Distancia total: " << distancias[destino] << " metros" << endl;

    int pasos = 0;
    for (int nodo = destino; nodo != -1; nodo = padres[nodo]){
        pasos++;
    }

    cout << "Steps taken : " << pasos -1 << endl;

    return 0;
}

//Video con la explicación
//https://drive.google.com/drive/folders/1AQ_TEWlsF0WoYi3iNK6c6YgJXGMmOLzB?usp=sharing