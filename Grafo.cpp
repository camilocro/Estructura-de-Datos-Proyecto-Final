#include "Grafo.h"

Grafo::Grafo() {
}

void Grafo::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string dato;

    if (archivo.is_open()) {
        while (archivo >> dato) {
            if (dato != "-1") {
                if (mapaIndices.find(dato) == mapaIndices.end()) {
                    vertices.emplace_back(dato);
                    mapaIndices[dato] = (int)vertices.size() - 1;
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
                    if (indiceOrigen != -1) {
                        auto it = mapaIndices.find(dato);
                        if (it != mapaIndices.end()) {
                            int indiceDestino = it->second;
                            vertices[indiceOrigen].agregarVecino(indiceDestino);
                        }
                    }
                }
            }
        }
        archivo.close();
        mapaIndices.clear();
    }
}

void Grafo::obtenerAristaAleatoria(int& idxN1, int& idxN2) {
    if (vertices.size() >= 2) {

        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> disN1(0, (int)vertices.size() - 1);

        idxN1 = disN1(gen);

        Vertice& v = vertices[idxN1];
        int numVecinos = (int)v.getVecinos().size();

        if (numVecinos > 0) {
            uniform_int_distribution<> disN2(0, numVecinos - 1);
            int azarVecino = disN2(gen);

            idxN2 = v.getVecinos()[azarVecino];
        }
        else {
            idxN2 = -1;
        }
    }
    else {
        idxN1 = -1;
        idxN2 = -1;
    }
}

void Grafo::contraerArista(int idxu, int idxv) {
    vector<int>& vecinosU = vertices[idxu].getVecinos();
    vector<int>& vecinosV = vertices[idxv].getVecinos();

    vecinosU.insert(vecinosU.end(), vecinosV.begin(), vecinosV.end());

    int k = 0;
    while (k < (int)vecinosU.size()) {
        if (vecinosU[k] == idxu || vecinosU[k] == idxv) {
            vecinosU[k] = vecinosU.back();
            vecinosU.pop_back();
        }
        else {
            k++;
        }
    }

    int indiceUltimo = (int)vertices.size() - 1;

    int nuevoIndiceParaV = idxu;
    int nuevoIndiceParaLast = idxv;

    if (idxu == indiceUltimo) {
        nuevoIndiceParaV = idxv;
    }

    if (idxv != indiceUltimo) {
        vertices[idxv] = vertices[indiceUltimo];
    }

    vertices.pop_back();

    for (int i = 0; i < (int)vertices.size(); i++) {
        vector<int>& lista = vertices[i].getVecinos();
        for (int j = 0; j < (int)lista.size(); j++) {
            int target = lista[j];

            if (target == idxv) {
                lista[j] = nuevoIndiceParaV;
            }
            else {
                if (target == indiceUltimo) {
                    lista[j] = nuevoIndiceParaLast;
                }
            }
        }
    }
}

int Grafo::getNumVertices() const {
    return (int)vertices.size();
}

int Grafo::contarAristasRestantes() const {
    int cantidad = 0;
    if (vertices.size() > 0) {
        cantidad = (int)vertices[0].getVecinos().size();
    }
    return cantidad;
}

void Grafo::mostrar() const {
    cout << "--------------------------------------------------------" << endl;
    cout << " Estructura Final (2 Super-Vertices Restantes) " << endl;
    cout << "--------------------------------------------------------" << endl;

    for (const auto& v : vertices) {
        cout << "GRUPO [" << v.getNombre() << "] conecta con:" << endl;
        cout << "   -> ";

        const vector<int>& vecinos = v.getVecinos();

        for (size_t k = 0; k < vecinos.size(); ++k) {
            int indiceVecino = vecinos[k];

            if (indiceVecino >= 0 && indiceVecino < vertices.size()) {
                cout << vertices[indiceVecino].getNombre();

                if (k < vecinos.size() - 1) {
                    cout << ", ";
                }
            }
        }
        cout << endl << "   (Total aristas: " << vecinos.size() << ")" << endl << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}