#include <iostream>
#include "piezas.h"
using namespace std;




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

    uint vacios = n3.vco1|n3.vco2;
    uint va = n3.vaciossonAdyacentes();

    n3.print_board();

    if(va == 2) {
        uint a = arriba(vacios);
        if(a == n3.H)
            print_board(n3.H);
        if((a!=0) && (a|n3.G) == n3.G) {
            print_board(n3.G);
        }
        uint b = abajo(vacios);
        if(b == n3.H)
            print_board(n3.H);
        if((b!=0) && ((b|n3.G) == n3.G)) {
            print_board(n3.G);
        }
    }
    else if(va == 1) {
        uint iz = izquierda(vacios);
         for(int i=pV1; i<=pV4; i++) {
            if(iz == n3[i])
                print_board(n3[i]);
        }
        if((iz != 0) && (n3.G == (iz|n3.G))) {
            cout << "izquierda: " << endl;
            print_board(n3.G);
        }
        uint de = derecha(vacios);
        for(int i=pV1; i<=pV4; i++) {
            if(de == n3[i])
                print_board(n3[i]);
        }
        if((de != 0) && (n3.G == (de|n3.G))) {
            print_board(n3.G);
        }

    }




    return 0;
}

