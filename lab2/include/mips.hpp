#ifndef MIPS_H
#define MIPS_H

#include <stdint.h>
#include <stdio.h>

#define MEM_SIZE 4096
#define BEBUG_MODE 0 /* 0- no debug 1- basic debug 2- full debug */


enum OPCODES {
    // lembrem que so sao considerados os 6 primeiros bits dessas constantes.
    EXT=0x00,   LW=0x23,   LB=0x20,   LBU=0x24,
    LH=0x21,    LHU=0x25,  LUI=0x0F,  SW=0x2B,
    SB=0x28,    SH=0x29,   BEQ=0x04,  BNE=0x05,
    BLEZ=0x06,  BGTZ=0x07, ADDI=0x08, SLTI=0x0A,
    SLTIU=0x0B, ANDI=0x0C, ORI=0x0D,  XORI=0x0E,
    J=0x02,     JAL=0x03,  ADDIU=0x09
};

enum FUNCT {
    ADD=0x20, SUB=0x22,     MULT=0x18, DIV=0x1A,
    AND=0x24, OR=0x25,      XOR=0x26,  NOR=0x27,
    SLT=0x2A, JR=0x08,      SLL=0x00,  SRL=0x02,
    SRA=0x03, SYSCALL=0x0c, MFHI=0x10, MFLO=0x12,
    UNKNOWN,  NOP
};

class Mips {
private:
    int pc, debug; /* to print debug string */
    uint32_t ri, op, rs, rt, rd, shamt, funct, address, hi, lo;
    uint32_t rb[32];
    int16_t imm;

public:
    uint32_t mem[MEM_SIZE];
    Mips(const char *, const char *);
    void fetch(){
        ri = mem[pc];
        pc++;
    }
    void decode();
    void execute();
    void step() {fetch(); decode(); execute();}
    void run();
    void dump_mem(int, int, char);
    void dump_reg(char);
    void load_binary(const char*, int32_t);
    int32_t lb(uint32_t, int16_t);
    int32_t lh(uint32_t, int16_t);
    int32_t lw(uint32_t, int16_t);
    uint32_t lbu(uint32_t, int16_t);
    uint32_t lhu(uint32_t, int16_t);
    void sb(uint32_t, int16_t, int8_t);
    void sh(uint32_t, int16_t, int16_t);
    void sw(uint32_t, int16_t, int32_t);
    void syscall();
    void syscall4(uint32_t);
    uint32_t decode_inst(uint32_t);
};

Mips::Mips(const char* textbin, const char* databin) {
    pc = 0;
    debug = BEBUG_MODE;
    load_binary(textbin, 0x0);
    load_binary(databin, 0x800);
    for (int i = 0; i < 32; ++i)
        rb[32] = 0x0;
}

void Mips::run() {
    int counter = 0;
    do {
        step();
        counter++;
        if (debug > 1) {
            printf("----------[COUNTER]=%d\n", counter);
            for (int i = 0; i < 32; ++i)
                printf("REGISTER $%d=%x\n", i, rb[i]);
        }
        if (counter == 110 && debug)
            break;
    } while (rb[2] != 0xa && pc < MEM_SIZE);
    printf("\n");
}

void Mips::decode() {
    rs = (ri >> 21) & 0xf;
    rt = (ri >> 16) & 0xf;
    rd = (ri >> 11) & 0xf;
    shamt = (ri >> 6) & 0xf;
    funct = ri & 0xff;
    op = decode_inst(ri);
    imm = ri;
    address = (ri << 6) >> 6;
}

uint32_t Mips::decode_inst(uint32_t inst) {
    int funct, name = UNKNOWN;

    if (inst == 0xc) return SYSCALL;
    else if (inst == 0x0) return NOP;

    op= inst >> 26; funct = inst & 0x3f;

    switch (op) {
        case 0x0:
            switch (funct) {
                case 0x20: name = ADD; break;
                default: name = NOP;
            }
            break;
        default:
            name = op;
    }
    return name;
}

void Mips::execute(){
    switch (op) {
        case EXT:
            switch (funct) {
                case 0x20: op = ADD; break;
                default: op = NOP;
            }
            break;
        case ADD:
            rb[rd] = rb[rs] + rb[rt];
            if (debug)
                printf("[ADD] $%d $%d=%x $%d=%x\n", rd, rs, rb[rs], rt, rb[rt]);
            break;
        case ADDI:
        case ADDIU:
            rb[rt] = rb[rs] + imm;
            if (debug)
                printf("[ADDI] $%d $%d=%x imm=%x\n", rt, rs, rb[rs], imm);
            break;
        case LW:
            rb[rt] = lw(rb[rs], imm);
            if (debug)
                printf("[LW] $%d=%x pos=%x elem=%x imm=%x\n", rt, rb[rt], rs, rb[rs], imm);
            break;
        case J:
            pc = address;// >> 2;
            if (debug)
                printf("[JUMP] pc=%x\n", pc);
            break;
        case SYSCALL:
            syscall();
            if (debug)
                printf("[SYSCALL] $2=%x $4=%x\n", rb[2], rb[4]);
            break;
        case BEQ:
            if (rb[rs] == rb[rt])
                pc += imm;
            if (debug)
                printf("[BEQ] $%d=%x $%d=%x address=%x\n", rs, rb[rs],
                                                           rt, rb[rt], pc);
            break;
        case SUB:
            rb[rd] = rb[rs] - rb[rt];
            if (debug)
                printf("[SUB]\n");
            break;
        default:
            if (debug)
            printf("[UNKNOWN] opcode=%x\n", op);
    }
}

