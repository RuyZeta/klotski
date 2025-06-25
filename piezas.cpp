//
// Created by rodrigo on 23/06/25.
//

#include "piezas.h"

nodo::nodo() {
    vco1 = vacio1;
    vco2 = vacio2;
    G = bloqueG;
    V1 = bloqueV1;
    V2 = bloqueV2;
    V3 = bloqueV3;
    V4 = bloqueV4;
    H = horiz;
    s1 = small1;
    s2 = small2;
    s3 = small3;
    s4 = small4;
}

void nodo::print_board() {
    for(int i=19; i>=0; i--) {
        std::cout << " " << letra_bloque(uno<<i) << " ";
        if(!(i%4))
            std::cout << '\n';
    }
    std::cout << '\n';
}

char nodo::letra_bloque(const uint &b) {
    if(b&vco1)
        return '-';
    else if (b&vco2)
        return '-';
    else if(b&G)
        return 'X';
    else if(b&V1)
        return 'I';
    else if(b&V2)
        return 'I';
    else if(b&V3)
        return 'I';
    else if(b&V4)
        return 'I';
    else if(b&H)
        return 'h';
    else if(b&s1)
        return 's';
    else if(b&s2)
        return 's';
    else if(b&s3)
        return 's';
    else if(b&s4)
        return 's';
    return 'F';

}

void nodo::set_board(uint *bd) {
    vco1 = bd[0];
    vco2 = bd[1];
    G = bd[2];
    V1 = bd[3];
    V2 = bd[4];
    V3 = bd[5];
    V4 = bd[6];
    H = bd[7];
    s1 = bd[8];
    s2 = bd[9];
    s3 = bd[10];
    s4 = bd[11];
}

void print_board(const uint& b) {
    for(int i=19; i>=0; i--) {
        std::cout <<((b&(1<<i)) ? " 1 " : " 0 ");
        if(!(i%4))
            std::cout << '\n';
    }
    std::cout << '\n';
}


