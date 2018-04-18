#ifndef MIPS_H
#define MIPS_H

#include <stdint.h>
#include <stdio.h>

#define MEM_SIZE 4096

enum OPCODES {
    // lembrem que so sao considerados os 6 primeiros bits dessas constantes.
    EXT=0x00,   LW=0x23,   LB=0x20,   LBU=0x24,
    LH=0x21,    LHU=0x25,  LUI=0x0F,  SW=0x2B,
    SB=0x28,    SH=0x29,   BEQ=0x04,  BNE=0x05,
    BLEZ=0x06,  BGTZ=0x07, ADDI=0x08, SLTI=0x0A,
    SLTIU=0x0B, ANDI=0x0C, ORI=0x0D,  XORI=0x0E,
    J=0x02,     JAL=0x03, ADDIU=0x09,
/* enum FUNCT { */
    ADD=0x20, SUB=0x22,     MULT=0x18, DIV=0x1A,
    AND=0x24, OR=0x25,      XOR=0x26,  NOR=0x27,
    SLT=0x2A, JR=0x08,      SLL=0x00,  SRL=0x02,
    SRA=0x03, SYSCALL=0x0c, MFHI=0x10, MFLO=0x12
};

class Mips {
private:
    int pc, debug; /* to print debug string */
    uint32_t ri;
    uint32_t op, rs, rt, rd, shamt, funct, imm, address;
    uint32_t rb[32];

public:
    int32_t mem[MEM_SIZE];
    Mips(const char *, const char *);
    void fetch(){
        ri = mem[pc];
        pc++;
    }
    void decode();
    void execute();
    void step() {fetch(); decode(); execute();}
    void dump_mem(int, int, char);
    void dump_reg(char);
    void load_binary(const char*, int32_t);
    int32_t lw(uint32_t, uint32_t);
};

Mips::Mips(const char* textbin, const char* databin) {
    load_binary(textbin, 0x0);
    load_binary(databin, 0x800);
    pc = 0;
    debug = 1;
}

void Mips::decode() {
    op = ri >> 26;
    rs = (ri >> 21) & 0x1f;
    rt = (ri >> 16) & 0x1f;
    rd = (ri >> 11) & 0x1f;
    shamt = (ri >> 6) & 0x1f;
    funct = ri & 0x3f;
    imm = ri & 0xffff;
    address = (ri & 0x3ffffff) << 2;
}

void Mips::execute(){
    switch (op) {
        case EXT:
            switch (funct) {
                case ADD:
                    rb[rd] = rb[rs] + rb[rt];
                    if (debug)
                        printf("[ADD]\n");
                    break;
                default:
                    if (debug)
                        printf("[INVALID FUNCT]");
            }
            break;
        case ADDI:
        case ADDIU:
            rb[rt] = rb[rs] + imm;
            if (debug)
                printf("[ADD/ADDI] rt=%x rs=%x imm=%x\n", rt, rs, imm);
            break;
        case LW:
            rb[rt] = lw(rb[rs], imm);
            if (debug)
                printf("[LW]\n");
            break;
        case J:
            pc = (int)address >> 2;
            if (debug)
                printf("[JUMP] pc=%x\n", pc);
            break;
        case SYSCALL:
            /* TODO */
            if (debug)
                printf("[SYSCALL]\n");
            break;
        case BEQ:
            /* TODO */
            if (debug)
                printf("[BEQ]\n");
            break;
        case SUB:
            /* TODO */
            if (debug)
                printf("[SUB]\n");
            break;
        default:
            if (debug)
                printf("[UNKNOWN]\n");
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

void Mips::load_binary(const char* input, int32_t begin){
    FILE* inlet = fopen(input, "rb");

    while (!feof(inlet)) {
        fread(&mem[begin], sizeof(int32_t), 1, inlet);
        begin++;
    }
    fclose(inlet);
}

int32_t Mips::lw(uint32_t rs, uint32_t imm) {
    if (rs % 4 != 0 || imm % 4 != 0) {
        printf("[error] not alligned memory point.");
        return 0;
    }
  	return mem[(rs + imm) >> 2]; //+2048?
}

#endif /* MIPS_H */
