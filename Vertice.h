#pragma once
#include "ListaDin.h"
#include <string>

using namespace std;

class Vertice {
private:
    string nombre;
    ListaDin<int> vecinos;

public:
    Vertice() {
        nombre = "";
    }

    Vertice(string _nombre) {
        nombre = _nombre;
    }

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