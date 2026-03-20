#include "game.h"
#include "board.h"
#include "pieces.h"
#include <iostream>

using namespace std;

int pieza_actual = 0;
int rotacion_actual = 0;
int posicion_x = 0;
int posicion_y = 0;
unsigned short* forma_actual = 0;
int ancho_pieza = 0;
int alto_pieza = 0;
int estado_juego_terminado = 0;
int estado_salida_solicitada = 0;
int MAX_TAMANO_PIEZA = 4;
int NUMERO_PIEZAS = 7;

int puede_colocar(int x, int y, unsigned short* forma, int ancho, int alto) {
    if (x < 0 || x + ancho > obtener_ancho_tablero()) {
        return 0;
    }

    if (y < 0 || y + alto > obtener_alto_tablero()) {
        return 0;
    }

    for (int fila = 0; fila < alto; fila++) {
        unsigned short fila_actual = forma[fila];
        for (int columna = 0; columna < ancho; columna++) {
            if (fila_actual & (1 << (15 - columna))) {
                if (obtener_bit(y + fila, x + columna)) {
                    return 0;
                }
            }
        }
    }

    return 1;
}

void generar_nueva_pieza() {
    pieza_actual = pieza_aleatoria();
    rotacion_actual = 0;
    obtener_pieza_inicial(pieza_actual, forma_actual, &ancho_pieza, &alto_pieza);
    posicion_x = (obtener_ancho_tablero() - ancho_pieza) / 2;
    posicion_y = 0;

    if (!puede_colocar(posicion_x, posicion_y, forma_actual, ancho_pieza, alto_pieza)) {
        estado_juego_terminado = 1;
    }
}

void fijar_pieza() {
    for (int fila = 0; fila < alto_pieza; fila++) {
        unsigned short fila_actual = forma_actual[fila];
        for (int columna = 0; columna < ancho_pieza; columna++) {
            if (fila_actual & (1 << (15 - columna))) {
                establecer_bit(posicion_y + fila, posicion_x + columna, 1);
            }
        }
    }

    limpiar_lineas_completas();
    generar_nueva_pieza();
}

void mostrar_juego() {
    for (int i = 0; i < 30; i++) {
        cout << "\n";
    }

    cout << "=== TETRIS (Version Bits) ===\n";
    cout << "Tablero: " << obtener_ancho_tablero() << "x" << obtener_alto_tablero() << "\n\n";

    cout << "+";
    for (int i = 0; i < obtener_ancho_tablero(); i++) {
        cout << "-";
    }
    cout << "+\n";

    for (int fila = 0; fila < obtener_alto_tablero(); fila++) {
        cout << "|";
        for (int columna = 0; columna < obtener_ancho_tablero(); columna++) {
            int es_pieza_actual = 0;

            if (fila >= posicion_y && fila < posicion_y + alto_pieza &&
                columna >= posicion_x && columna < posicion_x + ancho_pieza) {
                int fila_pieza = fila - posicion_y;
                int columna_pieza = columna - posicion_x;

                if (forma_actual[fila_pieza] & (1 << (15 - columna_pieza))) {
                    es_pieza_actual = 1;
                }
            }

            if (es_pieza_actual) {
                cout << "@";
            } else if (obtener_bit(fila, columna)) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << "|\n";
    }

    cout << "+";
    for (int i = 0; i < obtener_ancho_tablero(); i++) {
        cout << "-";
    }
    cout << "+\n";
}

int mover_izquierda() {
    if (puede_colocar(posicion_x - 1, posicion_y, forma_actual, ancho_pieza, alto_pieza)) {
        posicion_x--;
        return 1;
    }

    return 0;
}

int mover_derecha() {
    if (puede_colocar(posicion_x + 1, posicion_y, forma_actual, ancho_pieza, alto_pieza)) {
        posicion_x++;
        return 1;
    }

    return 0;
}

int mover_abajo() {
    if (puede_colocar(posicion_x, posicion_y + 1, forma_actual, ancho_pieza, alto_pieza)) {
        posicion_y++;
        return 1;
    }

    fijar_pieza();
    return 0;
}

int rotar_pieza() {
    unsigned short forma_rotada[4];
    int nuevo_ancho;
    int nuevo_alto;
    int nueva_x;

    rotar_forma_pieza(forma_actual, ancho_pieza, alto_pieza, forma_rotada, &nuevo_ancho, &nuevo_alto);
    nueva_x = posicion_x;

    if (nueva_x + nuevo_ancho > obtener_ancho_tablero()) {
        nueva_x = obtener_ancho_tablero() - nuevo_ancho;
    }

    if (nueva_x < 0) {
        nueva_x = 0;
    }

    if (!puede_colocar(nueva_x, posicion_y, forma_rotada, nuevo_ancho, nuevo_alto)) {
        return 0;
    }

    for (int i = 0; i < MAX_TAMANO_PIEZA; i++) {
        forma_actual[i] = forma_rotada[i];
    }

    ancho_pieza = nuevo_ancho;
    alto_pieza = nuevo_alto;
    posicion_x = nueva_x;
    rotacion_actual = (rotacion_actual + 1) % 4;
    return 1;
}
