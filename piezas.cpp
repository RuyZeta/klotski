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

nodo::nodo(const nodo &n) {
    vco1 = n.vco1;
    vco2 = n.vco2;
    G = n.G;
    V1 = n.V1;
    V2 = n.V2;
    V3 = n.V3;
    V4 = n.V4;
    H = n.H;
    s1 = n.s1;
    s2 = n.s2;
    s3 = n.s3;
    s4 = n.s4;
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

/////////////////////////////////////////////
/// clase busca
///



busca::busca(const nodo &n) {
    raiz = new nodo(n);
}

void busca::hace_movida(const nodo& n) {
    uint vacios = n.vco1|n.vco2;
    uint va = n.vaciossonAdyacentes();

    if(va == 2) { //horizontales
        uint a = arriba(vacios);
        if(a == n.H) { //la barra horizontal está arriba de vacios
            nodo* nod = new nodo(n);
            nod->vco1 = arriba(n.vco1);
            nod->vco2 = arriba(n.vco2);
            nod->H = vacios;
            movidas.push(nod);
        }
        if((a!=0) && (a|n.G) == n.G) {  // el bloque grande está arriba de vacios
            nodo* nod = new nodo(n);
            nod->vco1 = arriba(arriba(n.vco1));
            nod->vco2 = arriba(arriba(n.vco2));
            nod->G = (n.G|vacios) & ~(nod->vco1|nod->vco2);
            movidas.push(nod);
        }
        uint b = abajo(vacios);
        if(b == n.H) { //barra horizontal está abajo de vacios
            nodo* nod = new nodo(n);
            nod->vco1 = abajo(n.vco1);
            nod->vco2 = abajo(n.vco2);
            nod->H = vacios;
            movidas.push(nod);
        }

        if((b!=0) && ((b|n.G) == n.G)) { //el bloque grande está abajo de vacios
            nodo* nod = new nodo(n);
            nod->vco1 = abajo(abajo(n.vco1));
            nod->vco2 = abajo(abajo(n.vco2));
            nod->G = (n.G|vacios) & ~(nod->vco1|nod->vco2);
            movidas.push(nod);
        }
    }
    else if(va == 1) {
        // verticales
        uint iz = izquierda(vacios);
        uint de = derecha(vacios);
        for(int i=pV1; i<=pV4; i++) {
            //las barras verticales están a la izquierda de vacios
            if(iz == n[i]) {
                nodo* nod = new nodo(n);
                nod->vco1 = izquierda(n.vco1);
                nod->vco2 = izquierda(n.vco2);
                *(&nod->vco1+i) = vacios; // resulta?
                movidas.push(nod);
            }
            if(de == n[i]) {
                nodo* nod = new nodo(n);
                nod->vco1 = derecha(n.vco1);
                nod->vco2 = derecha(n.vco2);
                *(&nod->vco1+i) = vacios;
                movidas.push(nod);
            }
        }
        if((iz != 0) && (n.G == (iz|n.G))) { // el bloque está a la izquierda de vacios
                nodo* nod = new nodo(n);
                nod->vco1 = izquierda(izquierda(n.vco1));
                nod->vco2 = izquierda(izquierda(n.vco2));
                nod->G = (n.G|vacios) & ~(nod->vco1|nod->vco2);
                movidas.push(nod);
        }

        if((de != 0) && (n.G == (de|n.G))) { // el bloque está a la derecha de vacios verticalmente
                nodo* nod = new nodo(n);
                nod->vco1 = derecha(derecha(n.vco1));
                nod->vco2 = derecha(derecha(n.vco2));
                nod->G = (n.G|vacios) & ~(nod->vco1|nod->vco2);
                movidas.push(nod);
        }

    }
    //////////////////////////////// todos los vacios de uno, primero s1 y después s2. No están juntos

    uint movearriba = 0;
    uint moveabajo = 0;
    uint moveizq = 0; //izquierda derecha incluye la horizontal y las pequeñas
    uint moveder = 0;

    for (int j = 0; j<pG; j++) {
        movearriba = arriba(n[j]);
        moveabajo = abajo(n[j]);
        moveizq = izquierda(n[j]);
        moveder = derecha(n[j]);
        for (int i=pV1; i<=ps4; i++) {
            if((i != pH) && ((movearriba!=0) && ((movearriba|n[i]) == n[i]))) {
                ////// arriba del vacio están las barras verticales o los cuadrados chicos ////
                if (i<pH) { // barras verticales arriba
                    nodo* nod = new nodo(n);
                    *(&nod->vco1+j) = arriba(arriba(n[j]));
                    *(&nod->vco1+i) = (n[i]|n[j]) & ~(*(&nod->vco1+j));
                    movidas.push(nod);
                }
                if (i>pH) { // un cuadrado chico arriba de vacio
                    nodo* nod = new nodo(n);
                    *(&nod->vco1+j) = arriba(n[j]);
                    *(&nod->vco1+i) = n[j];
                    movidas.push(nod);
                }
            }
            if((i != pH) && ((moveabajo!=0) && ((moveabajo|n[i]) == n[i]))) { //barras verticales abajo
                if (i<pH) { // barras verticales abajo
                    nodo* nod = new nodo(n);
                    *(&nod->vco1+j) = abajo(abajo(n[j]));
                    *(&nod->vco1+i) = (n[i]|n[j]) & ~(*(&nod->vco1+j));
                    movidas.push(nod);
                }
                if (i>pH) { // un cuadrado chico abajo de vacio
                    nodo* nod = new nodo(n);
                    *(&nod->vco1+j) = abajo(n[j]);
                    *(&nod->vco1+i) = n[j];
                    movidas.push(nod);
                }
            }
        }

        for (int i=pH; i<=ps4; i++) {
            if((moveizq!=0) && ((moveizq|n[i]) == n[i])) {
                    if (i==pH) { //barra horizontal a la izquierda
                        nodo* nod = new nodo(n);
                        *(&nod->vco1+j) = izquierda(izquierda(n[j]));
                        *(&nod->vco1+i) = (n[i]|n[j]) & ~(*(&nod->vco1+j));
                        movidas.push(nod);
                    }
                    if (i > pH) { // cuadrados chicos a la izquierda
                        nodo* nod = new nodo(n);
                        *(&nod->vco1+j) = izquierda(n[j]);
                        *(&nod->vco1+i) = n[j];
                        movidas.push(nod);
                    }
                }
                if((moveder!=0) && ((moveder|n[i]) == n[i])) {
                    if (i==pH) { //barra horizontal a la derecha
                        nodo* nod = new nodo(n);
                        *(&nod->vco1+j) = derecha(derecha(n[j]));
                        *(&nod->vco1+i) = (n[i]|n[j]) & ~(*(&nod->vco1+j));
                        movidas.push(nod);
                    }
                    if (i > pH) { // cuadrados chicos a la derecha
                        nodo* nod = new nodo(n);
                        *(&nod->vco1+j) = derecha(n[j]);
                        *(&nod->vco1+i) = n[j];
                        movidas.push(nod);
                    }
                }
            }
    }
}

void busca::run() {
    hace_movida(*raiz);
    while (!movidas.empty()) {
        nodo *temp = movidas.front();
        movidas.pop();
        if (temp->G == GObjetivo) {
            std::cout << "encontrado" << std::endl;
            break;
        }
        else {
            temp->print_board();
            std::cin.get();
            hace_movida(*temp);
        }
    }
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