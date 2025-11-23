#include "Grafo.h"

Grafo::Grafo() {
    // Constructor vacío
}

Grafo::Grafo(const Grafo& otro) {
    vertices = otro.vertices;
}

Grafo& Grafo::operator=(const Grafo& otro) {
    if (this != &otro) {
        vertices = otro.vertices;
    }
    return *this;
}

void Grafo::cargarDesdeArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string dato;

    if (archivo.is_open()) {
        // PASADA 1: Crear Vértices
        while (archivo >> dato) {
            if (dato != "-1") {
                if (mapaIndices.find(dato) == mapaIndices.end()) {
                    Vertice v(dato);
                    vertices.insertar(v);
                    mapaIndices[dato] = vertices.getCantidad() - 1;
                }
            }
        }

        // Reiniciar lectura
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
                    // Inicio de fila: Vértice Origen
                    // Usamos .at() para asegurar que existe, si falla es error de archivo
                    if (mapaIndices.find(dato) != mapaIndices.end()) {
                        indiceOrigen = mapaIndices[dato];
                    }
                    nuevaLinea = false;
                }
                else {
                    // Vecino: Vértice Destino
                    if (indiceOrigen != -1 && mapaIndices.find(dato) != mapaIndices.end()) {
                        int indiceDestino = mapaIndices[dato];
                        vertices.obtenerRef(indiceOrigen).agregarVecino(indiceDestino);
                    }
                }
            }
        }
        archivo.close();
        mapaIndices.clear();
    }
}

void Grafo::obtenerAristaAleatoria(int& idxN1, int& idxN2) {
    int total = vertices.getCantidad();
    if (total < 2) return;

    // N1 = rand % total
    idxN1 = rand() % total;

    Vertice& v = vertices.obtenerRef(idxN1);
    int numVecinos = v.getVecinos().getCantidad();

    if (numVecinos > 0) {
        // N2 = rand % vecinos
        int azarVecino = rand() % numVecinos;
        idxN2 = v.getVecinos().obtener(azarVecino);
    }
    else {
        idxN2 = -1;
    }
}

void Grafo::contraerArista(int idxu, int idxv) {
    // Referencias a los vértices
    Vertice& u = vertices.obtenerRef(idxu);
    Vertice& v = vertices.obtenerRef(idxv);

    ListaDin<int>& vecinosU = u.getVecinos();
    ListaDin<int>& vecinosV = v.getVecinos();

    // 1. Mover vecinos de V a U
    int i = 0;
    int cantV = vecinosV.getCantidad();
    while (i < cantV) {
        vecinosU.insertar(vecinosV.obtener(i));
        i++;
    }

    // 2. Eliminar referencias circulares (auto-ciclos)
    vecinosU.eliminarValor(idxu);
    vecinosU.eliminarValor(idxv);

    // 3. SWAP AND POP ROBUSTO (Aquí estaba el error del 0)
    int indiceUltimo = vertices.getCantidad() - 1;

    // Calculamos a dónde deben apuntar ahora las referencias
    // Normalmente: Lo que apuntaba a V -> Ahora apunta a U
    //              Lo que apuntaba a Last -> Ahora apunta al hueco de V
    int nuevoIndiceParaV = idxu;
    int nuevoIndiceParaLast = idxv;

    // CASO ESPECIAL CRITICO:
    // Si el nodo que sobrevive (U) era casualmente el último del array,
    // al mover el último a la posición de V, ¡U se mueve a la posición de V!
    // Entonces las referencias a U deben actualizarse a idxv también.
    if (idxu == indiceUltimo) {
        nuevoIndiceParaV = idxv;
    }

    // Movemos físicamente el último vértice a la posición de V (tapamos el hueco)
    if (idxv != indiceUltimo) {
        vertices.obtenerRef(idxv) = vertices.obtenerRef(indiceUltimo);
    }

    // Actualizamos referencias en TODO el grafo
    // Solo recorremos hasta indiceUltimo (sin incluirlo) porque ese nodo ya "se movió"
    int k = 0;
    while (k < indiceUltimo) {
        ListaDin<int>& lista = vertices.obtenerRef(k).getVecinos();
        int j = 0;
        int cantVecinos = lista.getCantidad();

        while (j < cantVecinos) {
            int target = lista[j];

            if (target == idxv) {
                // Apuntaba al nodo muerto (V) -> Redirigir al superviviente
                lista[j] = nuevoIndiceParaV;
            }
            else if (target == indiceUltimo) {
                // Apuntaba al nodo que movimos -> Redirigir a su nueva posición
                lista[j] = nuevoIndiceParaLast;
            }
            j++;
        }
        k++;
    }

    // Finalmente eliminamos el último (que ya copiamos)
    vertices.eliminarSwap(indiceUltimo);
}

int Grafo::getNumVertices() {
    return vertices.getCantidad();
}

int Grafo::contarAristasRestantes() {
    if (vertices.getCantidad() > 0) {
        return vertices.obtenerRef(0).getVecinos().getCantidad();
    }
    return 0;
}

void Grafo::mostrar() {
    int n = vertices.getCantidad();
    cout << "--- Grafo (" << n << " nodos) ---" << endl;

    int i = 0;
    while (i < n) {
        Vertice& v = vertices.obtenerRef(i);
        cout << "[" << v.getNombre() << "] -> ";

        int j = 0;
        int nVecinos = v.getVecinos().getCantidad();

        if (nVecinos > 15) {
            cout << nVecinos << " conexiones.";
        }
        else {
            while (j < nVecinos) {
                int idxVecino = v.getVecinos().obtener(j);
                if (idxVecino >= 0 && idxVecino < n) {
                    cout << vertices.obtenerRef(idxVecino).getNombre() << " ";
                }
                j++;
            }
        }
        cout << endl;
        i++;
    }
    cout << "--------------------------------" << endl;
}