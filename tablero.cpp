#include "tablero.h"
#include <iostream>
using namespace std;

int tablero_ancho = 0;
int tablero_alto = 0;
int tablero_bytes_por_fila = 0;
unsigned char** tablero_datos = 0;

int crear_tablero(int ancho, int alto) {
    if (ancho < 8 || alto < 8 || ancho % 8 != 0) {
        return 0;
    }

    if (tablero_datos != 0) {
        destruir_tablero();
    }

    tablero_ancho = ancho;
    tablero_alto = alto;
    tablero_bytes_por_fila = ancho / 8;
    tablero_datos = new unsigned char*[alto];

    for (int i = 0; i < alto; i++) {
        tablero_datos[i] = new unsigned char[tablero_bytes_por_fila];
    }

    limpiar_tablero();
    return 1;
}

void destruir_tablero() {
    if (tablero_datos == 0) {
        return;
    }

    for (int i = 0; i < tablero_alto; i++) {
        delete[] tablero_datos[i];
    }

    delete[] tablero_datos;
    tablero_datos = 0;
    tablero_ancho = 0;
    tablero_alto = 0;
    tablero_bytes_por_fila = 0;
}


void limpiar_tablero() {
    for (int i = 0; i < tablero_alto; i++) {
        for (int j = 0; j < tablero_bytes_por_fila; j++) {
            tablero_datos[i][j] = 0;
        }
    }
}