void Mips::dump_mem(int start, int end, char format) {
    if (format == 'h')
        for (start; start <= end; ++start)
            printf("MEM[%d]=%x\n", start, mem[start]);
    else if (format == 'd')
        for (start; start <= end; ++start)
            printf("MEM[%d]=%d\n", start, mem[start]);
    else
        printf("Invalid format.\n");
}

void Mips::dump_reg(char format) {
    if (format == 'h') {
        for (int i = 0; i < 32; ++i)
            printf("RB[%d]=%x", i, rb[i]);
        printf("pc=%x hi=%x lo=%x", pc, hi, lo);
    }
    else if (format == 'd'){
        for (int i = 0; i < 32; ++i)
            printf("RB[%d]=%d", i, rb[i]);
        printf("pc=%d hi=%d lo=%d", pc, hi, lo);
    }
    else
        printf("Invalid format.\n");
}

void Mips::load_binary(const char* input, int32_t begin){
    FILE* inlet = fopen(input, "rb");

    while (!feof(inlet)) {
        fread(&mem[begin], sizeof(uint32_t), 1, inlet);
        if (debug>1)
            printf("MEM[%d] %x\n", begin, mem[begin]);
        begin++;
    }
    fclose(inlet);
}

int32_t Mips::lw(uint32_t rbrs, int16_t cons) {
    if (rbrs % 4 != 0 || cons % 4 != 0) {
        printf("[error] not alligned memory point.");
        return -2;
    }
    if (debug)
        printf("LOADWORD = %d\n", (rbrs + cons) >> 2);
  	return mem[(rbrs + cons) >> 2]; //+2048?
}

int32_t Mips::lh(uint32_t rbrs, int16_t cons) {
    if (rbrs % 4 != 0 || cons % 4 != 0) {
        printf("[error] not alligned memory point.");
        return -2;
    }
    if (debug)
        printf("LOADWORD = %d\n", (rbrs + cons) >> 2);
  	return (mem[(rbrs + cons) >> 2] >> (cons*8)) & 0xffff;
}

int32_t Mips::lb(uint32_t rbrs, int16_t cons) {
    if (rbrs % 4 != 0 || cons % 4 != 0) {
        printf("[error] not alligned memory point.");
        return -2;
    }
    if (debug)
        printf("LOADWORD = %d\n", (rbrs + cons) >> 2);
  	return (mem[(rbrs + cons) >> 2] >> (cons*8)) & 0xff;
}

uint32_t Mips::lhu(uint32_t rbrs, int16_t cons) {
    return lh(rbrs, cons);
}

uint32_t Mips::lbu(uint32_t rbrs, int16_t cons) {
    return lb(rbrs, cons);
}

void Mips::sw(uint32_t address, int16_t kte, int32_t dado) {
    // => escreve um inteiro alinhado na memória - endereços múltiplos de 4
    mem[address/4] = dado;
}

void Mips::sh(uint32_t address, int16_t kte, int16_t dado) {
    // => escreve meia palavra, 16 bits - endereços múltiplos de 2
    uint32_t shifter = kte * 8;
    uint32_t mask = ~(0xffff << shifter);
    mem[address/4] = (mem[address/4] & mask) | (dado << shifter);
}

void Mips::sb(uint32_t address, int16_t kte, int8_t dado) {
    // => escreve um byte na memória
    uint32_t shifter = kte * 8;
    uint32_t mask = ~(0xff << shifter);
    mem[address/4] = (mem[address/4] & mask) | (dado << shifter);
}

void Mips::syscall() {
    long v0 = rb[2];
    long a0 = rb[4];
    rb[1] = 0;

    switch (v0) {
        case 1:
            printf("%ld", a0);
            if (debug)
                printf("\n");
            break;
        case 4:
            syscall4((a0)/4);
            break;
        case 5:
            scanf("%ld", &v0);
            rb[2] = v0;
            break;
        case 10:
            if (debug)
                printf("--sycall exit\n");
            break;
        default:
            if (debug)
                printf("--syscall unknown $2=%ld\n", v0);
    }
}

void Mips::syscall4(uint32_t a0) {
    unsigned char c = '\0';
    int i = 0;

    c = (mem[a0+(i/4)] >> 8*(i % 4)) & 0xff;
    while (c != '\0') {
        printf("%c", c);
        i++;
        c = (mem[a0+(i/4)] >> 8*(i % 4)) & 0xff;
    }
    if (debug)
        printf("\n");
}


#endif /* MIPS_H */
