#pragma once
#include <vector>
#include <string>

using namespace std;

class Vertice {
private:
    string nombre;
    vector<int> vecinos;

public:
    Vertice() {
        nombre = "";
    }

    Vertice(const string& _nombre) {
        nombre = _nombre;
    }

    void setNombre(const string& n) {
        nombre = n;
    }

    string getNombre() const {
        return nombre;
    }

    void agregarVecino(int indiceVecino) {
        vecinos.push_back(indiceVecino);
    }

    vector<int>& getVecinos() {
        return vecinos;
    }

    const vector<int>& getVecinos() const {
        return vecinos;
    }
};