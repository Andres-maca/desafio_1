#include <iostream>
using namespace std;

unsigned short piesas(int t);
void figura(int t, char **filas);

int lineaseliminadas = 0;
int g_alto = 0;
int g_ancho = 0;
unsigned short g_mascara = 0;
int g_piezaX = 0;
int g_piezaY = 0;
int bytsporfila = 0;
unsigned char* g_tablero = 0;

void figura(int t, char **filas) {
    unsigned short p = piesas(t);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            int indexado = 15 - (y * 4 + x);
            int bit = (p >> indexado) & 1;
            filas[y][x] = bit ? '#' : '.';
        }
        filas[y][4] = '\0';
    }
}

int tableroindice(int x, int y) {
    return y * bytsporfila + (x >> 3);
}

int dentro(int x, int y) {
    return x >= 0 && x < g_ancho && y >= 0 && y < g_alto;
}

int esta_ocupado(int x, int y) {
    if (!dentro(x, y)) return 1;

    int idx = tableroindice(x, y);
    unsigned char bit = (unsigned char)(1u << (x & 7));
    return (g_tablero[idx] & bit) != 0;
}

void imprimir_tablero() {
    cout << "\nLineas eliminadas: " << lineaseliminadas << "\n";

    for (int y = 0; y < g_alto; ++y) {
        cout << "|";
        for (int x = 0; x < g_ancho; ++x) {
            int ocupado = esta_ocupado(x, y);

            int lx = x - g_piezaX;
            int ly = y - g_piezaY;
            if (lx >= 0 && lx < 4 && ly >= 0 && ly < 4) {
                int posicionBit = ly * 4 + lx;
                if (((g_mascara >> posicionBit) & 1u) != 0) {
                    ocupado = 1;
                }
            }

            cout << (ocupado ? '#' : '.');
        }
        cout << "|\n";
    }
}

int main() {
    //imprimir figura 4x4
    char f0[5], f1[5], f2[5], f3[5];
    char *filas[4] = { f0, f1, f2, f3 };

    figura(9, filas);
    for (int i = 0; i < 4; i++) {
        cout << filas[i] << '\n';
    }

    //tablero completo
    cout << "Ancho (multiplo de 8): ";
    cin >> g_ancho;

    cout << "Alto (minimo 1): ";
    cin >> g_alto;

    if (g_ancho <= 0 || g_alto <= 0 || (g_ancho % 8) != 0) {
        cout << "Dimensiones invalidas.\n";
        return 1;
    }

    bytsporfila = g_ancho / 8;
    int bytes = g_alto * bytsporfila;
    g_tablero = new unsigned char[bytes];

    for (int i = 0; i < bytes; ++i) g_tablero[i] = 0;

    cout << "Lineas eliminadas: ";
    cin >> lineaseliminadas;

    // Pieza T por defecto
    g_mascara = 0;
    g_mascara |= (1u << (0 * 4 + 1));
    g_mascara |= (1u << (1 * 4 + 0));
    g_mascara |= (1u << (1 * 4 + 1));
    g_mascara |= (1u << (1 * 4 + 2));

    cout << "posicion X de la pieza: ";
    cin >> g_piezaX;

    cout << "posicion Y de la pieza: ";
    cin >> g_piezaY;

    imprimir_tablero();

    delete[] g_tablero;
    g_tablero = 0;
    return 0;
}
