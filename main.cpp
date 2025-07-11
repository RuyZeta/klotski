#include <iostream>
#include "piezas.h"
#include <vector>

using namespace std;

lista_nodos Nodos;


void make_moves(nodo& n) {
    uint vacios = n.vco1|n.vco2;
    uint va = n.vaciossonAdyacentes();

    if(va == 2) { //horizontales
        uint a = arriba(vacios);
        if(a == n.H) { //la barra horizontal está arriba de vacios
            nodo* nod = new nodo(n);
            nod->vco1 = arriba(n.vco1);
            nod->vco2 = arriba(n.vco2);
            nod->H = vacios;
            Nodos.push_back(nod);
        }
        if((a!=0) && (a|n.G) == n.G) {  // el bloque grande está arriba de vacios
            nodo* nod = new nodo(n);
            nod->vco1 = arriba(arriba(n.vco1));
            nod->vco2 = arriba(arriba(n.vco2));
            nod->G = (n.G|vacios) & ~(nod->vco1|nod->vco2);
            Nodos.push_back(nod);
        }
        uint b = abajo(vacios);
        if(b == n.H) { //barra horizontal está abajo de vacios
            nodo* nod = new nodo(n);
            nod->vco1 = abajo(n.vco1);
            nod->vco2 = abajo(n.vco2);
            nod->H = vacios;
            Nodos.push_back(nod);
        }

        if((b!=0) && ((b|n.G) == n.G)) { //el bloque grande está abajo de vacios
            nodo* nod = new nodo(n);
            nod->vco1 = abajo(abajo(n.vco1));
            nod->vco2 = abajo(abajo(n.vco2));
            nod->G = (n.G|vacios) & ~(nod->vco1|nod->vco2);
            Nodos.push_back(nod);
        }
    }
    else if(va == 1) {
        // verticales
        uint iz = izquierda(vacios);
        for(int i=pV1; i<=pV4; i++)  //las barras verticales están a la izquierda de vacios
            if(iz == n[i]) {
                nodo* nod = new nodo(n);
                nod->vco1 = izquierda(n.vco1);
                nod->vco2 = izquierda(n.vco2);
                *(&nod->vco1+i) = vacios; // resulta?
                Nodos.push_back(nod);
            }

        if((iz != 0) && (n.G == (iz|n.G))) { // el bloque está a la izquierda de vacios
            nodo* nod = new nodo(n);
            nod->vco1 = izquierda(izquierda(n.vco1));
            nod->vco2 = izquierda(izquierda(n.vco2));
            nod->G = (n.G|vacios) & ~(nod->vco1|nod->vco2);
            Nodos.push_back(nod);
        }

        uint de = derecha(vacios);
        for(int i=pV1; i<=pV4; i++)  // las barras verticales están a la derecha de vacios
            if(de == n[i]) {
                nodo* nod = new nodo(n);
                nod->vco1 = derecha(n.vco1);
                nod->vco2 = derecha(n.vco2);
                *(&nod->vco1+i) = vacios;
                Nodos.push_back(nod);
            }

        if((de != 0) && (n.G == (de|n.G))) { // el bloque está a la izquierda de vacios verticalmente
            nodo* nod = new nodo(n);
            nod->vco1 = derecha(derecha(n.vco1));
            nod->vco2 = derecha(derecha(n.vco2));
            nod->G = (n.G|vacios) & ~(nod->vco1|nod->vco2);
            Nodos.push_back(nod);
        }
    }
//////////////////////////////// todos los vacios de uno, primero s1 y después s2. No están juntos

    uint movearriba = 0;
    for (int j = 0; j<pG; j++) {
        movearriba = arriba(n[j]);
        for (int i=pV1; i<=ps4; i++)
             if((i != pH) && ((movearriba!=0) && ((movearriba|n[i]) == n[i]))) {
                 ////// arriba del vacio están las barras verticales o los cuadrados chicos ////
                 if (i<pH) { // barras verticales arriba
                     nodo* nod = new nodo(n);
                     *(&nod->vco1+j) = arriba(arriba(n[j]));
                     *(&nod->vco1+i) = (n[i]|n[j]) & ~(*(&nod->vco1+j));
                     Nodos.push_back(nod);
                 }
                 if (i>pH) { // un cuadrado chico arriba de vacio
                     nodo* nod = new nodo(n);
                     *(&nod->vco1+j) = arriba(n[j]);
                     *(&nod->vco1+i) = n[j];
                     Nodos.push_back(nod);
                 }
             }
    }
    uint moveabajo = 0;
    for (int j = 0; j<pG; j++) {
        moveabajo = abajo(n[j]);
        for (int i=pV1; i<=ps4; i++)
            if((i != pH) && ((moveabajo!=0) && ((moveabajo|n[i]) == n[i]))) { //barras verticales abajo
                if (i<pH) { // barras verticales abajo
                    nodo* nod = new nodo(n);
                    *(&nod->vco1+j) = abajo(abajo(n[j]));
                    *(&nod->vco1+i) = (n[i]|n[j]) & ~(*(&nod->vco1+j));
                    Nodos.push_back(nod);
                }
                if (i>pH) { // un cuadrado chico abajo de vacio
                    nodo* nod = new nodo(n);
                    *(&nod->vco1+j) = abajo(n[j]);
                    *(&nod->vco1+i) = n[j];
                    Nodos.push_back(nod);
                }
            }
    }

    uint moveizq = 0; //izquierda derecha incluye la horizontal y las pequeñas
    for (int j = 0; j<pG; j++) {
        moveizq = izquierda(n[j]);
        for (int i=pH; i<=ps4; i++)
            if((moveizq!=0) && ((moveizq|n[i]) == n[i])) {
                if (i==pH) { //barra horizontal a la izquierda
                    nodo* nod = new nodo(n);
                    *(&nod->vco1+j) = izquierda(izquierda(n[j]));
                    *(&nod->vco1+i) = (n[i]|n[j]) & ~(*(&nod->vco1+j));
                    Nodos.push_back(nod);
                }
                if (i > pH) { // cuadrados chicos a la izquierda
                    nodo* nod = new nodo(n);
                    *(&nod->vco1+j) = izquierda(n[j]);
                    *(&nod->vco1+i) = n[j];
                    Nodos.push_back(nod);
                }
            }
    }

    uint moveder = 0;
    for (int j = 0; j<pG; j++) {
        moveder = derecha(n[j]);
        for (int i=pH; i<=ps4; i++) {
            if((moveder!=0) && ((moveder|n[i]) == n[i])) {
                if (i==pH) { //barra horizontal a la derecha
                    nodo* nod = new nodo(n);
                    *(&nod->vco1+j) = derecha(derecha(n[j]));
                    *(&nod->vco1+i) = (n[i]|n[j]) & ~(*(&nod->vco1+j));
                    Nodos.push_back(nod);
                }
                if (i > pH) { // cuadrados chicos a la derecha
                    nodo* nod = new nodo(n);
                    *(&nod->vco1+j) = derecha(n[j]);
                    *(&nod->vco1+i) = n[j];
                    Nodos.push_back(nod);
                }
            }
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

    busca sol(n1);
    sol.run();





    return 0;
}

