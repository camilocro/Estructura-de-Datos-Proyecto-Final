#include "Grafo.h"

Grafo::Grafo() {
    // Constructor vacío
}

// No hace falta implementar copia profunda, vector lo hace automático

void Grafo::cargarDesdeArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string dato;

    if (archivo.is_open()) {
        // PASADA 1: Crear Vértices
        while (archivo >> dato) {
            if (dato != "-1") {
                if (mapaIndices.find(dato) == mapaIndices.end()) {
                    Vertice v(dato);
                    vertices.push_back(v); // Usamos push_back
                    mapaIndices[dato] = vertices.size() - 1; // Usamos size()
                }
            }
        }

        archivo.clear();
        archivo.seekg(0);

        int indiceOrigen = -1;
        bool nuevaLinea = true;

        // PASADA 2: Crear Aristas
        while (archivo >> dato) {
            if (dato == "-1") {
                nuevaLinea = true;
            }
            else {
                if (nuevaLinea) {
                    if (mapaIndices.find(dato) != mapaIndices.end()) {
                        indiceOrigen = mapaIndices[dato];
                    }
                    nuevaLinea = false;
                }
                else {
                    if (indiceOrigen != -1 && mapaIndices.find(dato) != mapaIndices.end()) {
                        int indiceDestino = mapaIndices[dato];
                        // Acceso directo con [] como en arrays
                        vertices[indiceOrigen].agregarVecino(indiceDestino);
                    }
                }
            }
        }
        archivo.close();
        mapaIndices.clear();
    }
}

void Grafo::obtenerAristaAleatoria(int& idxN1, int& idxN2) {
    if (vertices.size() < 2) {
        idxN1 = -1; idxN2 = -1;
        return;
    }

    // rand % size()
    idxN1 = rand() % vertices.size();

    Vertice& v = vertices[idxN1];
    int numVecinos = v.getVecinos().size();

    if (numVecinos > 0) {
        int azarVecino = rand() % numVecinos;
        // Accedemos al vecino en la posición aleatoria
        idxN2 = v.getVecinos()[azarVecino];
    }
    else {
        idxN2 = -1;
    }
}

void Grafo::contraerArista(int idxu, int idxv) {
    Vertice& u = vertices[idxu];
    Vertice& v = vertices[idxv];

    vector<int>& vecinosU = u.getVecinos();
    vector<int>& vecinosV = v.getVecinos();

    // 1. Mover vecinos de V a U
    for (int vecino : vecinosV) {
        vecinosU.push_back(vecino);
    }

    // 2. Eliminar auto-ciclos (referencias a U o V)
    // Implementación manual de "filter" sobre el vector de U
    // Usamos un iterador para borrar eficientemente
    int k = 0;
    while (k < vecinosU.size()) {
        if (vecinosU[k] == idxu || vecinosU[k] == idxv) {
            // Swap and Pop para borrar en O(1)
            vecinosU[k] = vecinosU.back();
            vecinosU.pop_back();
        }
        else {
            k++;
        }
    }

    // 3. SWAP AND POP GLOBAL
    // Vamos a eliminar el nodo V moviendo el ULTIMO nodo a su lugar.
    int indiceUltimo = vertices.size() - 1;

    // Índices de remapeo
    int nuevoIndiceParaV = idxu;
    int nuevoIndiceParaLast = idxv;

    // Caso especial: Si el que sobrevive (U) era el último, al moverlo cambia de ID
    if (idxu == indiceUltimo) {
        nuevoIndiceParaV = idxv;
    }

    // Mover datos físicos: El último sobrescribe a V
    if (idxv != indiceUltimo) {
        vertices[idxv] = vertices[indiceUltimo];
    }

    // Borrar el último físico (ya está copiado o era V)
    vertices.pop_back();

    // 4. Actualizar referencias en todo el grafo
    // Como movimos el nodo "Ultimo" a la posición "idxv", 
    // todos los que apuntaban a "Ultimo" ahora deben apuntar a "idxv".
    // Y todos los que apuntaban al nodo muerto "v", ahora apuntan a "u".

    for (int i = 0; i < vertices.size(); i++) {
        vector<int>& lista = vertices[i].getVecinos();
        for (int j = 0; j < lista.size(); j++) {
            int target = lista[j];

            if (target == idxv) {
                lista[j] = nuevoIndiceParaV; // Redirigir V -> U
            }
            else if (target == indiceUltimo) {
                lista[j] = nuevoIndiceParaLast; // Redirigir Last -> Hueco de V
            }
        }
    }
}

int Grafo::getNumVertices() {
    return vertices.size();
}

int Grafo::contarAristasRestantes() {
    if (vertices.size() > 0) {
        return vertices[0].getVecinos().size();
    }
    return 0;
}

void Grafo::mostrar() {
    cout << "--- Grafo (" << vertices.size() << " nodos) ---" << endl;
    for (int i = 0; i < vertices.size(); i++) {
        cout << "[" << vertices[i].getNombre() << "] -> "
            << vertices[i].getVecinos().size() << " conexiones." << endl;
    }
    cout << "--------------------------------" << endl;
}