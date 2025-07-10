#include <iostream>
#include "piezas.h"
#include <vector>

using namespace std;

typedef vector<uint> lista_pos;
lista_pos PosMoves;


void make_moves(const nodo& n) {
    uint vacios = n.vco1|n.vco2;
    uint va = n.vaciossonAdyacentes();

    if(va == 2) { //horizontales
        uint a = arriba(vacios);
        if(a == n.H)
            PosMoves.push_back(n.H);
        if((a!=0) && (a|n.G) == n.G) {
            PosMoves.push_back(n.G);
        }
        uint b = abajo(vacios);
        if(b == n.H)
            PosMoves.push_back(n.H);
        if((b!=0) && ((b|n.G) == n.G)) {
            PosMoves.push_back(n.G);
        }
    }
    else if(va == 1) {
        // verticales
        uint iz = izquierda(vacios);
        for(int i=pV1; i<=pV4; i++) {
            if(iz == n[i])
                PosMoves.push_back(n[i]);
        }
        if((iz != 0) && (n.G == (iz|n.G))) {

            PosMoves.push_back(n.G);
        }
        uint de = derecha(vacios);
        for(int i=pV1; i<=pV4; i++) {
            if(de == n[i])
                PosMoves.push_back(n[i]);
        }
        if((de != 0) && (n.G == (de|n.G))) {
            PosMoves.push_back(n.G);
        }
    }
        ////// todos los vacios de uno, primero s1 y después s2. No están juntos

    uint movearriba = 0;
    for (int j = 0; j<pG; j++) {
        movearriba = arriba(n[j]);
        for (int i=pV1; i<=ps4; i++) {
             if (i != pH)
                 if((movearriba!=0) && ((movearriba|n[i]) == n[i]))
                        PosMoves.push_back(n[i]);
        }
    }

    uint moveabajo = 0;
    for (int j = 0; j<pG; j++) {
        moveabajo = abajo(n[j]);
        for (int i=pV1; i<=ps4; i++) {
            if (i != pH)
               if((moveabajo!=0) && ((moveabajo|n[i]) == n[i]))
                    PosMoves.push_back(n[i]);
        }
    }

    uint moveizq = 0;
    for (int j = 0; j<pG; j++) {
        moveizq = izquierda(n[j]);
        for (int i=pH; i<=ps4; i++) {
            if((moveizq!=0) && ((moveizq|n[i]) == n[i]))
                PosMoves.push_back(n[i]);
       }
    }

    uint moveder = 0;
    for (int j = 0; j<pG; j++) {
        moveder = derecha(n[j]);
        for (int i=pH; i<=ps4; i++) {
            if((moveder!=0) && ((moveder|n[i]) == n[i]))
                  PosMoves.push_back(n[i]);
        }
    }



}


int main() {
    nodo n1, n2, n3, n4, n5;;
    uint pos[12]  {0x800, 0x400, 0xcc000, 0x22000, 0x220, 0x110, 0x44,
                   0x3, 0x10000, 0x1000, 0x80, 0x8};
    uint pos1[12]  {0x800, 0x80, 0x330, 0x88000, 0x44000, 0x22000, 0x11000,
                    0xc, 0x400, 0x40, 0x2, 0x1};
    uint pos2[12] { 0x8, 0x1, 0x6600, 0x88000, 0x11000, 0x880, 0x110, 0x60000,
                    0x40, 0x20, 0x4, 0x2};
    uint pos3[12] { 0x4000, 0x400, 0x3300, 0x8800, 0x88, 0x22, 0x11, 0x30000,
        0x4, 0x40, 0x40000, 0x80000
    };


    n2.set_board(pos);
    n3.set_board(pos1);
    n4.set_board(pos2);
    n5.set_board(pos3);

    nodo arr[6] {n1, n2, n3, n4, n5 };

    for (int i=0; i<6; i++) {
        make_moves(arr[i]);
        while (!PosMoves.empty()) {
            print_board(PosMoves.back());
            PosMoves.pop_back();
        }
        cin.get();
        std::cout << "\033[2J\033[1;1H";
    }


    cin.get();
    return 0;
}

