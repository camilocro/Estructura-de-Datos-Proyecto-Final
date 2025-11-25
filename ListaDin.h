#pragma once
#include <iostream>
#include <cstdlib>

template <class T>
class ListaDin {
private:
    T* datos;
    int cantidad;
    int capacidad;

    void redimensionar(int nuevaCapacidad) {
        T* nuevosDatos = new T[nuevaCapacidad];
        int i = 0;
        bool continuar = true;
        while (continuar && i < cantidad) {
            nuevosDatos[i] = datos[i];
            i++;
        }

        if (capacidad > 0) {
            delete[] datos;
        }
        datos = nuevosDatos;
        capacidad = nuevaCapacidad;
    }

public:
    ListaDin() {
        capacidad = 10;
        cantidad = 0;
        datos = new T[capacidad];
    }

    ListaDin(const ListaDin& otra) {
        capacidad = otra.capacidad;
        cantidad = otra.cantidad;
        datos = new T[capacidad];
        int i = 0;
        while (i < cantidad) {
            datos[i] = otra.datos[i];
            i++;
        }
    }

    ListaDin& operator=(const ListaDin& otra) {
        if (this != &otra) { 
            if (capacidad > 0) {
                delete[] datos;
            }

            capacidad = otra.capacidad;
            cantidad = otra.cantidad;

            datos = new T[capacidad];
            int i = 0;
            while (i < cantidad) {
                datos[i] = otra.datos[i];
                i++;
            }
        }
        return *this;
    }

    ~ListaDin() {
        if (capacidad > 0) {
            delete[] datos;
        }
    }

    void insertar(T valor) {
        if (cantidad >= capacidad) {
            redimensionar(capacidad * 2);
        }
        datos[cantidad] = valor;
        cantidad++;
    }

    void eliminarSwap(int indice) {
        if (indice >= 0 && indice < cantidad) {
            datos[indice] = datos[cantidad - 1];
            cantidad--;
        }
    }

    void eliminarValor(T valor) {
        int i = 0;
        while (i < cantidad) {
            if (datos[i] == valor) {
                datos[i] = datos[cantidad - 1];
                cantidad--;
            }
            else {
                i++;
            }
        }
    }

    T obtener(int indice) const {
        T valor;
        if (indice >= 0 && indice < cantidad) {
            valor = datos[indice];
        }
        return valor;
    }

    T& obtenerRef(int indice) {
        return datos[indice];
    }

    int getCantidad() const {
        return cantidad;
    }

    T& operator[](int index) {
        return datos[index];
    }

    const T& operator[](int index) const {
        return datos[index];
    }
};