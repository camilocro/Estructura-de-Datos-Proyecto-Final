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
    ListaDin<Vertice> vertices; // Array dinámico de vértices

    // Mapa auxiliar solo para la carga inicial
    map<string, int> mapaIndices;

public:
    Grafo();

    // Constructor de copia
    Grafo(const Grafo& otro);

    // Operador de asignación (NECESARIO para guardar el grafo ganador)
    Grafo& operator=(const Grafo& otro);

    void cargarDesdeArchivo(string nombreArchivo);

    void obtenerAristaAleatoria(int& idxN1, int& idxN2);
    void contraerArista(int idxu, int idxv);

    int getNumVertices();
    int contarAristasRestantes();

    // NUEVO METODO PARA VER EL GRAFO
    void mostrar();
};