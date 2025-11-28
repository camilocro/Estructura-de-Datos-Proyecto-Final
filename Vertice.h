#pragma once
#include <vector>
#include <string>

using namespace std;

class Vertice {
private:
    string nombre;
    vector<int> vecinos; // USAMOS VECTOR ESTÁNDAR

public:
    Vertice() {
        nombre = "";
    }

    Vertice(string _nombre) {
        nombre = _nombre;
    }

    // Ya no necesitamos constructores de copia manuales, vector lo hace solo

    void setNombre(string n) {
        nombre = n;
    }

    string getNombre() {
        return nombre;
    }

    void agregarVecino(int indiceVecino) {
        vecinos.push_back(indiceVecino); // push_back en lugar de insertar
    }

    // Devolvemos referencia al vector para poder modificarlo fuera
    vector<int>& getVecinos() {
        return vecinos;
    }
};