#pragma once
#include "integers.hpp"

#define ZERO_FLAG_BYTE_POSITION (uint8) 7
#define SUBSTRACT_FLAG_BYTE_POSITION (uint8) 6
#define HALF_CARRY_FLAG_BYTE_POSITION (uint8) 5
#define CARRY_FLAG_BYTE_POSITION (uint8) 4

struct Flags {
    uint8 Z : 1;
    uint8 S : 1;
    uint8 C : 1;
    uint8 H : 1;
    uint8 nothing : 4;
};

class Registers {
    struct {
        union {
            struct {
                Flags f;
                uint8 a;
            };
            uint16 af;
        };
    };
    struct {
        union {
            struct {
                uint8 c;
                uint8 b;
            };
            uint16 bc;
        };
    };
    struct {
        union {
            struct {
                uint8 e;
                uint8 d;
            };
            uint16 de;
        };
    };
    struct {
        union {
            struct {
                uint8 l;
                uint8 h;
            };
            uint16 hl;
        };
    };

public:
    Registers(void);

    

    uint16 get_af(void);
    void set_af(uint16);
    uint16 get_bc(void);
    void set_bc(uint16);
    uint16 get_de(void);
    void set_de(uint16);
    uint16 get_hl(void);
    void set_hl(uint16);

    friend class CPU;
};
