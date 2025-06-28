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
static uint first_col = 0x88888;
static uint second_col = 0x44444;
static uint third_col = 0x22222;
static uint fourth_col = 0x11111;
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

static uint GMoves[12] {
                    0xdd3ff,0x669ff, 0xbbcff, 0x3dd3f,
                    0x9669f, 0xcbbcf, 0xf3dd3, 0xf9669,
                    0xfcbbc, 0xff3dd, 0xff966, 0xffcbb
};

static uint VMoves[16] {
                        0xbb7ff, 0x55bff, 0xaadff, 0xddeff,
                        0x7bb7f, 0xb55bf, 0xdaadf, 0xeddef,
                        0xf7bb7, 0xfb55b, 0xfdaad, 0xfedde,
                        0xff7bb, 0xffb55, 0xffdaa, 0xffedd
};

static uint HMoves[15] {
                            0xd3fff, 0x69fff, 0xbcfff,
                            0x3d3ff, 0x969ff, 0xcbcff,
                            0xf3d3f, 0xf969f, 0xfcbcf,
                            0xff3d3, 0xff969, 0xffcbc,
                            0xfff3d, 0xfff96, 0xfffcb
};

static uint SMoves[20] {
    0xb7fff, 0x5bfff, 0xadfff, 0xdefff,
    0x7b7ff, 0xb5bff, 0xdadff, 0xedeff,
    0xf7b7f, 0xfb5bf, 0xfdadf, 0xfedef,
    0xff7b7, 0xffb5b, 0xffdad, 0x8fede,
    0xfff7b, 0xfffb5, 0xfffda, 0xfffed
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
