#include <iostream>
using namespace std;

unsigned short piesas(int t);
void figura(int t, char **filas);

int main() {
    char f0[5], f1[5], f2[5], f3[5];
    char *filas[4] = { f0, f1, f2, f3 };
    figura(9, filas);
    for (int i = 0; i < 4; i++) {
        cout << filas[i] << '\n';
    }
    return 0;
}

unsigned short piesas(int t) {
    if (t == 0) return (unsigned short)0x00F0;
    if (t == 1) return (unsigned short)0x0066;
    if (t == 2) return (unsigned short)0x0072;
    if (t == 3) return (unsigned short)0x0036;
    if (t == 4) return (unsigned short)0x0063;
    if (t == 5) return (unsigned short)0x0071;
    return (unsigned short)0x0074;
}

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
