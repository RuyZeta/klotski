#include <iostream>
#include "piezas.h"
using namespace std;

uint bloqueGPos[12] = {
                        0x33,       0x33<<1,    0x33<<2,
                        0x33<<4,    0x33<<5,    0x33<<6,
                        0x33<<8,    0x33<<9,    0x33<<10,
                        0x33<<12,   0x33<<13,   0x33<<14
};

uint maskGmoves(const uint& g) {
    uint derecha = ((g>>1) & (~g)) & (~first_col);
    uint izquierda = ((g<<1) & (~g)) & (~fourth_col);
    uint abajo = (g>>4) & (~g);
    uint arriba = ((g<<4) & (~g)) & (fullBoard);
    return (derecha | izquierda | abajo | arriba);
}

int main() {
    nodo n1, n2, n3, n4;
    uint pos[12]  {0x800, 0x400, 0xcc000, 0x22000, 0x220, 0x110, 0x44,
                   0x3, 0x10000, 0x1000, 0x80, 0x8};
    uint pos1[12]  {0x800, 0x80, 0x330, 0x88000, 0x44000, 0x22000, 0x11000,
                    0xc, 0x400, 0x40, 0x2, 0x1};
    uint pos2[12] { 0x8, 0x1, 0x6600, 0x88000, 0x11000, 0x880, 0x110, 0x60000,
                    0x40, 0x20, 0x4, 0x2};
    n2.set_board(pos);
    n3.set_board(pos1);
    n4.set_board(pos2);

    uint a = 234;
    uint b = 456;
    uint m = 0b10001001010011010000;


    uint g= 0;
    for(int i = 0; i < 12; i++) {
        print_board(maskGmoves( bloqueGPos[i]));
        cin.get();

    }


    cin.get();

    return 0;
}
