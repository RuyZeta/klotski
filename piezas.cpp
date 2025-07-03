//
// Created by rodrigo on 23/06/25.
//

#include "piezas.h"

#include <iomanip>

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

void nodo::print_board() const {
    for(int i=19; i>=0; i--) {
        std::cout << " " << letra_bloque(uno<<i) << " ";
        if(!(i%4))
            std::cout << '\n';
    }
    std::cout << '\n';
}



char nodo::letra_bloque(const uint &b) const {
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

uint nodo::get_fichaPos(uint f) const {
    const uint* temp = &vco1;
    temp+=f;
    return *temp;
    //return *(&vco1 + f);
}

//return 2 si son horizontales, 1 si son verticales, 0 si no son adyacentes
uint nodo::vaciossonAdyacentes() const {
    if(((vco1>>1) & ~first_col) == vco2)
        return 2;
    else if((((vco1<<1) & ~fourth_col) & fullBoard) == vco2)
        return 2;
    else if((((vco1<<4) & ~fifth_line)) == vco2)
        return 1;
    else if((vco1>>4) == vco2)
        return 1;
    else
        return 0;
}

////////////////////////////////////
////////////////////////////////////
void print_board(const uint& b) {
    std::cout  << "hex: " << std::hex << b <<
               " dec: " << std::dec << b << std::endl;
    for(int i=19; i>=0; i--) {
        std::cout <<((b&(1<<i)) ? "1 " : "0 ");
        if(!(i%4))
            std::cout << '\n';
    }
    std::cout << '\n';
}


void print_bin(const uint &b, std::string s) {
    std::cout  << "  hex: " << std::left << std::hex << std::setw(10) << b <<
    " dec: " << std::dec << std::setw(10) << b << " :  ";
    for(int i=31; i>=0; i--) {
        std::cout << ((b&(1<<i)) ? "1 " : "0 ");
        if(!(i%4))
            std::cout << "  ";
    }
    std::cout << "   " << s << std::endl;

}



uint maskmoves(const uint& g) {
    uint derecha = ((g>>1) & (~g)) & (~first_col);
    uint izquierda = ((g<<1) & (~g)) & (~fourth_col);
    uint abajo = (g>>4) & (~g);
    uint arriba = ((g<<4) & (~g)) & (fullBoard);
    return (derecha | izquierda | abajo | arriba);
}

////////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////// bits hacks /////////////////////////

uint MSB(const uint &n) {
    uint i = n;
    // llena de 1s desde el bit más significativo hasta el primer 0
    i |= (i >> 1);
    i |= (i >> 2);
    i |= (i >> 4);
    i |= (i >> 8);
    i |= (i >> 16);
    // suma 1, así solo está seteado una posición más allá del bit más significativo
    i = i+1;
    // desplaza a la derecha 1 bit, que es la posición del bit más significativo
    return (i >> 1);
}

uint LSB(const uint &n) {
    return (n & -n); // obtiene el bit menos significativo
}

uint clearLSB(const uint &n) {
    return (n & (n - 1)); // limpia el bit menos significativo
}

uint clearibitsfromLSB(uint n, const uint &i) {
    n = n & ~((1 << i+1 ) - 1);
    return n;
}

uint clearbitsfromMSB(uint n, const uint &i) {
    n = n & ((1 << i) - 1);
    return n;
}

uint propagateLSB(const uint& n) {
    uint x = n | (n-1);
    return x;
}

uint popcount(const uint &n) {
    uint n1 = n;
    int i = 0;
    while(n) {
        n1 &= (n1 - 1); // elimina el bit menos significativo
        i++;
    }
    return i;
}