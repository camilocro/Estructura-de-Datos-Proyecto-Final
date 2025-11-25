#include "Grafo.h"

Grafo::Grafo() {
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
        while (archivo >> dato) {
            if (dato != "-1") {
                if (mapaIndices.find(dato) == mapaIndices.end()) {
                    Vertice v(dato);
                    vertices.insertar(v);
                    mapaIndices[dato] = vertices.getCantidad() - 1;
                }
            }
        }
        archivo.clear();
        archivo.seekg(0);

        int indiceOrigen = -1;
        bool nuevaLinea = true;

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

    if (total >= 2) {
        idxN1 = rand() % total;

        Vertice& v = vertices.obtenerRef(idxN1);
        int numVecinos = v.getVecinos().getCantidad();

        if (numVecinos > 0) {
            int azarVecino = rand() % numVecinos;
            idxN2 = v.getVecinos().obtener(azarVecino);
        }
        else {
            idxN2 = -1;
        }
    }
}

void Grafo::contraerArista(int idxu, int idxv) {
    Vertice& u = vertices.obtenerRef(idxu);
    Vertice& v = vertices.obtenerRef(idxv);

    ListaDin<int>& vecinosU = u.getVecinos();
    ListaDin<int>& vecinosV = v.getVecinos();

    int i = 0;
    int cantV = vecinosV.getCantidad();
    while (i < cantV) {
        vecinosU.insertar(vecinosV.obtener(i));
        i++;
    }
    vecinosU.eliminarValor(idxu);
    vecinosU.eliminarValor(idxv);

    int indiceUltimo = vertices.getCantidad() - 1;

    int nuevoIndiceParaV = idxu;
    int nuevoIndiceParaLast = idxv;

    if (idxu == indiceUltimo) {
        nuevoIndiceParaV = idxv;
    }

    if (idxv != indiceUltimo) {
        vertices.obtenerRef(idxv) = vertices.obtenerRef(indiceUltimo);
    }

    int k = 0;
    while (k < indiceUltimo) {
        ListaDin<int>& lista = vertices.obtenerRef(k).getVecinos();
        int j = 0;
        int cantVecinos = lista.getCantidad();

        while (j < cantVecinos) {
            int target = lista[j];

            if (target == idxv) {
                lista[j] = nuevoIndiceParaV;
            }
            else if (target == indiceUltimo) {
                lista[j] = nuevoIndiceParaLast;
            }
            j++;
        }
        k++;
    }
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