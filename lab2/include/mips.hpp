#ifndef MIPS_H
#define MIPS_H

#include <stdint.h>
#include <stdio.h>
#include "funcs.hpp"

#define MEM_SIZE 4096

enum OPCODES {
    // lembrem que so sao considerados os 6 primeiros bits dessas constantes.
    EXT=0x00,   LW=0x23,   LB=0x20,   LBU=0x24,
    LH=0x21,    LHU=0x25,  LUI=0x0F,  SW=0x2B,
    SB=0x28,    SH=0x29,   BEQ=0x04,  BNE=0x05,
    BLEZ=0x06,  BGTZ=0x07, ADDI=0x08, SLTI=0x0A,
    SLTIU=0x0B, ANDI=0x0C, ORI=0x0D,  XORI=0x0E,
    J=0x02,     JAL=0x03,
/* enum FUNCT { */
    ADD=0x20, SUB=0x22,     MULT=0x18, DIV=0x1A,
    AND=0x24, OR=0x25,      XOR=0x26,  NOR=0x27,
    SLT=0x2A, JR=0x08,      SLL=0x00,  SRL=0x02,
    SRA=0x03, SYSCALL=0x0c, MFHI=0x10, MFLO=0x12
};

class Mips {
private:
    int pc;
    int32_t mem[MEM_SIZE];
    uint32_t ri;
    uint32_t opcode, rs, rt, rd, shamnt, funct, imm, address;
    uint32_t rb[32];
    uint32_t * text;
    uint32_t * data;

public:
    Mips(const char *, const char *);
    void fetch(){
        ri = mem[pc];
        pc++;
    }
    void decode();
    void execute();
    void step(){ fetch(); decode(); execute(); }
    void dump_mem(int, int, char);
    void dump_reg(char);
};

Mips::Mips(const char* textbin, const char* databin) {
    text = load_binary(textbin);
    data = load_binary(databin);
    pc = 0;
}

void Mips::decode(){
    opcode = ri >> 26;
    rs = (ri >> 21) & 0xf;
    rt = (ri >> 16) & 0xf;
    rd = (ri >> 11) & 0xf;
    shamnt = (ri >> 6) & 0xf;
    funct = ri & 0xff;
    imm = ri & 0x0000FFFF;
    address = (ri & 0x3FFFFFF) << 2;
}

void Mips::execute(){
    switch (opcode) {
        case LW:
            rb[rt] = lw(data, rb[rs], imm);
            break;
        case J:
            pc = (int)address/4;
            break;
        case ADD:
            break;
        case SUB:
            break;
    }
}

void Mips::dump_mem(int start, int end, char format) {
    if (format == 'h')
        for (start = 0; start < end; ++start)
            printf("%x\n", mem[start]);
    else if (format == 'd')
        for (start = 0; start < end; ++start)
            printf("%d\n", mem[start]);
    else
        printf("Invalid format.\n");
}

#endif /* MIPS_H */

/* int32_t lw(uint32_t address, int16_t kte) { */
/*     // => lê um inteiro alinhado - endereços múltiplos de 4 */
/*     int32_t dado = mem[address/4]; */
/*     return dado; */
/* } */

/* int32_t lh(uint32_t address, int16_t kte) { */
/*     // => lê meia palavra, 16 bits - retorna inteiro com sinal */
/*     int32_t dado = (mem[address/4] >> (kte*8)) & 0xFFFF; */
/*     return dado; */
/* } */

/* uint32_t lhu(uint32_t address, int16_t kte) { */
/*     // => lê meia palavra, 16 bits formato inteiro sem sinal */
/*     uint32_t dado = (mem[address/4] >> (kte*8)) & 0xFFFF; */
/*     return dado; */
/* } */

/* int32_t lb(uint32_t address, int16_t kte) { */
/*     // => lê um byte - retorna inteiro com sinal */
/*     int32_t dado = (mem[address/4] >> (kte*8)) & 0xFF; */
/*     return dado; */
/* } */

/* uint32_t lbu(uint32_t address, int16_t kte) { */
/*     // => lê um byte - 8 bits formato inteiro sem sinal */
/*     uint32_t dado = (mem[address/4] >> (kte*8)) & 0xFF; */
/*     return dado; */
/* } */

/* void sw(uint32_t address, int16_t kte, int32_t dado) { */
/*     // => escreve um inteiro alinhado na memória - endereços múltiplos de 4 */
/*     mem[address/4] = dado; */
/* } */

/* void sh(uint32_t address, int16_t kte, int16_t dado) { */
/*     // => escreve meia palavra, 16 bits - endereços múltiplos de 2 */
/*     uint32_t shifter = kte * 8; */
/*     uint32_t mask = ~(0xffff << shifter); */
/*     mem[address/4] = (mem[address/4] & mask) | (dado << shifter); */
/* } */

/* void sb(uint32_t address, int16_t kte, int8_t dado) { */
/*     // => escreve um byte na memória */
/*     uint32_t shifter = kte * 8; */
/*     uint32_t mask = ~(0xff << shifter); */
/*     mem[address/4] = (mem[address/4] & mask) | (dado << shifter); */
/* } */
