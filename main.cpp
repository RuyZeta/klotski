#include <iostream>
#include "piezas.h"
#include <queue>
#include <vector>
using namespace std;

typedef vector<uint> lista_uint;
lista_uint posmove;



void make_move(const nodo& n) {
    n.print_board();
    uint vacios = n.vco1|n.vco2;
    uint va = n.vaciossonAdyacentes();
    if(va == 2) {
        uint a = arriba(vacios); //arriba
        if(a == n.H)
            posmove.push_back(n.H);
        if((a!=0) && (a|n.G) == n.G)
            posmove.push_back(n.G);

        uint b = abajo(vacios); //abajo
        if(b == n.H)
            posmove.push_back(n.H);
        if((b!=0) && ((b|n.G) == n.G))
            posmove.push_back(n.G);

    }
    else if(va == 1) {
        uint iz = izquierda(vacios); //izquierda
        for(int i=pV1; i<=pV4; i++) {
            if(iz == n[i])
                posmove.push_back(n[i]);
        }
        if((iz != 0) && (n.G == (iz|n.G)))
            posmove.push_back(n.G);

        uint de = derecha(vacios); //derecha
        for(int i=pV1; i<=pV4; i++) {
            if(de == n[i])
                posmove.push_back(n[i]);
        }
        if((de != 0) && (n.G == (de|n.G))) {
            posmove.push_back(n.G);
        }

    }
    
}

int main() {
    nodo n1, n2, n3, n4, n5;
    uint pos[12]  {0x800, 0x400, 0xcc000, 0x22000, 0x220, 0x110, 0x44,
                   0x3, 0x10000, 0x1000, 0x80, 0x8};
    uint pos1[12]  {0x800, 0x80, 0x330, 0x88000, 0x44000, 0x22000, 0x11000,
                    0xc, 0x400, 0x40, 0x2, 0x1};
    uint pos2[12] { 0x8, 0x1, 0x6600, 0x88000, 0x11000, 0x880, 0x110, 0x60000,
                    0x40, 0x20, 0x4, 0x2};

    uint pos3[12] { 0x4000, 0x400, 0x3300, 0x8800, 0x88, 0x11, 0x22, 0x30000, 0x80000, 0x40000, 0x40, 0x4 };


    n2.set_board(pos);
    n3.set_board(pos1);
    n4.set_board(pos2);
    n5.set_board(pos3);

    uint a = 234;
    uint b = 456;
    uint m = 0b10001001010011010000;


    uint vacios = n3.vco1|n3.vco2;
    uint va = n3.vaciossonAdyacentes();



    make_move(n5);
    while(!posmove.empty()) {
        print_board(posmove.back());
        posmove.pop_back();
    }




    return 0;
}

