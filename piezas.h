//
// Created by rodrigo on 23/06/25.
//

#ifndef PIEZAS_H
#define PIEZAS_H

#include <iostream>
#include <string>
#include <cassert>
#include <iomanip>

typedef unsigned int uint;

#define uno ((uint)1)
typedef uint board;
#define TotFichas 12
#define pvco1 0
#define pvco2 1
#define pG   2
#define pV1  3
#define pV2  4
#define pV3  5
#define pV4  6
#define pH   7
#define ps1  8
#define ps2  9
#define ps3  10
#define ps4  11
//board and tiles definitions for initials positions
static uint fullBoard = 0xfffff;
static uint first_line = 0xf;
static uint second_line = 0xf0;
static uint third_line = 0xf00;
static uint fourth_line = 0xf000;
static uint fifth_line = 0xf0000;
static uint first_col = 0x88888888;
static uint second_col = 0x44444444;
static uint third_col = 0x22222222;
static uint fourth_col = 0x11111111;
static uint bloqueG = 0x66000;
static uint bloqueV1 = 0x88000;
static uint bloqueV2 = 0x11000;
static uint bloqueV3 = 0x88;
static uint bloqueV4 = 0x11;
static uint small1 = 0x800;
static uint small2 = 0x100;
static uint small3 = 0x40;
static uint small4 = 0x20;
static uint horiz = 0x600;
static uint vacio1 = 0x4;
static uint vacio2 = 0x2;



static uint bloqueGpos[12] = {
        0x33,       0x33<<1,    0x33<<2,
        0x33<<4,    0x33<<5,    0x33<<6,
        0x33<<8,    0x33<<9,    0x33<<10,
        0x33<<12,   0x33<<13,   0x33<<14
};
static uint bloqueHpos[15] {
        0x3,       0x3<<1,     0x3<<2,
        0x3<<4,    0x3<<5,     0x3<<6,
        0x3<<8,    0x3<<9,     0x3<<10,
        0x3<<12,   0x3<<13,    0x3<<14,
        0x3<<16,   0x3<<17,    0x3<<18
};

static uint bloqueVpos[16] {
        0x11,     0x11<<1,    0x11<<2, 0x11<<3,
        0x11 << 4, 0x11 << 5, 0x11 << 6, 0x11 << 7,
        0x11 << 8, 0x11 << 9, 0x11 << 10, 0x11 << 11,
        0x11 << 12, 0x11 << 13, 0x11 << 14, 0x11 << 15

};

#define sq20    (uno<<19)
#define sq19    (uno<<18)
#define sq18    (uno<<17)
#define sq17    (uno<<16)
#define sq16    (uno<<15)
#define sq15    (uno<<14)
#define sq14    (uno<<13)
#define sq13    (uno<<12)
#define sq12    (uno<<11)
#define sq11    (uno<<10)
#define sq10    (uno<<9)
#define sq9     (uno<<8)
#define sq8     (uno<<7)
#define sq7     (uno<<6)
#define sq6     (uno<<5)
#define sq5     (uno<<4)
#define sq4     (uno<<3)
#define sq3     (uno<<2)
#define sq2     (uno<<1)
#define sq1     (uno<<0)

struct nodo {
    uint vco1, vco2, G, V1, V2, V3, V4, H, s1, s2, s3, s4;
    nodo();
    void print_board() const;
    char letra_bloque(const uint& b) const;
    void set_board(uint* bd);
    uint get_fichaPos(uint f) const;
    uint vaciossonAdyacentes() const;
    uint& operator[] (const uint& index) {
        assert((index < TotFichas) && "error de limite array fichas");
        return *(&vco1+index);
    }
};

uint maskmoves(const uint& g);
void print_board(const uint& b);
void print_bin(const uint& b, std::string s="");

//bit manipulation functions BIT HACKS
//most significant bit
uint MSB(const uint& n);
//least significant bit
uint LSB(const uint& n);
//clear the least significant bit
uint clearLSB(const uint& n);
//clear bits from LSB to the i-th bit
uint clearibitsfromLSB( uint n, const uint& i);
//clear bits from MSB to the i-th bit
uint clearbitsfromMSB(uint n, const uint& i);
//popcount kerniggan
uint popcount(const uint& n);
//propagate the least significant bit
uint propagateLSB(const uint& n);

#endif //PIEZAS_H
