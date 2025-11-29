#include <iostream>
#include <string>
#include <cmath> 
#include <chrono> 
#include "Grafo.h"

using namespace std;

void cargarDatos(Grafo& grafo, string& nombreArchivo) {
    cout << "Ingrese nombre del archivo: ";
    char buffer[256];
    cin.getline(buffer, 256);
    nombreArchivo = string(buffer);

    if (nombreArchivo.empty()) {
        nombreArchivo = "MIN_CUT_CON_NOMBRES.txt";
    }

    cout << "Cargando desde '" << nombreArchivo << "'..." << endl;
    grafo.cargarDesdeArchivo(nombreArchivo);
}

void ejecutarAlgoritmoPrincipal(const Grafo& grafoOriginal, int iteraciones, Grafo& mejorGrafo, int& minCorteGlobal, long long& tiempoSegundos, int& tiempoMinutos) {
    cout << "Iniciando proceso..." << endl;

    auto inicioReloj = chrono::high_resolution_clock::now();

    minCorteGlobal = 2147483647;
    int i = 0;

    while (i < iteraciones) {
        Grafo grafoCopia(grafoOriginal);

        while (grafoCopia.getNumVertices() > 2) {
            int u = -1, v = -1;
            grafoCopia.obtenerAristaAleatoria(u, v);

            if (u != -1 && v != -1 && u != v) {
                grafoCopia.contraerArista(u, v);
            }
        }

        int corteActual = grafoCopia.contarAristasRestantes();

        // cout << "Iteracion " << i << ": Corte encontrado = " << corteActual << endl;

        if (corteActual < minCorteGlobal && corteActual > 0) {
            minCorteGlobal = corteActual;
            mejorGrafo = grafoCopia;

            cout << ">> [NUEVO RECORD] Corte: " << minCorteGlobal
                << " (En iteracion: " << i << ")" << endl;
        }

        if (iteraciones > 500 && i % (iteraciones / 50) == 0) {
            cout << ".";
        }

        i++;
    }

    auto finReloj = chrono::high_resolution_clock::now();
    auto duracionTotal = chrono::duration_cast<chrono::seconds>(finReloj - inicioReloj).count();

    tiempoMinutos = (int)(duracionTotal / 60);
    tiempoSegundos = (int)(duracionTotal % 60);
}

void mostrarResultados(int minCorte, int minutos, int segundos, const Grafo& mejorGrafo) {
    cout << endl << endl << "=== ANALISIS FINALIZADO ===" << endl;
    cout << "Tiempo Total: " << minutos << " min " << segundos << " seg." << endl;
    cout << "Corte Minimo DEFINITIVO: " << minCorte << endl;

    cout << endl << "Visualizacion detallada del grafo resultante:" << endl;
    mejorGrafo.mostrar();
}

int main() {
    cout << "=== PROYECTO FINAL: KARGER MIN CUT ===" << endl;

    Grafo grafoOriginal;
    string nombreArchivo;

    cargarDatos(grafoOriginal, nombreArchivo);

    int numVertices = grafoOriginal.getNumVertices();
    if (numVertices < 2) {
        cout << "ERROR: No se cargaron vertices o el archivo esta vacio." << endl;
        cin.get();
        return -1;
    }

    int iteraciones = (int)(numVertices * numVertices * log(numVertices));
    if (iteraciones < 10) iteraciones = 10;

    cout << "Vertices: " << numVertices << endl;
    cout << "Iteraciones calculadas (N^2 * ln N): " << iteraciones << endl;

    Grafo mejorGrafo;
    int minCorteGlobal;
    long long tiempoSeg;
    int minutos, segundos;

    ejecutarAlgoritmoPrincipal(grafoOriginal, iteraciones, mejorGrafo, minCorteGlobal, tiempoSeg, minutos);

    mostrarResultados(minCorteGlobal, minutos, (int)tiempoSeg, mejorGrafo);

    cin.get();
    return 0;
}