#pragma once
#include "ListaDin.h"
#include <string>

using namespace std;

class Vertice {
private:
    string nombre;
    ListaDin<int> vecinos; // Guarda índices de otros vértices en el array del Grafo

public:
    Vertice() {
        nombre = "";
    }

    Vertice(string _nombre) {
        nombre = _nombre;
    }

    // Constructor de copia por defecto funciona bien aquí gracias a ListaDin

    void setNombre(string n) {
        nombre = n;
    }

    string getNombre() {
        return nombre;
    }

    void agregarVecino(int indiceVecino) {
        vecinos.insertar(indiceVecino);
    }

    ListaDin<int>& getVecinos() {
        return vecinos;
    }
};