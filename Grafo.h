#pragma once
#include "Vertice.h"
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Grafo {
private:
    vector<Vertice> vertices; // El grafo es un vector de vértices

    // Mapa auxiliar solo para la carga
    map<string, int> mapaIndices;

public:
    Grafo();

    // NOTA: Ya no necesitamos declarar Constructor de Copia ni operator=
    // C++ usa los de 'vector' automáticamente.

    void cargarDesdeArchivo(string nombreArchivo);
    void obtenerAristaAleatoria(int& idxN1, int& idxN2);
    void contraerArista(int idxu, int idxv);

    int getNumVertices();
    int contarAristasRestantes();
    void mostrar();
};