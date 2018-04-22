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
    uint32_t ri;
    uint32_t op, rs, rt, rd, shamt, funct, imm, address;
    uint32_t rb[32];
    int32_t k16;
    uint32_t k26;

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
    uint32_t lw(uint32_t, uint32_t);
    void syscall();
    void syscall4(uint32_t);
    uint32_t sign_imm(uint32_t);
    uint32_t decode_inst(uint32_t);
};

Mips::Mips(const char* textbin, const char* databin) {
    pc = 0;
    debug = 0; /* 0- no debug 1- basic debug 2- full debug */
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
    /* rs = (ri << 6) >> 27; */
    /* rt = (ri << 11) >> 27; */
    /* rd = (ri << 16) >> 27; */
    rs = (ri >> 21) & 0xf;
    rt = (ri >> 16) & 0xf;
    rd = (ri >> 11) & 0xf;
    shamt = (ri >> 6) & 0xf;
    /* funct = ri & 0xff; */
    funct = ri << 26;
    funct = funct >> 26;
    /* imm = ri & 0x0000ffff; */
    /* address = (ri & 0x3ffffff) << 2; */
    op = decode_inst(ri);
    k16 = ri << 16;
    k16 = k16 >> 16;
    k26 = ri << 6;
    k26 = k26 >> 6;
    address = k26;
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
            rb[rt] = rb[rs] + k16;//sign_imm(imm);
            if (debug)
                printf("[ADDI] $%d $%d=%x imm=%x\n", rt, rs, rb[rs], sign_imm(imm));
            break;
        case LW:
            rb[rt] = lw(rb[rs], k16);//sign_imm(imm));
            if (debug)
                printf("[LW] $%d=%x pos=%x elem=%x imm=%x\n", rt, rb[rt], rs, rb[rs], sign_imm(imm));
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
                pc += k16;
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
        fread(&mem[begin], sizeof(uint32_t), 1, inlet);
        if (debug)
            printf("MEM[%d] %x\n", begin, mem[begin]);
        begin++;
    }
    fclose(inlet);
}

uint32_t Mips::lw(uint32_t rs, uint32_t imm) {
    if (rs % 4 != 0 || imm % 4 != 0) {
        printf("[error] not alligned memory point.");
        return -2;
    }
    if (debug)
        printf("LOADWORD = %d\n", (rs + imm ) >> 2);
  	return mem[(rs ) >> 2]; //+2048?
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

uint32_t Mips::sign_imm(uint32_t i) {
    return ((i >> 15) & 0x1)? (0xffff0000 | i) : i;
}

#endif /* MIPS_H */
