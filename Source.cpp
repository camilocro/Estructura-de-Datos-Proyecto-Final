#include <iostream>
#include <string>
#include <ctime>
#include <cmath> 
#include <chrono> // <--- LIBRERÍA PARA EL TIEMPO
#include "Grafo.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "=== PROYECTO FINAL: KARGER MIN CUT ===" << endl;

    // 1. Pedir nombre
    string nombreArchivo;
    cout << "Ingrese nombre del archivo: ";
    char buffer[256];
    cin.getline(buffer, 256);
    nombreArchivo = string(buffer);

    if (nombreArchivo.empty()) {
        nombreArchivo = "MIN_CUT_CON_NOMBRES.txt";
    }

    // 2. Carga inicial
    Grafo grafoOriginal;
    cout << "Cargando desde '" << nombreArchivo << "'..." << endl;
    grafoOriginal.cargarDesdeArchivo(nombreArchivo);

    int numVertices = grafoOriginal.getNumVertices();

    // VALIDACION DE SEGURIDAD
    if (numVertices < 2) {
        cout << "ERROR: No se cargaron vertices. Verifique el nombre del archivo." << endl;
        cin.get();
        return -1;
    }

    // Verificar que tenga aristas
    if (grafoOriginal.contarAristasRestantes() == 0) {
        cout << "ERROR: El grafo no tiene aristas o esta desconectado." << endl;
        cout << "Revise el formato del archivo de texto." << endl;
        cin.get();
        return -1;
    }

    // 3. Calculo iteraciones
    int iteraciones = (int)(numVertices * numVertices * log(numVertices));
    if (iteraciones < 10) iteraciones = 10;

    cout << "Vertices: " << numVertices << endl;
    cout << "Iteraciones calculadas: " << iteraciones << endl;
    cout << "Iniciando proceso..." << endl;
    cout << "Progreso: ";

    // --- INICIO DEL CRONOMETRO ---
    auto inicioReloj = chrono::high_resolution_clock::now();
    // -----------------------------

    int minCorteGlobal = 2147483647;
    Grafo mejorGrafo;

    // 4. Ciclo principal
    int i = 0;
    while (i < iteraciones) {
        Grafo grafoCopia(grafoOriginal);

        // Contracción
        while (grafoCopia.getNumVertices() > 2) {
            int u = -1, v = -1;
            grafoCopia.obtenerAristaAleatoria(u, v);

            if (u != -1 && v != -1 && u != v) {
                grafoCopia.contraerArista(u, v);
            }
        }

        int corte = grafoCopia.contarAristasRestantes();

        // Si encontramos un nuevo minimo
        if (corte < minCorteGlobal && corte > 0) {
            minCorteGlobal = corte;
            mejorGrafo = grafoCopia;

            cout << endl << ">> Nuevo Record: " << minCorteGlobal
                << " (Iter: " << i << ")" << endl << "Progreso: ";
        }

        // Barra de progreso simple
        if (iteraciones > 500 && i % (iteraciones / 50) == 0) {
            cout << ".";
        }

        i++;
    }

    // --- FIN DEL CRONOMETRO ---
    auto finReloj = chrono::high_resolution_clock::now();

    // Calculo de duracion
    auto duracionTotal = chrono::duration_cast<chrono::seconds>(finReloj - inicioReloj).count();
    int minutos = duracionTotal / 60;
    int segundos = duracionTotal % 60;
    // --------------------------

    cout << endl << endl << "=== ANALISIS FINALIZADO ===" << endl;
    cout << "Tiempo Total de Ejecucion: " << minutos << " min " << segundos << " seg." << endl;
    cout << "Corte Minimo DEFINITIVO: " << minCorteGlobal << endl;

    cout << endl << "Visualizacion del corte:" << endl;
    mejorGrafo.mostrar();

    cin.get();
    return 0;
}