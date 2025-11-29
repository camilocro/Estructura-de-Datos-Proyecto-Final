#pragma once
#include "Vertice.h"
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <random> 

using namespace std;

class Grafo {
private:
    vector<Vertice> vertices;
    map<string, int> mapaIndices;

public:
    Grafo();
    void cargarDesdeArchivo(const string& nombreArchivo);
    void obtenerAristaAleatoria(int& idxN1, int& idxN2);
    void contraerArista(int idxu, int idxv);
    int getNumVertices() const;
    int contarAristasRestantes() const;
    void mostrar() const;
};