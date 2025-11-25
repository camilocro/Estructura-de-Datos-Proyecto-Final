#pragma once
#include "Vertice.h"
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <random>

using namespace std;

class Grafo {
private:
    ListaDin<Vertice> vertices; 
    map<string, int> mapaIndices;

public:
    Grafo();
    Grafo(const Grafo& otro);
    Grafo& operator=(const Grafo& otro);
    void cargarDesdeArchivo(string nombreArchivo);
    void obtenerAristaAleatoria(int& idxN1, int& idxN2);
    void contraerArista(int idxu, int idxv);
    int getNumVertices();
    int contarAristasRestantes();
    void mostrar();
};